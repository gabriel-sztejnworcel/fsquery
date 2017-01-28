
#include "FSQueryInterpreter.h"
#include "Scope.h"

#include "QueryASTNode.h"
#include "FromTableListASTNode.h"
#include "FromSingleTableASTNode.h"
#include "FromDirectoryASTNode.h"
#include "FromInnerQueryASTNode.h"
#include "BoolExprASTNode.h"
#include "SelectColumnListASTNode.h"
#include "SelectSingleColumnASTNode.h"
#include "BinaryBoolExprASTNode.h"
#include "LiteralBoolExprASTNode.h"
#include "ComparisonBoolExprASTNode.h"
#include "SingleColumnValueASTNode.h"
#include "StringValueASTNode.h"
#include "NumberValueASTNode.h"
#include "SingleColumnASTNode.h"

#include "Table.h"
#include "TableHeader.h"
#include "ColumnDescriptor.h"
#include "RowIterator.h"
#include "TableBuilder.h"
#include "DirectoryReader.h"
#include "Value.h"
#include "ValueType.h"

#include "StringLikeMatcher.h"

#include "FSQueryException.h"

#include <iostream>

FSQueryInterpreter::FSQueryInterpreter() :
	m_directoryReader(DirectoryReader::Create())
{
	
}

FSQueryInterpreter::~FSQueryInterpreter()
{
	
}

std::unique_ptr<Table> FSQueryInterpreter::Interpret(QueryASTNode* node)
{
	TableBuilder tableBuilder;
	PushNewScope();
	
	std::vector<std::unique_ptr<Table>> tables;
	for (size_t i = 0; i < node->GetFromTableListNode()->GetSize(); ++i)
	{
		FromSingleTableASTNode* fromSingleTableNode = node->GetFromTableListNode()->GetTable(i);
		
		std::unique_ptr<Table> tableUPtr = InterpretSingleTable(fromSingleTableNode);
		tables.push_back(std::move(tableUPtr));
		
		Table* table = tables.back().get();
		PutTableInScope(table->GetTableName(), table);
	}
	
	CreateColumns(tableBuilder, node);
	InterpretCartesianProduct(tableBuilder, tables, 0, node);
	PopScope();
	
	return tableBuilder.Construct();
}

void FSQueryInterpreter::InterpretCartesianProduct(TableBuilder& tableBuilder, std::vector<std::unique_ptr<Table>>& tables, size_t currentTablePosition, QueryASTNode* queryNode)
{
	if (currentTablePosition == tables.size())
	{
		BoolExprASTNode* whereClauseNode = queryNode->GetWhereClauseNode();
		
		if (whereClauseNode == nullptr || CheckCondition(whereClauseNode))
		{
			CreateRow(tableBuilder, queryNode);
		}
	}
	else
	{
		Table* currentTable = tables[currentTablePosition].get();
		std::unique_ptr<RowIterator> currentTableIterator = currentTable->Iterator();
		PutIteratorInScope(currentTable->GetTableName(), currentTableIterator.get());
		
		for (currentTableIterator->Begin(); !currentTableIterator->End(); currentTableIterator->Next())
		{
			InterpretCartesianProduct(tableBuilder, tables, currentTablePosition + 1, queryNode);
		}
	}
}

std::unique_ptr<Table> FSQueryInterpreter::InterpretSingleTable(FromSingleTableASTNode* fromSingleTableNode)
{
	std::unique_ptr<Table> table(nullptr);
	
	if (typeid(*fromSingleTableNode) == typeid(FromDirectoryASTNode))
	{
		table = InterpretFromDirectoryTable(static_cast<FromDirectoryASTNode*>(fromSingleTableNode));
	}
	else if (typeid(*fromSingleTableNode) == typeid(FromInnerQueryASTNode))
	{
		table = InterpretFromInnerQueryTable(static_cast<FromInnerQueryASTNode*>(fromSingleTableNode));
	}
	
	return table;
}

std::unique_ptr<Table> FSQueryInterpreter::InterpretFromDirectoryTable(FromDirectoryASTNode* fromDirectoryTableNode)
{
	return m_directoryReader->ReadDirectory(fromDirectoryTableNode->GetPath(), fromDirectoryTableNode->GetAlias(), fromDirectoryTableNode->IsRecursive());
}

std::unique_ptr<Table> FSQueryInterpreter::InterpretFromInnerQueryTable(FromInnerQueryASTNode* fromInnerQueryTableNode)
{
	std::unique_ptr<Table> table = Interpret(fromInnerQueryTableNode->GetQueryNode());
	// validate no duplicate columns
	table->SetTableName(fromInnerQueryTableNode->GetAlias());
	return table;
}

bool FSQueryInterpreter::CheckCondition(BoolExprASTNode* node)
{
	bool result = false;
	
	if (typeid(*node) == typeid(BinaryBoolExprASTNode))
	{
		result = CheckCondition(static_cast<BinaryBoolExprASTNode*>(node));
	}
	else if (typeid(*node) == typeid(LiteralBoolExprASTNode))
	{
		result = CheckCondition(static_cast<LiteralBoolExprASTNode*>(node));
	}
	else if (typeid(*node) == typeid(ComparisonBoolExprASTNode))
	{
		result = CheckCondition(static_cast<ComparisonBoolExprASTNode*>(node));
	}
	
	return result;
}

bool FSQueryInterpreter::CheckCondition(BinaryBoolExprASTNode* node)
{
	bool result = false;
	
	BoolExprASTNode* left = node->GetLeft();
	BoolExprASTNode* right = node->GetRight();
	
	switch (node->GetOper())
	{
	case BinaryBoolOperator::AND:
		result = CheckCondition(left) && CheckCondition(right);
		break;
		
	case BinaryBoolOperator::OR:
		result = CheckCondition(left) || CheckCondition(right);
		break;
	}
	
	return result;
}

bool FSQueryInterpreter::CheckCondition(LiteralBoolExprASTNode* node)
{
	return node->GetVal();
}

bool FSQueryInterpreter::CheckCondition(ComparisonBoolExprASTNode* node)
{
	bool result = false;
	
	SingleValueASTNode* left = node->GetLeft();
	SingleValueASTNode* right = node->GetRight();
	
	std::pair<ValueType, Value> leftValue = GetTypedValue(left);
	std::pair<ValueType, Value> rightValue = GetTypedValue(right);
	
	if (node->GetOper() == ComparisonOperator::LIKE)
	{
		if (leftValue.first != ValueType::STRING ||
			rightValue.first != ValueType::STRING)
		{
			throw FSQueryException("FSQueryInterpreter: Type mismatch");
		}
		
		result = CheckLikeCondition(leftValue.second.GetString(), rightValue.second.GetString());
		return result;
	}
	
	if (leftValue.first == ValueType::TIME &&
		rightValue.first == ValueType::STRING)
	{
		TimeValue timeValue;
		bool parse = TimeValue::ParseTime(rightValue.second.GetString(), timeValue);
		
		if (!parse)
		{
			throw FSQueryException("FSQueryInterpreter: Type mismatch");
		}
		
		rightValue.first = ValueType::TIME;
		rightValue.second = Value(timeValue);
	}
	else if (rightValue.first == ValueType::TIME &&
		leftValue.first == ValueType::STRING)
	{
		TimeValue timeValue;
		bool parse = TimeValue::ParseTime(leftValue.second.GetString(), timeValue);
		
		if (!parse)
		{
			throw FSQueryException("FSQueryInterpreter: Type mismatch");
		}
		
		leftValue.first = ValueType::TIME;
		leftValue.second = Value(timeValue);
	}
	
	if (leftValue.first != rightValue.first)
	{
		throw FSQueryException("FSQueryInterpreter: Type mismatch");
	}
	
	switch (leftValue.first)
	{
	case ValueType::STRING:
		result = CheckCondition(leftValue.second.GetString(), rightValue.second.GetString(), node->GetOper());
		break;
		
	case ValueType::NUMBER:
		result = CheckCondition(leftValue.second.GetNumber(), rightValue.second.GetNumber(), node->GetOper());
		break;
		
	case ValueType::TIME:
		result = CheckCondition(leftValue.second.GetTimeValue(), rightValue.second.GetTimeValue(), node->GetOper());
		break;
		
	default:
		throw FSQueryException("FSQueryInterpreter: Unknown value type");
	}
	
	return result;
}

template <typename T>
bool FSQueryInterpreter::CheckCondition(const T& left, const T& right, ComparisonOperator oper)
{
	bool result = false;
	
	switch (oper)
	{
	case ComparisonOperator::EQUAL:
		result = left == right;
		break;
		
	case ComparisonOperator::NOT_EQUAL:
		result = left != right;
		break;
		
	case ComparisonOperator::LESS_THAN:
		result = left < right;
		break;
		
	case ComparisonOperator::GREATER_THAN:
		result = left > right;
		break;
		
	case ComparisonOperator::LESS_OR_EQUAL:
		result = left <= right;
		break;
		
	case ComparisonOperator::GREATER_OR_EQUAL:
		result = left >= right;
		break;
		
	default:
		throw FSQueryException("FSQueryInterpreter: Unknown comparison operator");
	}
	
	return result;
}

bool FSQueryInterpreter::CheckLikeCondition(const std::string& left, const std::string& right)
{
	StringLikeMatcher matcher(right);
	return matcher.Match(left);
}

std::pair<ValueType, Value> FSQueryInterpreter::GetTypedValue(SingleValueASTNode* node)
{
	if (typeid(*node) == typeid(SingleColumnValueASTNode))
	{
		return GetTypedValue(static_cast<SingleColumnValueASTNode*>(node));
	}
	else if (typeid(*node) == typeid(StringValueASTNode))
	{
		return GetTypedValue(static_cast<StringValueASTNode*>(node));
	}
	else if (typeid(*node) == typeid(NumberValueASTNode))
	{
		return GetTypedValue(static_cast<NumberValueASTNode*>(node));
	}
	else
	{
		throw FSQueryException("FSQueryInterpreter: Unknown node type");
	}
}

std::pair<ValueType, Value> FSQueryInterpreter::GetTypedValue(SingleColumnValueASTNode* node)
{
	std::string columnName = node->GetSingleColumnNode()->GetColumnName();
	std::string tableName = node->GetSingleColumnNode()->GetTableName();
	
	Table* table = GetTableFromScope(tableName);
	RowIterator* rowIterator = GetIteratorFromScope(tableName);
	
	if (table == nullptr || rowIterator == nullptr)
	{
		throw FSQueryException("FSQueryInterpreter: Table '" + tableName + "' not found");
	}
	
	TableHeader* tableHeader = table->GetTableHeader();
	size_t columnPosition = tableHeader->GetColumnPosition(columnName);
	ColumnDescriptor* columnDescriptor = tableHeader->GetColumnDescriptor(columnPosition);
	
	return std::make_pair(columnDescriptor->GetDataType(), *rowIterator->GetValue(columnPosition));
}

std::pair<ValueType, Value> FSQueryInterpreter::GetTypedValue(StringValueASTNode* node)
{
	return std::make_pair(ValueType::STRING, Value(node->GetStr()));
}

std::pair<ValueType, Value> FSQueryInterpreter::GetTypedValue(NumberValueASTNode* node)
{
	return std::make_pair(ValueType::NUMBER, Value(node->GetNumber()));
}

void FSQueryInterpreter::CreateColumns(TableBuilder& tableBuilder, QueryASTNode* queryNode)
{
	SelectColumnListASTNode* selectColumnListNode = queryNode->GetSelectColumnListNode();
	
	for (size_t i = 0; i < selectColumnListNode->GetSize(); ++i)
	{
		SelectSingleColumnASTNode* selectSingleColumnNode = selectColumnListNode->GetColumn(i);
		std::string tableName = selectSingleColumnNode->GetTableName();
		Table* table = GetTableFromScope(tableName);
		
		if (table == nullptr)
		{
			throw FSQueryException("FSQueryInterpreter: Table '" + tableName + "' not found");
		}
		
		TableHeader* tableHeader = table->GetTableHeader();
		std::string columnName = selectSingleColumnNode->GetColumnName();
		
		if (columnName == "*")
		{
			for (size_t j = 0; j < tableHeader->GetNumColumns(); ++j)
			{
				ColumnDescriptor* columnDescriptor = tableHeader->GetColumnDescriptor(j);
				tableBuilder.AddColumn(columnDescriptor->GetColumnName(), columnDescriptor->GetDataType());
			}
		}
		else
		{
			ColumnDescriptor* columnDescriptor = tableHeader->GetColumnDescriptor(columnName);
			
			if (columnDescriptor == nullptr)
			{
				throw FSQueryException("FSQueryInterpreter: Column '" + tableName + "." + columnName + "' not found");
			}
			
			std::string newColumnName = selectSingleColumnNode->GetColumnAlias() != "" ? selectSingleColumnNode->GetColumnAlias() : columnName;
			tableBuilder.AddColumn(newColumnName, columnDescriptor->GetDataType());
		}
	}
	
	tableBuilder.SealColumns();
}

void FSQueryInterpreter::CreateRow(TableBuilder& tableBuilder, QueryASTNode* queryNode)
{
	SelectColumnListASTNode* selectColumnListNode = queryNode->GetSelectColumnListNode();
	size_t nextColumnPosition = 0;
	
	for (size_t i = 0; i < selectColumnListNode->GetSize(); ++i)
	{
		SelectSingleColumnASTNode* selectSingleColumnNode = selectColumnListNode->GetColumn(i);
		std::string tableName = selectSingleColumnNode->GetTableName();
		RowIterator* rowIterator = GetIteratorFromScope(tableName);
		
		if (rowIterator == nullptr)
		{
			throw FSQueryException("FSQueryInterpreter: Table '" + tableName + "' not found");
		}
		
		TableHeader* tableHeader = rowIterator->GetTableHeader();
		std::string columnName = selectSingleColumnNode->GetColumnName();
		
		if (columnName == "*")
		{
			for (size_t j = 0; j < tableHeader->GetNumColumns(); ++j)
			{
				Value* value = rowIterator->GetValue(j);
				tableBuilder.SetValue(nextColumnPosition, value);
				++nextColumnPosition;
			}
		}
		else
		{
			Value* value = rowIterator->GetValue(columnName);
			
			if (value == nullptr)
			{
				throw FSQueryException("FSQueryInterpreter: Column '" + tableName + "." + columnName + "' not found");
			}
			
			tableBuilder.SetValue(nextColumnPosition, value);
			++nextColumnPosition;
		}
	}
	
	tableBuilder.SealRow();
}

void FSQueryInterpreter::PushNewScope()
{
	m_scopeStack.push_front(std::make_unique<Scope>());
}

void FSQueryInterpreter::PopScope()
{
	m_scopeStack.pop_front();
}

void FSQueryInterpreter::PutIteratorInScope(const std::string& tableName, RowIterator* iterator)
{
	m_scopeStack.front()->PutIterator(tableName, iterator);
}

RowIterator* FSQueryInterpreter::GetIteratorFromScope(const std::string& tableName)
{
	RowIterator* iteratorRet = nullptr;
	
	for (auto& iteratorUPtr : m_scopeStack)
	{
		Scope* scope = iteratorUPtr.get();
		RowIterator* iterator = scope->GetIterator(tableName);
		
		if (iterator != nullptr)
		{
			iteratorRet = iterator;
			break;
		}
	}
	
	return iteratorRet;
}

void FSQueryInterpreter::PutTableInScope(const std::string& tableName, Table* table)
{
	m_scopeStack.front()->PutTable(tableName, table);
}

Table* FSQueryInterpreter::GetTableFromScope(const std::string& tableName)
{
	Table* tableRet = nullptr;
	
	for (auto& iteratorUPtr : m_scopeStack)
	{
		Scope* scope = iteratorUPtr.get();
		Table* table = scope->GetTable(tableName);
		
		if (table != nullptr)
		{
			tableRet = table;
			break;
		}
	}
	
	return tableRet;
}

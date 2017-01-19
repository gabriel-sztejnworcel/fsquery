
#ifndef FSQUERYINTERPRETER_H
#define FSQUERYINTERPRETER_H

#include "Value.h"

#include <memory>
#include <list>
#include <vector>

class Table;
class DirectoryReader;
class QueryASTNode;
class FromTableListASTNode;
class FromSingleTableASTNode;
class FromDirectoryASTNode;
class FromInnerQueryASTNode;
class Scope;
class RowIterator;
class TableBuilder;
class BoolExprASTNode;
class BinaryBoolExprASTNode;
class LiteralBoolExprASTNode;
class ComparisonBoolExprASTNode;
class SingleValueASTNode;
class SingleColumnValueASTNode;
class StringValueASTNode;
class NumberValueASTNode;
class Value;

enum class ValueType;
enum class ComparisonOperator;

class FSQueryInterpreter
{
public:
	FSQueryInterpreter();
	~FSQueryInterpreter();
	
	std::unique_ptr<Table> Interpret(QueryASTNode* node);
	
private:
	void InterpretCartesianProduct(TableBuilder& tableBuilder, std::vector<std::unique_ptr<Table>>& tables, size_t currentTablePosition, QueryASTNode* queryNode);
	std::unique_ptr<Table> InterpretSingleTable(FromSingleTableASTNode* fromSingleTableNode);
	std::unique_ptr<Table> InterpretFromDirectoryTable(FromDirectoryASTNode* fromDirectoryTableNode);
	std::unique_ptr<Table> InterpretFromInnerQueryTable(FromInnerQueryASTNode* fromInnerQueryTableNode);
	
	bool CheckCondition(BoolExprASTNode* node);
	bool CheckCondition(BinaryBoolExprASTNode* node);
	bool CheckCondition(LiteralBoolExprASTNode* node);
	bool CheckCondition(ComparisonBoolExprASTNode* node);
	
	template <typename T>
	bool CheckCondition(const T& left, const T& right, ComparisonOperator oper);
	
	std::pair<ValueType, Value> GetTypedValue(SingleValueASTNode* node);
	std::pair<ValueType, Value> GetTypedValue(SingleColumnValueASTNode* node);
	std::pair<ValueType, Value> GetTypedValue(StringValueASTNode* node);
	std::pair<ValueType, Value> GetTypedValue(NumberValueASTNode* node);

	void CreateColumns(TableBuilder& tableBuilder, QueryASTNode* queryNode);
	void CreateRow(TableBuilder& tableBuilder, QueryASTNode* queryNode);

	void PushNewScope();
	void PopScope();
	
	void PutIteratorInScope(const std::string& tableName, RowIterator* iterator);
	RowIterator* GetIteratorFromScope(const std::string& tableName);
	void PutTableInScope(const std::string& tableName, Table* table);
	Table* GetTableFromScope(const std::string& tableName);
	
	std::unique_ptr<DirectoryReader> m_directoryReader;
	std::list<std::unique_ptr<Scope>> m_scopeStack;
};

#endif // FSQUERYINTERPRETER_H

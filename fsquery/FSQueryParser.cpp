
#include "FSQueryParser.h"

#include "QueryASTNode.h"
#include "SelectColumnListASTNode.h"
#include "SelectSingleColumnASTNode.h"
#include "FromTableListASTNode.h"
#include "FromSingleTableASTNode.h"
#include "FromDirectoryASTNode.h"
#include "FromInnerQueryASTNode.h"
#include "BoolExprASTNode.h"
#include "BinaryBoolExprASTNode.h"
#include "LiteralBoolExprASTNode.h"
#include "ComparisonBoolExprASTNode.h"
#include "SingleValueASTNode.h"
#include "SingleColumnValueASTNode.h"
#include "ColumnListASTNode.h"
#include "SingleColumnASTNode.h"
#include "StringValueASTNode.h"
#include "NumberValueASTNode.h"

#include "FSQueryTokenType.h"
#include "FSQueryException.h"

#include <iostream>

FSQueryParser::FSQueryParser(Lexer& lexer) : Parser(lexer, 2)
{
	
}

FSQueryParser::~FSQueryParser() /* override */
{
	
}

std::unique_ptr<QueryASTNode> FSQueryParser::Query()
{
	Match(FSQUERY_TOKEN_TYPE_SELECT);
	std::unique_ptr<SelectColumnListASTNode> selectColumnListNode = SelectColumnList();
	
	Match(FSQUERY_TOKEN_TYPE_FROM);
	std::unique_ptr<FromTableListASTNode> fromTableListNode = FromTableList();
	
	std::unique_ptr<BoolExprASTNode> whereClauseNode(nullptr);
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_WHERE)
	{
		Consume();
		whereClauseNode = WhereClause();
	}
	
	std::unique_ptr<ColumnListASTNode> orderByClauseNode(nullptr);
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_ORDER)
	{
		Consume();
		Match(FSQUERY_TOKEN_TYPE_BY);
		orderByClauseNode = OrderByClause();
	}
	
	return std::make_unique<QueryASTNode>(
		std::move(selectColumnListNode),
		std::move(fromTableListNode),
		std::move(whereClauseNode),
		std::move(orderByClauseNode)
		);
}

std::unique_ptr<SelectColumnListASTNode> FSQueryParser::SelectColumnList()
{
	std::vector<std::unique_ptr<SelectSingleColumnASTNode>> columns;
	
	columns.push_back(SelectSingleColumn());
	
	while (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_COMMA)
	{
		Consume();
		columns.push_back(SelectSingleColumn());
	}
	
	return std::make_unique<SelectColumnListASTNode>(std::move(columns));
}

std::unique_ptr<SelectSingleColumnASTNode> FSQueryParser::SelectSingleColumn()
{
	std::string tableName;
	std::string columnName;
	std::string columnAlias;
	
	tableName = GetCurrent().GetVal();
	Match(FSQUERY_TOKEN_TYPE_IDENTIFIER);
	Match(FSQUERY_TOKEN_TYPE_DOT);
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_ASTERISK)
	{
		columnName = GetCurrent().GetVal();
		Consume();
	}
	else
	{
		columnName = GetCurrent().GetVal();
		Match(FSQUERY_TOKEN_TYPE_IDENTIFIER);
		
		if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_AS)
		{
			Consume(); // "as"
			columnAlias = GetCurrent().GetVal();
			Match(FSQUERY_TOKEN_TYPE_IDENTIFIER);
		}
	}
	
	return std::make_unique<SelectSingleColumnASTNode>(tableName, columnName, columnAlias);
}

std::unique_ptr<FromTableListASTNode> FSQueryParser::FromTableList()
{
	std::vector<std::unique_ptr<FromSingleTableASTNode>> tables;
	
	tables.push_back(FromSingleTable());
	
	while (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_COMMA)
	{
		Consume();
		tables.push_back(FromSingleTable());
	}
	
	return std::make_unique<FromTableListASTNode>(std::move(tables));
}

std::unique_ptr<FromSingleTableASTNode> FSQueryParser::FromSingleTable()
{
	std::unique_ptr<FromSingleTableASTNode> fromSingleTableNode(nullptr);
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_SINGLE_QUOTED_STRING)
	{
		fromSingleTableNode = FromDirectory();
	}
	else
	{
		fromSingleTableNode = FromInnerQuery();
	}
	
	return fromSingleTableNode;
}

std::unique_ptr<FromDirectoryASTNode> FSQueryParser::FromDirectory()
{
	std::string path;
	bool recursive = false;
	std::string alias;
	
	path = GetCurrent().GetVal();
	Match(FSQUERY_TOKEN_TYPE_SINGLE_QUOTED_STRING);
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_RECURSIVE)
	{
		recursive = true;
		Consume();
	}
	
	alias = GetCurrent().GetVal();
	Consume();

	return std::make_unique<FromDirectoryASTNode>(path, recursive, alias);
}

std::unique_ptr<FromInnerQueryASTNode> FSQueryParser::FromInnerQuery()
{
	Match(FSQUERY_TOKEN_TYPE_LEFT_PAREN);
	std::unique_ptr<QueryASTNode> queryNode = Query();
	Match(FSQUERY_TOKEN_TYPE_RIGHT_PAREN);
	
	std::string alias = GetCurrent().GetVal();
	Match(FSQUERY_TOKEN_TYPE_IDENTIFIER);
	
	return std::make_unique<FromInnerQueryASTNode>(std::move(queryNode), alias);
}

std::unique_ptr<BoolExprASTNode> FSQueryParser::WhereClause()
{
	return BoolExpr();
}

std::unique_ptr<BoolExprASTNode> FSQueryParser::BoolExpr()
{
	return BoolAndExpr();
}

std::unique_ptr<BoolExprASTNode> FSQueryParser::BoolAndExpr()
{
	std::unique_ptr<BoolExprASTNode> boolExpr = BoolOrExpr();
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_AND)
	{
		Consume();
		std::unique_ptr<BoolExprASTNode> rightExpr = BoolExpr();
		
		boolExpr = std::make_unique<BinaryBoolExprASTNode>(
			std::move(boolExpr),
			std::move(rightExpr),
			BinaryBoolOperator::AND
			);
	}
	
	return boolExpr;
}

std::unique_ptr<BoolExprASTNode> FSQueryParser::BoolOrExpr()
{
	std::unique_ptr<BoolExprASTNode> boolExpr = BoolAtomicExpr();
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_OR)
	{
		Consume();
		std::unique_ptr<BoolExprASTNode> rightExpr = BoolExpr();
		
		boolExpr = std::make_unique<BinaryBoolExprASTNode>(
			std::move(boolExpr),
			std::move(rightExpr),
			BinaryBoolOperator::OR
			);
	}

	return boolExpr;
}

std::unique_ptr<BoolExprASTNode> FSQueryParser::BoolAtomicExpr()
{
	std::unique_ptr<BoolExprASTNode> boolExpr(nullptr);
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_TRUE ||
		GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_FALSE)
	{
		boolExpr = BoolLiteral();
	}
	else if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_LEFT_PAREN)
	{
		Consume();
		boolExpr = BoolExpr();
		Match(FSQUERY_TOKEN_TYPE_RIGHT_PAREN);
	}
	else
	{
		boolExpr = BoolComparisonExpr();
	}
	
	return boolExpr;
}

std::unique_ptr<LiteralBoolExprASTNode> FSQueryParser::BoolLiteral()
{
	bool val = false;
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_TRUE)
	{
		val = true;
		Consume();
	}
	else
	{
		val = false;
		Match(FSQUERY_TOKEN_TYPE_FALSE);
	}

	return std::make_unique<LiteralBoolExprASTNode>(val);
}

std::unique_ptr<ComparisonBoolExprASTNode> FSQueryParser::BoolComparisonExpr()
{
	std::unique_ptr<SingleValueASTNode> leftValue = SingleValue();
	
	ComparisonOperator oper = CurrentTokenTypeToComparisonOperator();
	Consume(); // operator
	
	std::unique_ptr<SingleValueASTNode> rightValue = SingleValue();
	
	return std::make_unique<ComparisonBoolExprASTNode>(
		std::move(leftValue),
		std::move(rightValue),
		oper
		);
}

std::unique_ptr<SingleValueASTNode> FSQueryParser::SingleValue()
{
	std::unique_ptr<SingleValueASTNode> singleValueNode(nullptr);
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_SINGLE_QUOTED_STRING ||
		GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_NUMBER)
	{
		singleValueNode = LiteralValue();
	}
	else
	{
		singleValueNode = std::make_unique<SingleColumnValueASTNode>(SingleColumn());
	}
	
	return singleValueNode;
}

std::unique_ptr<SingleColumnASTNode> FSQueryParser::SingleColumn()
{
	std::string tableName;
	std::string columnName;
	
	tableName = GetCurrent().GetVal();
	Match(FSQUERY_TOKEN_TYPE_IDENTIFIER);
	Match(FSQUERY_TOKEN_TYPE_DOT);
	
	columnName = GetCurrent().GetVal();
	Match(FSQUERY_TOKEN_TYPE_IDENTIFIER);
	
	return std::make_unique<SingleColumnASTNode>(tableName, columnName);
}

std::unique_ptr<SingleValueASTNode> FSQueryParser::LiteralValue()
{
	std::unique_ptr<SingleValueASTNode> singleValueNode(nullptr);
	
	if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_SINGLE_QUOTED_STRING)
	{
		singleValueNode = std::make_unique<StringValueASTNode>(GetCurrent().GetVal());
		Consume();
	}
	else if (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_NUMBER)
	{
		singleValueNode = std::make_unique<NumberValueASTNode>(std::stod(GetCurrent().GetVal()));
		Consume();
	}

	return singleValueNode;
}

std::unique_ptr<ColumnListASTNode> FSQueryParser::OrderByClause()
{
	return ColumnList();
}

std::unique_ptr<ColumnListASTNode> FSQueryParser::ColumnList()
{
	std::vector<std::unique_ptr<SingleColumnASTNode>> columns;
	
	columns.push_back(SingleColumn());
	
	while (GetCurrent().GetType() == FSQUERY_TOKEN_TYPE_COMMA)
	{
		Consume();
		columns.push_back(SingleColumn());
	}
	
	return std::make_unique<ColumnListASTNode>(std::move(columns));
}

ComparisonOperator FSQueryParser::CurrentTokenTypeToComparisonOperator()
{
	ComparisonOperator oper;
	
	switch (GetCurrent().GetType())
	{
	case FSQUERY_TOKEN_TYPE_EQUAL:
		oper = ComparisonOperator::EQUAL;
		break;
		
	case FSQUERY_TOKEN_TYPE_NOT_EQUAL:
		oper = ComparisonOperator::NOT_EQUAL;
		break;
		
	case FSQUERY_TOKEN_TYPE_LESS_THAN:
		oper = ComparisonOperator::LESS_THAN;
		break;
		
	case FSQUERY_TOKEN_TYPE_GREATER_THAN:
		oper = ComparisonOperator::GREATER_THAN;
		break;
		
	case FSQUERY_TOKEN_TYPE_LESS_OR_EQUAL:
		oper = ComparisonOperator::LESS_OR_EQUAL;
		break;
		
	case FSQUERY_TOKEN_TYPE_GREATER_OR_EQUAL:
		oper = ComparisonOperator::GREATER_OR_EQUAL;
		break;
		
	case FSQUERY_TOKEN_TYPE_LIKE:
		oper = ComparisonOperator::LIKE;
		break;
		
	default:
		throw FSQueryException("FSQueryParser: Unexpected token '" + GetCurrent().GetVal() + "'");
		break;
	}
	
	return oper;
}


#ifndef FSQUERYPARSER_H
#define FSQUERYPARSER_H

#include "Parser.h"
#include "ASTNode.h"

#include <memory>

class Lexer;

class QueryASTNode;
class SelectColumnListASTNode;
class SelectSingleColumnASTNode;
class FromTableListASTNode;
class FromSingleTableASTNode;
class FromDirectoryASTNode;
class FromInnerQueryASTNode;
class BoolExprASTNode;
class BinaryBoolExprASTNode;
class LiteralBoolExprASTNode;
class ComparisonBoolExprASTNode;
class SingleValueASTNode;
class SingleColumnValueASTNode;
class ColumnListASTNode;
class SingleColumnASTNode;

enum class ComparisonOperator;

class FSQueryParser : Parser
{
public:
	FSQueryParser(Lexer& lexer);
    ~FSQueryParser() override;
	
	std::unique_ptr<QueryASTNode> Query();
	
private:
	std::unique_ptr<SelectColumnListASTNode> SelectColumnList();
	std::unique_ptr<SelectSingleColumnASTNode> SelectSingleColumn();
	std::unique_ptr<FromTableListASTNode> FromTableList();
	std::unique_ptr<FromSingleTableASTNode> FromSingleTable();
	std::unique_ptr<FromDirectoryASTNode> FromDirectory();
	std::unique_ptr<FromInnerQueryASTNode> FromInnerQuery();
	std::unique_ptr<BoolExprASTNode> WhereClause();
	std::unique_ptr<BoolExprASTNode> BoolExpr();
	std::unique_ptr<BoolExprASTNode> BoolAndExpr();
	std::unique_ptr<BoolExprASTNode> BoolOrExpr();
	std::unique_ptr<BoolExprASTNode> BoolAtomicExpr();
	std::unique_ptr<ComparisonBoolExprASTNode> BoolComparisonExpr();
	std::unique_ptr<LiteralBoolExprASTNode> BoolLiteral();
	std::unique_ptr<SingleValueASTNode> SingleValue();
	std::unique_ptr<SingleColumnASTNode> SingleColumn();
	std::unique_ptr<SingleValueASTNode> LiteralValue();
	std::unique_ptr<ColumnListASTNode> OrderByClause();
	std::unique_ptr<ColumnListASTNode> ColumnList();
	
	ComparisonOperator CurrentTokenTypeToComparisonOperator();
};

#endif // FSQUERYPARSER_H

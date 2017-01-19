
#ifndef QUERYASTNODE_H
#define QUERYASTNODE_H

#include "ASTNode.h"

#include <memory>

class SelectColumnListASTNode;
class FromTableListASTNode;
class BoolExprASTNode;
class ColumnListASTNode;
class SelectSingleColumnASTNode;

class QueryASTNode : public ASTNode
{
public:
	QueryASTNode(
		std::unique_ptr<SelectColumnListASTNode>&& selectColumnList,
		std::unique_ptr<FromTableListASTNode>&& fromTableList,
		std::unique_ptr<BoolExprASTNode>&& whereClause,
		std::unique_ptr<ColumnListASTNode>&& orderByClause
		);
		
	~QueryASTNode() override;
		
	SelectColumnListASTNode* GetSelectColumnListNode();
	FromTableListASTNode* GetFromTableListNode();
	BoolExprASTNode* GetWhereClauseNode();
	ColumnListASTNode* GetOrderByClauseNode();
		
private:
	std::unique_ptr<SelectColumnListASTNode> m_selectColumnList;
	std::unique_ptr<FromTableListASTNode> m_fromTableList;
	std::unique_ptr<BoolExprASTNode> m_whereClause;
	std::unique_ptr<ColumnListASTNode> m_orderByClause;
};

#endif // QUERYASTNODE_H

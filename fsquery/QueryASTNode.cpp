
#include "QueryASTNode.h"
#include "SelectSingleColumnASTNode.h"
#include "SelectColumnListASTNode.h"
#include "FromTableListASTNode.h"
#include "BoolExprASTNode.h"
#include "ColumnListASTNode.h"


QueryASTNode::QueryASTNode(
	std::unique_ptr<SelectColumnListASTNode>&& selectColumnList,
	std::unique_ptr<FromTableListASTNode>&& fromTableList,
	std::unique_ptr<BoolExprASTNode>&& whereClause,
	std::unique_ptr<ColumnListASTNode>&& orderByClause
	) :
	m_selectColumnList(std::move(selectColumnList)),
	m_fromTableList(std::move(fromTableList)),
	m_whereClause(std::move(whereClause)),
	m_orderByClause(std::move(orderByClause))
{
	
}

QueryASTNode::~QueryASTNode() /* override */
{
	
}

SelectColumnListASTNode* QueryASTNode::GetSelectColumnListNode()
{
	return m_selectColumnList.get();
}

FromTableListASTNode* QueryASTNode::GetFromTableListNode()
{
	return m_fromTableList.get();
}

BoolExprASTNode* QueryASTNode::GetWhereClauseNode()
{
	return m_whereClause.get();
}

ColumnListASTNode* QueryASTNode::GetOrderByClauseNode()
{
	return m_orderByClause.get();
}

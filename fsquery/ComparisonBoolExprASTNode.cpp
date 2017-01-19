
#include "ComparisonBoolExprASTNode.h"
#include "SingleValueASTNode.h"

ComparisonBoolExprASTNode::ComparisonBoolExprASTNode(std::unique_ptr<SingleValueASTNode>&& left, std::unique_ptr<SingleValueASTNode>&& right, ComparisonOperator oper) :
	m_left(std::move(left)),
	m_right(std::move(right)),
	m_oper(oper)
{
	
}

ComparisonBoolExprASTNode::~ComparisonBoolExprASTNode() /* override */
{
    
}

SingleValueASTNode* ComparisonBoolExprASTNode::GetLeft()
{
	return m_left.get();
}

SingleValueASTNode* ComparisonBoolExprASTNode::GetRight()
{
	return m_right.get();
}

ComparisonOperator ComparisonBoolExprASTNode::GetOper() const
{
	return m_oper;
}

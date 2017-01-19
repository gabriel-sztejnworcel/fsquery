
#include "BinaryBoolExprASTNode.h"

BinaryBoolExprASTNode::BinaryBoolExprASTNode(std::unique_ptr<BoolExprASTNode>&& left, std::unique_ptr<BoolExprASTNode>&& right, BinaryBoolOperator oper) :
	m_left(std::move(left)),
	m_right(std::move(right)),
	m_oper(oper)
{
	
}

BinaryBoolExprASTNode::~BinaryBoolExprASTNode() /* override */
{
    
}

BoolExprASTNode* BinaryBoolExprASTNode::GetLeft()
{
	return m_left.get();
}

BoolExprASTNode* BinaryBoolExprASTNode::GetRight()
{
	return m_right.get();
}

BinaryBoolOperator BinaryBoolExprASTNode::GetOper() const
{
	return m_oper;
}

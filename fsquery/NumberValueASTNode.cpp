
#include "NumberValueASTNode.h"

NumberValueASTNode::NumberValueASTNode(double number) :
	m_number(number)
{
	
}

NumberValueASTNode::~NumberValueASTNode() /* override */
{
    
}

double NumberValueASTNode::GetNumber() const
{
	return m_number;
}

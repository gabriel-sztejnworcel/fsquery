
#include "LiteralBoolExprASTNode.h"

LiteralBoolExprASTNode::LiteralBoolExprASTNode(bool val) :
	m_val(val)
{
	
}

LiteralBoolExprASTNode::~LiteralBoolExprASTNode() /* override */
{
    
}

bool LiteralBoolExprASTNode::GetVal() const
{
	return m_val;
}

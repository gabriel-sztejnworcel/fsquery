
#include "StringValueASTNode.h"

StringValueASTNode::StringValueASTNode(const std::string& str) :
	m_str(str)
{
	
}

StringValueASTNode::~StringValueASTNode() /* override */
{
    
}

std::string StringValueASTNode::GetStr() const
{
	return m_str;
}

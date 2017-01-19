
#include "FromInnerQueryASTNode.h"
#include "QueryASTNode.h"

FromInnerQueryASTNode::FromInnerQueryASTNode(std::unique_ptr<QueryASTNode>&& queryNode, const std::string& alias) :
	m_queryNode(std::move(queryNode)),
	m_alias(alias)
{
	
}

FromInnerQueryASTNode::~FromInnerQueryASTNode() /* override */
{
    
}

QueryASTNode* FromInnerQueryASTNode::GetQueryNode()
{
	return m_queryNode.get();
}

std::string FromInnerQueryASTNode::GetAlias() const
{
	return m_alias;
}

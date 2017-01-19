
#include "FromDirectoryASTNode.h"

FromDirectoryASTNode::FromDirectoryASTNode(const std::string& path, bool recursive, const std::string& alias) :
	m_path(path),
	m_recursive(recursive),
	m_alias(alias)
{
	
}

FromDirectoryASTNode::~FromDirectoryASTNode() /* override */
{
    
}

std::string FromDirectoryASTNode::GetPath() const
{
	return m_path;
}

bool FromDirectoryASTNode::IsRecursive() const
{
	return m_recursive;
}

std::string FromDirectoryASTNode::GetAlias() const
{
	return m_alias;
}

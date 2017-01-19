
#include "SingleColumnASTNode.h"

SingleColumnASTNode::SingleColumnASTNode(const std::string& tableName, const std::string& columnName) :
	m_tableName(tableName),
	m_columnName(columnName)
{
	
}

SingleColumnASTNode::~SingleColumnASTNode() /* override */
{
    
}

std::string SingleColumnASTNode::GetTableName() const
{
	return m_tableName;
}

std::string SingleColumnASTNode::GetColumnName() const
{
	return m_columnName;
}

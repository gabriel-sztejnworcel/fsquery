
#include "SelectSingleColumnASTNode.h"

SelectSingleColumnASTNode::SelectSingleColumnASTNode(const std::string& tableName, const std::string& columnName, const std::string& columnAlias) :
	m_tableName(tableName),
	m_columnName(columnName),
	m_columnAlias(columnAlias)
{
	
}

SelectSingleColumnASTNode::~SelectSingleColumnASTNode() /* override */
{
    
}

std::string SelectSingleColumnASTNode::GetTableName() const
{
	return m_tableName;
}

std::string SelectSingleColumnASTNode::GetColumnName() const
{
	return m_columnName;
}

std::string SelectSingleColumnASTNode::GetColumnAlias() const
{
	return m_columnAlias;
}

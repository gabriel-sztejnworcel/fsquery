
#include "ColumnListASTNode.h"
#include "SingleColumnASTNode.h"

ColumnListASTNode::ColumnListASTNode(std::vector<std::unique_ptr<SingleColumnASTNode>>&& columns) :
	m_columns(std::move(columns))
{
	
}

ColumnListASTNode::~ColumnListASTNode() /* override */
{
    
}

size_t ColumnListASTNode::GetSize() const
{
	return m_columns.size();
}

SingleColumnASTNode* ColumnListASTNode::GetColumn(size_t i)
{
	return m_columns[i].get();
}

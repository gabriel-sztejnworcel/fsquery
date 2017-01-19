
#include "SelectColumnListASTNode.h"
#include "SelectSingleColumnASTNode.h"

SelectColumnListASTNode::SelectColumnListASTNode(std::vector<std::unique_ptr<SelectSingleColumnASTNode>>&& columns) :
	m_columns(std::move(columns))
{
	
}

SelectColumnListASTNode::~SelectColumnListASTNode() /* override */
{
    
}

size_t SelectColumnListASTNode::GetSize() const
{
	return m_columns.size();
}

SelectSingleColumnASTNode* SelectColumnListASTNode::GetColumn(size_t i)
{
	return m_columns[i].get();
}

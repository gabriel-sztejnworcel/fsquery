
#include "FromTableListASTNode.h"
#include "FromSingleTableASTNode.h"

FromTableListASTNode::FromTableListASTNode(std::vector<std::unique_ptr<FromSingleTableASTNode>>&& tables) :
	m_tables(std::move(tables))
{
	
}

FromTableListASTNode::~FromTableListASTNode() /* override */
{
    
}

size_t FromTableListASTNode::GetSize() const
{
	return m_tables.size();
}

FromSingleTableASTNode* FromTableListASTNode::GetTable(size_t i)
{
	return m_tables[i].get();
}

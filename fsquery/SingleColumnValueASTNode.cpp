
#include "SingleColumnValueASTNode.h"
#include "SingleColumnASTNode.h"

SingleColumnValueASTNode::SingleColumnValueASTNode(std::unique_ptr<SingleColumnASTNode>&& singleColumnNode) :
	m_singleColumnNode(std::move(singleColumnNode))
{
	
}

SingleColumnValueASTNode::~SingleColumnValueASTNode() /* override */
{
    
}

SingleColumnASTNode* SingleColumnValueASTNode::GetSingleColumnNode()
{
	return m_singleColumnNode.get();
}


#ifndef SINGLECOLUMNVALUEASTNODE_H
#define SINGLECOLUMNVALUEASTNODE_H

#include "SingleValueASTNode.h"

#include <memory>

class SingleColumnASTNode;

class SingleColumnValueASTNode : public SingleValueASTNode
{
public:
	SingleColumnValueASTNode(std::unique_ptr<SingleColumnASTNode>&& singleColumnNode);
    ~SingleColumnValueASTNode() override;
	
	SingleColumnASTNode* GetSingleColumnNode();

private:
	std::unique_ptr<SingleColumnASTNode> m_singleColumnNode;
};

#endif // SINGLECOLUMNVALUEASTNODE_H


#ifndef COLUMNLISTASTNODE_H
#define COLUMNLISTASTNODE_H

#include "ASTNode.h"

#include <vector>
#include <memory>

class SingleColumnASTNode;

class ColumnListASTNode : public ASTNode
{
public:
	ColumnListASTNode(std::vector<std::unique_ptr<SingleColumnASTNode>>&& columns);
    ~ColumnListASTNode() override;
	
	size_t GetSize() const;
	SingleColumnASTNode* GetColumn(size_t i);
	
private:
	std::vector<std::unique_ptr<SingleColumnASTNode>>&& m_columns;
};

#endif // COLUMNLISTASTNODE_H

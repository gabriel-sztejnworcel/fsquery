
#ifndef SELECTCOLUMNLISTASTNODE_H
#define SELECTCOLUMNLISTASTNODE_H

#include "ASTNode.h"

#include <memory>
#include <vector>

class SelectSingleColumnASTNode;

class SelectColumnListASTNode : public ASTNode
{
public:
	SelectColumnListASTNode(std::vector<std::unique_ptr<SelectSingleColumnASTNode>>&& columns);
    ~SelectColumnListASTNode() override;
	
	size_t GetSize() const;
	SelectSingleColumnASTNode* GetColumn(size_t i);
	
private:
	std::vector<std::unique_ptr<SelectSingleColumnASTNode>> m_columns;
};

#endif // SELECTCOLUMNLISTASTNODE_H


#ifndef FROMTABLELISTASTNODE_H
#define FROMTABLELISTASTNODE_H

#include "ASTNode.h"

#include <vector>
#include <memory>

class FromSingleTableASTNode;

class FromTableListASTNode : public ASTNode
{
public:
	FromTableListASTNode(std::vector<std::unique_ptr<FromSingleTableASTNode>>&& tables);
    ~FromTableListASTNode() override;
	
	size_t GetSize() const;
	FromSingleTableASTNode* GetTable(size_t i);
	
private:
	std::vector<std::unique_ptr<FromSingleTableASTNode>> m_tables;
};

#endif // FROMTABLELISTASTNODE_H

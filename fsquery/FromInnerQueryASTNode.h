
#ifndef FROMINNERQUERYASTNODE_H
#define FROMINNERQUERYASTNODE_H

#include "FromSingleTableASTNode.h"

#include <memory>
#include <string>

class QueryASTNode;

class FromInnerQueryASTNode : public FromSingleTableASTNode
{
public:
	FromInnerQueryASTNode(std::unique_ptr<QueryASTNode>&& queryNode, const std::string& alias);
    ~FromInnerQueryASTNode() override;
	
	QueryASTNode* GetQueryNode();
	std::string GetAlias() const;
	
private:
	std::unique_ptr<QueryASTNode> m_queryNode;
	std::string m_alias;
};

#endif // FROMINNERQUERYASTNODE_H

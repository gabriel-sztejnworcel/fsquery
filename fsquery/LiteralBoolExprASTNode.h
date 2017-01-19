
#ifndef LITERALBOOLEXPRASTNODE_H
#define LITERALBOOLEXPRASTNODE_H

#include "BoolExprASTNode.h"

class LiteralBoolExprASTNode : public BoolExprASTNode
{
public:
	LiteralBoolExprASTNode(bool val);
    ~LiteralBoolExprASTNode() override;
	
	bool GetVal() const;

private:
	bool m_val;
};

#endif // LITERALBOOLEXPRASTNODE_H

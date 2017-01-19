
#ifndef BINARYBOOLEXPRASTNODE_H
#define BINARYBOOLEXPRASTNODE_H

#include "BoolExprASTNode.h"

#include <memory>

enum class BinaryBoolOperator
{
	AND,
	OR
};

class BinaryBoolExprASTNode : public BoolExprASTNode
{
public:
	BinaryBoolExprASTNode(std::unique_ptr<BoolExprASTNode>&& left, std::unique_ptr<BoolExprASTNode>&& right, BinaryBoolOperator oper);
	~BinaryBoolExprASTNode() override;
	
	BoolExprASTNode* GetLeft();
	BoolExprASTNode* GetRight();
	BinaryBoolOperator GetOper() const;
	
private:
	std::unique_ptr<BoolExprASTNode> m_left;
	std::unique_ptr<BoolExprASTNode> m_right;
	BinaryBoolOperator m_oper;
};

#endif // BINARYBOOLEXPRASTNODE_H

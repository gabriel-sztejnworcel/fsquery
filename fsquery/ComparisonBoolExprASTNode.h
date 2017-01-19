
#ifndef COMPARISONBOOLEXPRASTNODE_H
#define COMPARISONBOOLEXPRASTNODE_H

#include "BoolExprASTNode.h"

#include <memory>

class SingleValueASTNode;

enum class ComparisonOperator
{
	EQUAL,
	NOT_EQUAL,
	LESS_THAN,
	GREATER_THAN,
	LESS_OR_EQUAL,
	GREATER_OR_EQUAL,
	LIKE
};

class ComparisonBoolExprASTNode : public BoolExprASTNode
{
public:
	ComparisonBoolExprASTNode(std::unique_ptr<SingleValueASTNode>&& left, std::unique_ptr<SingleValueASTNode>&& right, ComparisonOperator oper);
    ~ComparisonBoolExprASTNode() override;
	
	SingleValueASTNode* GetLeft();
	SingleValueASTNode* GetRight();
	ComparisonOperator GetOper() const;
	
private:
	std::unique_ptr<SingleValueASTNode> m_left;
	std::unique_ptr<SingleValueASTNode> m_right;
	ComparisonOperator m_oper;
};

#endif // COMPARISONBOOLEXPRASTNODE_H

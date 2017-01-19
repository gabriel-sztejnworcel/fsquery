
#ifndef NUMBERVALUEASTNODE_H
#define NUMBERVALUEASTNODE_H

#include "SingleValueASTNode.h"

class NumberValueASTNode : public SingleValueASTNode
{
public:
	NumberValueASTNode(double number);
    ~NumberValueASTNode() override;
	
	double GetNumber() const;

private:
	double m_number;
};

#endif // NUMBERVALUEASTNODE_H

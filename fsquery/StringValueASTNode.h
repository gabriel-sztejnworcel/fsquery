
#ifndef STRINGVALUEASTNODE_H
#define STRINGVALUEASTNODE_H

#include "SingleValueASTNode.h"

#include <string>

class StringValueASTNode : public SingleValueASTNode
{
public:
	StringValueASTNode(const std::string& str);
    ~StringValueASTNode() override;
	
	std::string GetStr() const;
	
private:
	std::string m_str;
};

#endif // STRINGVALUEASTNODE_H

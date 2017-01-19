
#ifndef SINGLECOLUMNASTNODE_H
#define SINGLECOLUMNASTNODE_H

#include "ASTNode.h"

#include <string>

class SingleColumnASTNode : public ASTNode
{
public:
	SingleColumnASTNode(const std::string& tableName, const std::string& columnName);
    ~SingleColumnASTNode() override;
	
	std::string GetTableName() const;
	std::string GetColumnName() const;
	
private:
	std::string m_tableName;
	std::string m_columnName;
};

#endif // SINGLECOLUMNASTNODE_H

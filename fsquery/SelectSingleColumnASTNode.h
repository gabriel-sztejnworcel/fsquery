
#ifndef SELECTSINGLECOLUMNASTNODE_H
#define SELECTSINGLECOLUMNASTNODE_H

#include "ASTNode.h"

#include <string>

class SelectSingleColumnASTNode : public ASTNode
{
public:
	SelectSingleColumnASTNode(const std::string& m_tableName, const std::string& m_columnName, const std::string& m_columnAlias);
    ~SelectSingleColumnASTNode() override;
	
	std::string GetTableName() const;
	std::string GetColumnName() const;
	std::string GetColumnAlias() const;

private:
	std::string m_tableName;
	std::string m_columnName;
	std::string m_columnAlias;
};

#endif // SELECTSINGLECOLUMNASTNODE_H


#ifndef FROMDIRECTORYASTNODE_H
#define FROMDIRECTORYASTNODE_H

#include "FromSingleTableASTNode.h"

#include <string>

class FromDirectoryASTNode : public FromSingleTableASTNode
{
public:
	FromDirectoryASTNode(const std::string& path, bool recursive, const std::string& alias);
    ~FromDirectoryASTNode() override;
	
	std::string GetPath() const;
	bool IsRecursive() const;
	std::string GetAlias() const;
	
private:
	std::string m_path;
	bool m_recursive;
	std::string m_alias;
};

#endif // FROMDIRECTORYASTNODE_H

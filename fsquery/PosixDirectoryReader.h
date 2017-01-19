
#ifndef POSIXDIRECTORYREADER_H
#define POSIXDIRECTORYREADER_H

#include "DirectoryReader.h"

class TableBuilder;

class PosixDirectoryReader : public DirectoryReader
{
public:
	PosixDirectoryReader();
	~PosixDirectoryReader();

	std::unique_ptr<Table> ReadDirectory(const std::string& path, const std::string& tableName, bool recursive) override;
	
private:
	void ReadDirectoryInner(const std::string& path, bool recursive, TableBuilder& tableBuilder);
};

#endif // POSIXDIRECTORYREADER_H

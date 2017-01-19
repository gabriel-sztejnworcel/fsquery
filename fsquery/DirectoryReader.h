
#ifndef DIRECTORYREADER_H
#define DIRECTORYREADER_H

#include <memory>
#include <string>

class Table;

class DirectoryReader
{
public:
	static std::unique_ptr<DirectoryReader> Create();
	
	virtual ~DirectoryReader();
	
	virtual std::unique_ptr<Table> ReadDirectory(const std::string& path, const std::string& tableName, bool recursive) = 0;
	
protected:
	std::string GetFileExtension(const std::string& fileName);
};

#endif // DIRECTORYREADER_H

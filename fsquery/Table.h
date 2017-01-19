
#ifndef TABLE_H
#define TABLE_H

#include <memory>
#include <functional>
#include <vector>
#include <string>

class TableHeader;
class RowIterator;

class Table
{
public:
	virtual ~Table();
	
	virtual void SetTableName(const std::string& tableName) = 0;
	virtual std::string GetTableName() = 0;
	
	virtual TableHeader* GetTableHeader() = 0;
	virtual std::unique_ptr<RowIterator> Iterator() = 0;
};

#endif // TABLE_H

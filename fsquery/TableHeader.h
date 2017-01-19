
#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include <vector>
#include <memory>
#include <string>

class ColumnDescriptor;

class TableHeader
{
public:
	TableHeader(std::vector<std::unique_ptr<ColumnDescriptor>>&& columnDescriptors);
	~TableHeader();
	
	ColumnDescriptor* GetColumnDescriptor(size_t columnPosition);
    ColumnDescriptor* GetColumnDescriptor(const std::string& columnName);
	size_t GetColumnPosition(const std::string& columnName, bool throwIfNotFound = true);
    size_t GetNumColumns();

private:
	std::vector<std::unique_ptr<ColumnDescriptor>> m_columnDescriptors;
};

#endif // TABLEHEADER_H

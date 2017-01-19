
#include "TableHeader.h"
#include "ColumnDescriptor.h"
#include "FSQueryException.h"

TableHeader::TableHeader(std::vector<std::unique_ptr<ColumnDescriptor>>&& columnDescriptors) :
	m_columnDescriptors(std::move(columnDescriptors))
{
	
}

TableHeader::~TableHeader()
{
	
}

ColumnDescriptor* TableHeader::GetColumnDescriptor(size_t columnPosition)
{
	if (columnPosition >= m_columnDescriptors.size())
	{
		throw FSQueryException("TableHeader: Column at position " + std::to_string(columnPosition) + " does not exist");
	}
	
	return m_columnDescriptors[columnPosition].get();
}

ColumnDescriptor* TableHeader::GetColumnDescriptor(const std::string& columnName)
{
	return GetColumnDescriptor(GetColumnPosition(columnName));
}

size_t TableHeader::GetColumnPosition(const std::string& columnName, bool throwIfNotFound /* = true */)
{
	bool found = false;
	size_t columnPosition = 0;
	
	for (size_t i = 0; i < m_columnDescriptors.size(); ++i)
	{
		ColumnDescriptor* columnDescriptor = GetColumnDescriptor(i);
		
		if (columnDescriptor->GetColumnName() == columnName)
		{
			columnPosition = i;
			found = true;
			break;
		}
	}
	
	if (!found)
	{
		if (throwIfNotFound)
		{
			throw FSQueryException("TableHeader: Column '" + columnName + "' not found");
		}
		else
		{
			columnPosition = std::string::npos;
		}
	}
	
	return columnPosition;
}

size_t TableHeader::GetNumColumns()
{
	return m_columnDescriptors.size();
}

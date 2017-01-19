
#include "ColumnDescriptor.h"

ColumnDescriptor::ColumnDescriptor(const std::string& columnName, ValueType dataType) :
	m_columnName(columnName),
	m_dataType(dataType)
{
	
}

std::string ColumnDescriptor::GetColumnName() const
{
	return m_columnName;
}

ValueType ColumnDescriptor::GetDataType() const
{
	return m_dataType;
}

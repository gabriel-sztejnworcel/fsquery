
#ifndef COLUMNDESCRIPTOR_H
#define COLUMNDESCRIPTOR_H

#include <string>

enum class ValueType;

class ColumnDescriptor
{
public:
	ColumnDescriptor(const std::string& columnName, ValueType dataType);
	
	std::string GetColumnName() const;
	ValueType GetDataType() const;

private:
	std::string m_columnName;
	ValueType m_dataType;
};

#endif // COLUMNDESCRIPTOR_H

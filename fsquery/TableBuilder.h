
#ifndef TABLEBUILDER_H
#define TABLEBUILDER_H

#include <string>
#include <vector>
#include <memory>

class Table;
class ColumnDescriptor;
class TableHeader;
class Row;
class Value;
class TimeValue;

enum class ValueType;

class TableBuilder
{
public:
	TableBuilder();
	~TableBuilder();
	
	void SetTableName(const std::string& tableName);
	void AddColumn(const std::string& columnName, ValueType dataType);
	void SealColumns();
    bool ColumnsSealed();
    
	void SetValue(size_t columnPosition, Value* value);
	void SetString(size_t columnPosition, const std::string& str);
	void SetNumber(size_t columnPosition, double number);
    void SetTimeValue(size_t columnPosition, const TimeValue& timeValue);
    
	void SealRow();
	
	std::unique_ptr<Table> Construct();

private:
	void Clear();
	void AssertColumnsSealed();

	bool m_columnsSealed;
	std::string m_tableName;
	std::vector<std::unique_ptr<ColumnDescriptor>> m_columnDescriptors;
	std::unique_ptr<TableHeader> m_tableHeader;
	size_t m_numColumns;
	std::vector<std::unique_ptr<Value>> m_values;
	std::vector<std::unique_ptr<Row>> m_rows;
};

#endif // TABLEBUILDER_H

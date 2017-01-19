
#include "TableBuilder.h"
#include "TableImpl.h"
#include "ColumnDescriptor.h"
#include "TableHeader.h"
#include "Row.h"
#include "Value.h"
#include "ValueType.h"
#include "FSQueryException.h"

TableBuilder::TableBuilder() :
	m_columnsSealed(false),
	m_tableHeader(nullptr)
{

}

TableBuilder::~TableBuilder()
{
	
}

void TableBuilder::SetTableName(const std::string& tableName)
{
	m_tableName = tableName;
}

void TableBuilder::AddColumn(const std::string& columnName, ValueType dataType)
{
	if (m_columnsSealed)
	{
		throw FSQueryException("TableBuilder: Columns sealed, cannot add a column");
	}
	
	m_columnDescriptors.push_back(std::make_unique<ColumnDescriptor>(columnName, dataType));
}

void TableBuilder::SealColumns()
{
	if (m_columnsSealed)
	{
		throw FSQueryException("TableBuilder: Columns already sealed, cannot seal columns");
	}

	m_numColumns = m_columnDescriptors.size();
	m_tableHeader = std::make_unique<TableHeader>(std::move(m_columnDescriptors));
	m_values = std::vector<std::unique_ptr<Value>>(m_numColumns);
	m_columnsSealed = true;
}

bool TableBuilder::ColumnsSealed()
{
	return m_columnsSealed;
}

void TableBuilder::SetValue(size_t columnPosition, Value* value)
{
	if (!m_columnsSealed)
	{
		throw FSQueryException("TableBuilder: Columns are not sealed, cannot set row values");
	}

	m_values[columnPosition] = std::make_unique<Value>(*value);
}

void TableBuilder::SetString(size_t columnPosition, const std::string& str)
{
	if (!m_columnsSealed)
	{
		throw FSQueryException("TableBuilder: Columns are not sealed, cannot set row values");
	}

	m_values[columnPosition] = std::make_unique<Value>(str);
}

void TableBuilder::SetNumber(size_t columnPosition, double number)
{
	if (!m_columnsSealed)
	{
		throw FSQueryException("TableBuilder: Columns are not sealed, cannot set row values");
	}

	m_values[columnPosition] = std::make_unique<Value>(number);
}

void TableBuilder::SealRow()
{
	if (!m_columnsSealed)
	{
		throw FSQueryException("TableBuilder: Columns are not sealed, cannot seal row");
	}

	m_rows.push_back(std::make_unique<Row>(std::move(m_values)));
	m_values = std::vector<std::unique_ptr<Value>>(m_numColumns);
}

std::unique_ptr<Table> TableBuilder::Construct()
{
	if (!m_columnsSealed)
	{
		throw FSQueryException("TableBuilder: Columns are not sealed, cannot contruct table");
	}

	std::unique_ptr<Table> table = std::make_unique<TableImpl>(m_tableName, std::move(m_tableHeader), std::move(m_rows));
	Clear();
	return table;
}

void TableBuilder::Clear()
{
	m_columnsSealed = false;
	m_tableName = "";
	m_columnDescriptors = std::vector<std::unique_ptr<ColumnDescriptor>>();
	m_tableHeader = nullptr;
	m_numColumns = 0;
	m_values = std::vector<std::unique_ptr<Value>>();
	m_rows = std::vector<std::unique_ptr<Row>>();
}

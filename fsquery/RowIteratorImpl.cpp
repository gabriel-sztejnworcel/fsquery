
#include "RowIteratorImpl.h"
#include "TableImpl.h"
#include "TableHeader.h"
#include "ValueType.h"
#include "Value.h"
#include "ColumnDescriptor.h"
#include "Row.h"
#include "FSQueryException.h"

#include <cmath>

RowIteratorImpl::RowIteratorImpl(TableImpl& tableImpl) :
	m_tableImpl(tableImpl)
{
	
}

RowIteratorImpl::~RowIteratorImpl()
{
	
}

TableHeader* RowIteratorImpl::GetTableHeader() /* override */
{
	return m_tableImpl.GetTableHeader();
}

void RowIteratorImpl::Begin() /* override */
{
	m_tableRowIterator = m_tableImpl.m_rows.begin();
}

void RowIteratorImpl::Next() /* override */
{
	++m_tableRowIterator;
}

bool RowIteratorImpl::End() /* override */
{
	return m_tableRowIterator == m_tableImpl.m_rows.end();
}

Value* RowIteratorImpl::GetValue(const std::string& columnName) /* override */
{
	size_t columnPosition = m_tableImpl.m_tableHeader->GetColumnPosition(columnName);
	return GetValue(columnPosition);
}

Value* RowIteratorImpl::GetValue(size_t columnPosition) /* override */
{
	Row* row = (*m_tableRowIterator).get();
	Value* value = row->GetValue(columnPosition);
	return value;
}

std::string RowIteratorImpl::GetString(const std::string& columnName) /* override */
{
	size_t columnPosition = m_tableImpl.m_tableHeader->GetColumnPosition(columnName);
	return GetString(columnPosition);
}

std::string RowIteratorImpl::GetString(size_t columnPosition) /* override */
{
	AssertType(columnPosition, ValueType::STRING);
	Row* row = (*m_tableRowIterator).get();
	Value* value = row->GetValue(columnPosition);
	return value->GetString();
}

double RowIteratorImpl::GetNumber(const std::string& columnName) /* override */
{
	size_t columnPosition = m_tableImpl.m_tableHeader->GetColumnPosition(columnName);
	return GetNumber(columnPosition);
}

double RowIteratorImpl::GetNumber(size_t columnPosition) /* override */
{
	AssertType(columnPosition, ValueType::NUMBER);
	Row* row = (*m_tableRowIterator).get();
	Value* value = row->GetValue(columnPosition);
	return value->GetNumber();
}

std::string RowIteratorImpl::ConvertToString(const std::string& columnName) /* override */
{
	size_t columnPosition = m_tableImpl.m_tableHeader->GetColumnPosition(columnName);
	return ConvertToString(columnPosition);
}

std::string RowIteratorImpl::ConvertToString(size_t columnPosition) /* override */
{
	double numValue;
	long longValue;
	std::string strValue;
	
	switch (GetDataType(columnPosition))
	{
	case ValueType::STRING:
		strValue = GetString(columnPosition);
		break;
		
	case ValueType::NUMBER:
		numValue = GetNumber(columnPosition);
		longValue = std::lround(numValue);
		strValue = longValue == numValue ? std::to_string(longValue) : std::to_string(numValue);
		break;
		
	default:
		throw FSQueryException("RowIteratorImpl: Unknown data type");
	}
	
	return strValue;
}

ValueType RowIteratorImpl::GetDataType(size_t columnPosition)
{
	ColumnDescriptor* columnDescriptor = m_tableImpl.m_tableHeader->GetColumnDescriptor(columnPosition);
	return columnDescriptor->GetDataType();
}

void RowIteratorImpl::AssertType(size_t columnPosition, ValueType type)
{
	if (GetDataType(columnPosition) != type)
	{
		throw FSQueryException("RowIteratorImpl: Type mismatch");
	}
}


#include "TableImpl.h"
#include "TableHeader.h"
#include "Row.h"
#include "RowIteratorImpl.h"
#include "TableBuilder.h"
#include "ColumnDescriptor.h"
#include "ValueType.h"
#include "ColumnListASTNode.h"
#include "SingleColumnASTNode.h"
#include "FSQueryException.h"

TableImpl::TableImpl(const std::string& tableName, std::unique_ptr<TableHeader>&& tableHeader, std::vector<std::unique_ptr<Row>>&& rows) :
	m_tableName(tableName),
	m_tableHeader(std::move(tableHeader)),
	m_rows(std::move(rows))
{
	
}

TableImpl::~TableImpl()
{
	
}

void TableImpl::SetTableName(const std::string& tableName) /* override */
{
	m_tableName = tableName;
}

std::string TableImpl::GetTableName() /* override */
{
	return m_tableName;
}

TableHeader* TableImpl::GetTableHeader() /* override */
{
	return m_tableHeader.get();
}

std::unique_ptr<RowIterator> TableImpl::Iterator() /* override */
{
	return std::make_unique<RowIteratorImpl>(*this);
}

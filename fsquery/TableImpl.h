
#ifndef TABLEIMPL_H
#define TABLEIMPL_H

#include "Table.h"

#include <vector>
#include <memory>
#include <string>

class TableHeader;
class Row;
class TableBuilder;

class TableImpl : public Table
{
public:
	TableImpl(const std::string& tableName, std::unique_ptr<TableHeader>&& tableHeader, std::vector<std::unique_ptr<Row>>&& rows);
	~TableImpl();
	
	void SetTableName(const std::string& tableName) override;
	std::string GetTableName() override;

	TableHeader* GetTableHeader() override;
	std::unique_ptr<RowIterator> Iterator() override;

private:
	friend class RowIteratorImpl;

	std::string m_tableName;
	std::unique_ptr<TableHeader> m_tableHeader;
	std::vector<std::unique_ptr<Row>> m_rows;
};

#endif // TABLEIMPL_H

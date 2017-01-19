
#ifndef ROWITERATORIMPL_H
#define ROWITERATORIMPL_H

#include "RowIterator.h"

#include <string>
#include <vector>
#include <memory>

class TableImpl;
class Row;

enum class ValueType;

class RowIteratorImpl : public RowIterator
{
public:
	RowIteratorImpl(TableImpl& tableImpl);
	~RowIteratorImpl();
	
	TableHeader* GetTableHeader() override;

	void Begin() override;
	void Next() override;
	bool End() override;

	Value* GetValue(const std::string& columnName) override;
	Value* GetValue(size_t columnPosition) override;

	std::string GetString(const std::string& columnName) override;
	std::string GetString(size_t columnPosition) override;
	
	double GetNumber(const std::string& columnName) override;
	double GetNumber(size_t columnPosition) override;
	
	std::string ConvertToString(const std::string& columnName) override;
	std::string ConvertToString(size_t columnPosition) override;

private:
	ValueType GetDataType(size_t columnPosition);
	void AssertType(size_t columnPosition, ValueType type);

	TableImpl& m_tableImpl;
	std::vector<std::unique_ptr<Row>>::iterator m_tableRowIterator;
};

#endif // ROWITERATORIMPL_H

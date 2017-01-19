
#ifndef ROWITERATOR_H
#define ROWITERATOR_H

#include <string>

class ColumnDescriptor;
class Value;
class TableHeader;

class RowIterator
{
public:
	RowIterator();
	virtual ~RowIterator();
	
	virtual TableHeader* GetTableHeader() = 0;
	
	virtual void Begin() = 0;
	virtual void Next() = 0;
	virtual bool End() = 0;
	
	virtual Value* GetValue(const std::string& columnName) = 0;
	virtual Value* GetValue(size_t columnPosition) = 0;
	
	virtual std::string GetString(const std::string& columnName) = 0;
	virtual std::string GetString(size_t columnPosition) = 0;
	
	virtual double GetNumber(const std::string& columnName) = 0;
	virtual double GetNumber(size_t columnPosition) = 0;

	virtual std::string ConvertToString(const std::string& columnName) = 0;
	virtual std::string ConvertToString(size_t columnPosition) = 0;
};

#endif // ROWITERATOR_H

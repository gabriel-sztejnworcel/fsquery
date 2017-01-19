
#ifndef SCOPE_H
#define SCOPE_H

#include <unordered_map>
#include <string>

class RowIterator;
class Table;

class Scope
{
public:
	Scope();
	~Scope();
	
	void PutIterator(const std::string& tableName, RowIterator* iterator);
	RowIterator* GetIterator(const std::string& tableName);

	void PutTable(const std::string& tableName, Table* table);
	Table* GetTable(const std::string& tableName);

private:
	std::unordered_map<std::string, RowIterator*> m_iterators;
    std::unordered_map<std::string, Table*> m_tables;
};

#endif // SCOPE_H

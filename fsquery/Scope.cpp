
#include "Scope.h"

Scope::Scope()
{
	
}

Scope::~Scope()
{
	
}

void Scope::PutIterator(const std::string& tableName, RowIterator* iterator)
{
	m_iterators[tableName] = iterator;
}

RowIterator* Scope::GetIterator(const std::string& tableName)
{
	RowIterator* iterator = nullptr;
	
	auto mapIterator = m_iterators.find(tableName);
	if (mapIterator != m_iterators.end())
	{
		iterator = mapIterator->second;
	}
	
	return iterator;
}

void Scope::PutTable(const std::string& tableName, Table* table)
{
	m_tables[tableName] = table;
}

Table* Scope::GetTable(const std::string& tableName)
{
	Table* table = nullptr;
	
	auto mapIterator = m_tables.find(tableName);
	if (mapIterator != m_tables.end())
	{
		table = mapIterator->second;
	}
	
	return table;
}

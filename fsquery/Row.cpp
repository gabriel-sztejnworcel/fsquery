
#include "Row.h"
#include "Value.h"

Row::Row(std::vector<std::unique_ptr<Value>>&& values) :
	m_values(std::move(values))
{
	
}

Row::~Row()
{
	
}

Value* Row::GetValue(size_t i)
{
	return m_values[i].get();
}

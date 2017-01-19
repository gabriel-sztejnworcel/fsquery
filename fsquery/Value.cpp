
#include "Value.h"

Value::Value(const std::string& strValue) :
	m_strValue(strValue)
{
	
}

Value::Value(double numValue) :
	m_numValue(numValue)
{
	
}

std::string Value::GetString() const
{
	return m_strValue;
}

double Value::GetNumber() const
{
	return m_numValue;
}

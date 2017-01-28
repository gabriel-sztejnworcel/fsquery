
#include "Value.h"

Value::Value(const std::string& strValue) :
	m_strValue(strValue)
{
	
}

Value::Value(double numValue) :
	m_numValue(numValue)
{
	
}

Value::Value(const TimeValue& timeValue) :
	m_timeValue(timeValue)
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

TimeValue Value::GetTimeValue() const
{
	return m_timeValue;
}

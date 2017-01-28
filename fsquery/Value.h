
#ifndef VALUE_H
#define VALUE_H

#include "TimeValue.h"

#include <string>

class Value
{
public:
	Value(const std::string& strValue);
	Value(double numValue);
	Value(const TimeValue& timeValue);
	
	std::string GetString() const;
	double GetNumber() const;
	TimeValue GetTimeValue() const;

private:
	std::string m_strValue;
	double m_numValue;
	TimeValue m_timeValue;
};

#endif // VALUE_H

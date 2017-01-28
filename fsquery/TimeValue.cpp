
#include "TimeValue.h"

#include <cstdio>

TimeValue::TimeValue(
	unsigned int year /* = 0 */,
	unsigned int month /* = 0 */,
	unsigned int day /* = 0 */,
	unsigned int hour /* = 0 */,
	unsigned int min /* = 0 */,
	unsigned int sec /* = 0 */
	)
{
	Set(year, month, day, hour, min, sec);
}

bool TimeValue::operator ==(const TimeValue& operand) const
{
	return m_year == operand.m_year
		&& m_month == operand.m_month
		&& m_day == operand.m_day
		&& m_hour == operand.m_hour
		&& m_min == operand.m_min
		&& m_sec == operand.m_sec;
}

bool TimeValue::operator !=(const TimeValue& operand) const
{
	return !(*this == operand);
}

bool TimeValue::operator <(const TimeValue& operand) const
{
	if (m_year < operand.m_year)
	{
		return true;
	}
	
	if (m_year > operand.m_year)
	{
		return false;
	}
	
	// m_year == operand.m_year
	
	if (m_month < operand.m_month)
	{
		return true;
	}
	
	if (m_month > operand.m_month)
	{
		return false;
	}
	
	// m_month == operand.m_month
	
	if (m_day < operand.m_day)
	{
		return true;
	}
	
	if (m_day > operand.m_day)
	{
		return false;
	}

	// m_day == operand.m_day
	
	if (m_hour < operand.m_hour)
	{
		return true;
	}
	
	if (m_hour > operand.m_hour)
	{
		return false;
	}

	// m_hour == operand.m_hour
	
	if (m_min < operand.m_min)
	{
		return true;
	}
	
	if (m_min > operand.m_min)
	{
		return false;
	}

	// m_min == operand.m_min
	
	if (m_sec < operand.m_sec)
	{
		return true;
	}
	
	if (m_sec > operand.m_sec)
	{
		return false;
	}
	
	// m_sec == operand.m_sec
	
	return false;
}

bool TimeValue::operator >(const TimeValue& operand) const
{
	return !(*this == operand || *this < operand);
}

bool TimeValue::operator <=(const TimeValue& operand) const
{
	return *this == operand || *this < operand;
}

bool TimeValue::operator >=(const TimeValue& operand) const
{
	return *this == operand || *this > operand;
}

TimeValue::~TimeValue()
{
	
}

void TimeValue::Set(
	unsigned int year/*  = 0 */,
	unsigned int month /* = 0 */,
	unsigned int day /* = 0 */,
	unsigned int hour /* = 0 */,
	unsigned int min /* = 0 */,
	unsigned int sec /* = 0 */
	)
{
	m_year = year;
	m_month = month;
	m_day = day;
	m_hour = hour;
	m_min = min;
	m_sec = sec;
}

/* static */ bool TimeValue::ParseTime(const std::string& str, TimeValue& timeValue)
{
	bool parse = false;
	
	if (str.length() == 19) // yyyy-dd-mm HH:MM:SS
	{
		if (ValidateLongFormat(str))
		{
			unsigned int year = (unsigned int)std::stoi(str.substr(0, 4));
			unsigned int month = (unsigned int)std::stoi(str.substr(5, 2));
			unsigned int day = (unsigned int)std::stoi(str.substr(8, 2));
			unsigned int hour = (unsigned int)std::stoi(str.substr(11, 2));
			unsigned int min = (unsigned int)std::stoi(str.substr(14, 2));
			unsigned int sec = (unsigned int)std::stoi(str.substr(17, 2));
			
			timeValue.Set(year, month, day, hour, min, sec);
			parse = true;
		}
	}
	else if (str.length() == 10) // yyyy-dd-mm
	{
		if (ValidateShortFormat(str))
		{
			unsigned int year = (unsigned int)std::stoi(str.substr(0, 4));
			unsigned int month = (unsigned int)std::stoi(str.substr(5, 2));
			unsigned int day = (unsigned int)std::stoi(str.substr(8, 2));
			
			timeValue.Set(year, month, day);
			parse = true;
		}
	}
	
	return parse;
}

/* static */ bool TimeValue::ValidateLongFormat(const std::string& str)
{
	bool valid = false;
	
	if (IsDigit(str[0]) && IsDigit(str[1]) && IsDigit(str[2]) && IsDigit(str[3])
		&& str[4] == '-' && IsDigit(str[5]) && IsDigit(str[6])
		&& str[7] == '-' && IsDigit(str[8]) && IsDigit(str[9])
		&& str[10] == ' ' && IsDigit(str[11]) && IsDigit(str[12])
		&& str[13] == ':' && IsDigit(str[14]) && IsDigit(str[15])
		&& str[16] == ':' && IsDigit(str[17]) && IsDigit(str[18]))
	{
		valid = true;
	}
	
	return valid;
}

/* static */ bool TimeValue::ValidateShortFormat(const std::string& str)
{
	bool valid = false;
	
	if (IsDigit(str[0]) && IsDigit(str[1]) && IsDigit(str[2]) && IsDigit(str[3])
		&& str[4] == '-' && IsDigit(str[5]) && IsDigit(str[6])
		&& str[7] == '-' && IsDigit(str[8]) && IsDigit(str[9]))
	{
		valid = true;
	}
	
	return valid;
}

/* static */ bool TimeValue::IsDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

std::string TimeValue::ToString() const
{
	char buf[20]; // yyyy-dd-mm HH:MM:SS
	std::sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", m_year, m_month, m_day, m_hour, m_min, m_sec);
	return std::string(buf);
}


#ifndef TIMEVALUE_H
#define TIMEVALUE_H

#include <string>

class TimeValue
{
public:
	TimeValue(
		unsigned int year = 0,
		unsigned int month = 0,
		unsigned int day = 0,
		unsigned int hour = 0,
		unsigned int min = 0,
		unsigned int sec = 0
		);
		
	bool operator ==(const TimeValue& operand) const;
	bool operator !=(const TimeValue& operand) const;
	bool operator <(const TimeValue& operand) const;
	bool operator >(const TimeValue& operand) const;
	bool operator <=(const TimeValue& operand) const;
	bool operator >=(const TimeValue& operand) const;
		
	~TimeValue();
	
	void Set(
		unsigned int year = 0,
		unsigned int month = 0,
		unsigned int day = 0,
		unsigned int hour = 0,
		unsigned int min = 0,
		unsigned int sec = 0
		);
	
	static bool ParseTime(const std::string& str, TimeValue& timeValue);
	
	std::string ToString() const;

private:
	static bool ValidateLongFormat(const std::string& str);
	static bool ValidateShortFormat(const std::string& str);
	static bool IsDigit(char ch);

	unsigned int m_year;
	unsigned int m_month;
	unsigned int m_day;
	unsigned int m_hour;
	unsigned int m_min;
	unsigned int m_sec;
};

#endif // TIMEVALUE_H

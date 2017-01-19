
#ifndef VALUE_H
#define VALUE_H

#include <string>

class Value
{
public:
	Value(const std::string& strValue);
	Value(double numValue);
	
	std::string GetString() const;
	double GetNumber() const;

private:
	std::string m_strValue;
	double m_numValue;
};

#endif // VALUE_H

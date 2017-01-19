
#include "StringInputStream.h"

StringInputStream::StringInputStream(const std::string& str)
: m_str(str), m_currentPosition(0), m_beforeStart(true)
{
	
}

bool StringInputStream::HasNext() const /* override */
{
	return (m_beforeStart && m_str.length() > 0) || m_currentPosition + 1 < m_str.length();
}

char StringInputStream::GetNext() /* override */
{
	if (m_beforeStart)
	{
		m_beforeStart = false;
	}
	else
	{
		++m_currentPosition;
	}
	
	return m_str[m_currentPosition];
}

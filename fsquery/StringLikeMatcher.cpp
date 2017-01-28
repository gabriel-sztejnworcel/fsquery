
#include "StringLikeMatcher.h"

StringLikeMatcher::StringLikeMatcher(const std::string& pattern)
{
	SplitPattern(pattern);
}

StringLikeMatcher::~StringLikeMatcher()
{
}

bool StringLikeMatcher::Match(const std::string& str)
{
	size_t startPosition = 0;
	bool matchSubstrAtStart = true; // true - next substr start = startPosition,
									// false - next substr start >= startPosition
									
	for (auto& patternItem : m_pattern)
	{
		if (patternItem == "%")
		{
			matchSubstrAtStart = false;
		}
		else if (patternItem == "_")
		{
			++startPosition;
			matchSubstrAtStart = true;
		}
		else
		{
			if (startPosition + patternItem.length() > str.length())
			{
				return false;
			}
			
			if (matchSubstrAtStart)
			{
				if (str.substr(startPosition, patternItem.length()) == patternItem)
				{
					startPosition += patternItem.length();
				}
				else
				{
					return false;
				}
			}
			else
			{
				size_t substrPos = str.find(patternItem, startPosition);
				
				if (substrPos != std::string::npos)
				{
					startPosition = substrPos + patternItem.length();
				}
				else
				{
					return false;
				}
			}
		}
	}
	
	return true;
}

void StringLikeMatcher::SplitPattern(const std::string& pattern)
{
	size_t substrStart = 0;
	size_t substrLen = 0;
	
	for (size_t i = 0; i < pattern.length(); ++i)
	{
		char ch = pattern[i];
		
		if (ch == '_' || ch == '%')
		{
			if (substrLen > 0)
			{
				m_pattern.push_back(pattern.substr(substrStart, substrLen));
			}
			
			m_pattern.push_back(pattern.substr(i, 1));
			substrStart = i + 1;
			substrLen = 0;
		}
		else
		{
			++substrLen;
		}
	}
	
	if (substrLen > 0)
	{
		m_pattern.push_back(pattern.substr(substrStart, substrLen));
	}
}

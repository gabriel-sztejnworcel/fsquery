
#ifndef STRINGLIKEMATCHER_H
#define STRINGLIKEMATCHER_H

#include <string>
#include <vector>

class StringLikeMatcher
{
public:
	StringLikeMatcher(const std::string& pattern);
	~StringLikeMatcher();
	
	bool Match(const std::string& str);
	
private:
	void SplitPattern(const std::string& pattern);

	std::vector<std::string> m_pattern;
};

#endif // STRINGLIKEMATCHER_H

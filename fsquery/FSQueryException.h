
#ifndef FSQUERYEXCEPTION_H
#define FSQUERYEEXCEPTION_H

#include <string>

class FSQueryException
{
public:
	FSQueryException(const std::string& msg);
	std::string GetMessage() const;
	
private:
	std::string m_msg;
};

#endif // FSQUERYEXCEPTION_H

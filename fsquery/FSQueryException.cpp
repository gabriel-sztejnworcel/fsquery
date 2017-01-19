
#include "FSQueryException.h"

FSQueryException::FSQueryException(const std::string& msg)
: m_msg(msg)
{
	
}

std::string FSQueryException::GetMessage() const
{
	return m_msg;
}

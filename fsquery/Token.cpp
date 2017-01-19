
#include "Token.h"

/* static */ Token Token::s_endOfInput = Token(-1, "");

/* static */ Token& Token::EndOfInput()
{
    return s_endOfInput;
}

Token::Token()
: m_type(0), m_val("")
{
    
}

Token::Token(int type, const std::string& val)
: m_type(type), m_val(val)
{
	
}

bool Token::operator==(const Token& token)
{
	return m_type == token.GetType() && m_val == token.GetVal();
}

bool Token::operator!=(const Token& token)
{
	return !(*this == token);
}

int Token::GetType() const
{
	return m_type;
}

std::string Token::GetVal() const
{
	return m_val;
}


#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
private:
    static Token s_endOfInput;
    
public:
    static Token& EndOfInput();

	Token();
    Token(int type, const std::string& val);
    bool operator==(const Token& token);
    bool operator!=(const Token& token);
	
	int GetType() const;
	std::string GetVal() const;
	
private:
	int m_type;
	std::string m_val;
};

#endif // TOKEN_H

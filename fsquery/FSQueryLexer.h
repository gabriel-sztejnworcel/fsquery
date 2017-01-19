
#ifndef FSQUERYLEXER_H
#define FSQUERYLEXER_H

#include "Lexer.h"

#include <unordered_map>

class FSQueryLexer : public Lexer
{
private:
	static std::unordered_map<std::string, int> s_keyWords;

public:
	FSQueryLexer(InputStream& inputStream);
	Token GetNext() override;
	
private:
	Token Number(char firstChar);
	Token SingleQuotedString(char firstChar);
	Token IdentifierOrKeyWord(char firstChar);

	void ConsumeWhiteSpaces();
	bool IsDigit(char ch);
	bool IsLetter(char ch);
	bool IsWhiteSpace(char ch);
};

#endif // FSQUERYLEXER_H

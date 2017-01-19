
#ifndef PARSER_H
#define PARSER_H

#include "Token.h"

#include <memory>

class Lexer;

class Parser
{
public:
	Parser(Lexer& lexer, size_t lookaheadBufferSize);
	virtual ~Parser() {}

protected:
	void Consume();
	Token& GetCurrent();
	Token& Lookahead(size_t offset);
	bool IsAtEndOfInput();
	void Match(int tokenType);

	Lexer& m_lexer;
	size_t m_lookaheadBufferSize;
	std::unique_ptr<Token[]> m_lookaheadBuffer;
	size_t m_currentPositionInLookahead;

private:
	void InitializeBuffer();
};

#endif // PARSER_H

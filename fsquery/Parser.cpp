
#include "Parser.h"
#include "Parser.h"
#include "Lexer.h"
#include "FSQueryException.h"

#include <iostream> // debug

Parser::Parser(Lexer& lexer, size_t lookaheadBufferSize) :
	m_lexer(lexer),
	m_lookaheadBufferSize(lookaheadBufferSize),
	m_lookaheadBuffer(std::make_unique<Token[]>(lookaheadBufferSize)),
	m_currentPositionInLookahead(0)
{
	InitializeBuffer();
}

void Parser::Consume()
{
	m_lookaheadBuffer[m_currentPositionInLookahead] = m_lexer.GetNext();
	m_currentPositionInLookahead = (m_currentPositionInLookahead + 1) % m_lookaheadBufferSize;
}

Token& Parser::GetCurrent()
{
	return Lookahead(0);
}

Token& Parser::Lookahead(size_t offset)
{
	return m_lookaheadBuffer[(m_currentPositionInLookahead + offset) % m_lookaheadBufferSize];
}

bool Parser::IsAtEndOfInput()
{
	return GetCurrent() == Token::EndOfInput();
}

void Parser::Match(int tokenType)
{
	if (GetCurrent().GetType() != tokenType)
	{
		throw FSQueryException("Parser: Unexpected token '" + GetCurrent().GetVal() + "'");
	}
	
	Consume();
}

void Parser::InitializeBuffer()
{
	for (size_t i = 0; i < m_lookaheadBufferSize; ++i)
	{
		m_lookaheadBuffer[i] = m_lexer.GetNext();
	}
}

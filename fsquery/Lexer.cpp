
#include "Lexer.h"
#include "InputStream.h"

#include <iostream>

Lexer::Lexer(InputStream& inputStream, size_t lookaheadBufferSize) :
	m_inputStream(inputStream),
	m_lookaheadBufferSize(lookaheadBufferSize),
	m_lookaheadBuffer(std::make_unique<char[]>(lookaheadBufferSize)),
	m_currentPositionInLookahead(0)
{
	InitializeBuffer();
}

void Lexer::Consume()
{
	if (m_inputStream.HasNext())
	{
		m_lookaheadBuffer[m_currentPositionInLookahead] = m_inputStream.GetNext();
	}
	else if (m_endPositionInLookahead == m_lookaheadBufferSize)
	{
		m_endPositionInLookahead = m_currentPositionInLookahead;
	}
	
	m_currentPositionInLookahead = (m_currentPositionInLookahead + 1) % m_lookaheadBufferSize;

	// Trace();
}

char Lexer::GetCurrent()
{
	return Lookahead(0);
}

bool Lexer::IsAtEndOfInput()
{
	return m_currentPositionInLookahead == m_endPositionInLookahead;
}

char Lexer::Lookahead(size_t offset)
{
	return m_lookaheadBuffer[(m_currentPositionInLookahead + offset) % m_lookaheadBufferSize];
}

void Lexer::InitializeBuffer()
{
	m_endPositionInLookahead = m_lookaheadBufferSize;

	for (size_t i = 0; i < m_lookaheadBufferSize; ++i)
	{
		if (m_inputStream.HasNext())
		{
			m_lookaheadBuffer[i] = m_inputStream.GetNext();
		}
		else
		{
			m_endPositionInLookahead = i;
			break;
		}
		
		// Trace();
	}
}

// *** debug *** //
void Lexer::Trace()
{
	for (size_t i = 0; i < m_lookaheadBufferSize; ++i)
	{
		size_t j = (i + m_currentPositionInLookahead) % m_lookaheadBufferSize;
		std::cout << j << "('" <<  m_lookaheadBuffer[j] << "') ";
	}
	
	std::cout << std::endl;
	std::cout << "Current position: " << m_currentPositionInLookahead << std::endl;
	std::cout << "End position: " << m_endPositionInLookahead << std::endl;
	std::cout << std::endl;
}

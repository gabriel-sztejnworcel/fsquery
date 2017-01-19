
#ifndef LEXER_H
#define LEXER_H

#include "Token.h"

#include <memory>

class InputStream;

class Lexer
{
public:
	Lexer(InputStream& inputStream, size_t lookaheadBufferSize);
	virtual ~Lexer() {}
    
    virtual Token GetNext() = 0;
    
protected:
    void Consume();
    char GetCurrent();
    bool IsAtEndOfInput();
    char Lookahead(size_t offset);
    
    // *** debug *** //
    void Trace();
    
private:
    void InitializeBuffer();

    InputStream& m_inputStream;
    size_t m_lookaheadBufferSize;
    std::unique_ptr<char[]> m_lookaheadBuffer;
    size_t m_currentPositionInLookahead;
    size_t m_endPositionInLookahead;
};

#endif // LEXER_H

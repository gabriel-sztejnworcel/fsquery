
#include "FSQueryLexer.h"
#include "FSQueryTokenType.h"
#include "FSQueryException.h"

#include <iostream>

/* static */ std::unordered_map<std::string, int> FSQueryLexer::s_keyWords =
{
	{"select", FSQUERY_TOKEN_TYPE_SELECT},
	{"from", FSQUERY_TOKEN_TYPE_FROM},
	{"where", FSQUERY_TOKEN_TYPE_WHERE},
	{"order", FSQUERY_TOKEN_TYPE_ORDER},
	{"by", FSQUERY_TOKEN_TYPE_BY},
	{"as", FSQUERY_TOKEN_TYPE_AS},
	{"recursive", FSQUERY_TOKEN_TYPE_RECURSIVE},
	{"and", FSQUERY_TOKEN_TYPE_AND},
	{"or", FSQUERY_TOKEN_TYPE_OR},
	{"true", FSQUERY_TOKEN_TYPE_TRUE},
	{"false", FSQUERY_TOKEN_TYPE_FALSE},
	{"like", FSQUERY_TOKEN_TYPE_LIKE}
};

FSQueryLexer::FSQueryLexer(InputStream& inputStream)
: Lexer(inputStream, 2)
{

}

Token FSQueryLexer::GetNext() /* override */
{
	ConsumeWhiteSpaces();
	
	if (IsAtEndOfInput())
	{
		return Token::EndOfInput();
	}

	Token token;
	char ch = GetCurrent();

	if (IsDigit(ch))
	{
		token = Number(ch);
	}
	else if (IsLetter(ch))
	{
		token = IdentifierOrKeyWord(ch);
	}
	else if (ch == '\'')
	{
		token = SingleQuotedString(ch);
	}
	else
	{
		int tokenType;
		std::string tokenVal;
		
		switch (ch)
		{
		case ',':
			tokenType = FSQUERY_TOKEN_TYPE_COMMA;
			tokenVal = ",";
			break;

		case '*':
			tokenType = FSQUERY_TOKEN_TYPE_ASTERISK;
			tokenVal = "*";
			break;

		case '.':
			tokenType = FSQUERY_TOKEN_TYPE_DOT;
			tokenVal = ".";
			break;

		case '(':
			tokenType = FSQUERY_TOKEN_TYPE_LEFT_PAREN;
			tokenVal = "(";
			break;
			
		case ')':
			tokenType = FSQUERY_TOKEN_TYPE_RIGHT_PAREN;
			tokenVal = ")";
			break;

		case '=':
			tokenType = FSQUERY_TOKEN_TYPE_EQUAL;
			tokenVal = "=";
			break;
			
		case '<':
		
			if (Lookahead(1) == '>')
			{
				tokenType = FSQUERY_TOKEN_TYPE_NOT_EQUAL;
				tokenVal = "<>";
				Consume();
			}
			else if (Lookahead(1) == '=')
			{
				tokenType = FSQUERY_TOKEN_TYPE_LESS_OR_EQUAL;
				tokenVal = "<=";
				Consume();
			}
			else
			{
				tokenType = FSQUERY_TOKEN_TYPE_LESS_THAN;
				tokenVal = "<";
			}

			break;
			
		case '>':
		
			if (Lookahead(1) == '=')
			{
				tokenType = FSQUERY_TOKEN_TYPE_GREATER_OR_EQUAL;
				tokenVal = ">=";
				Consume();
			}
			else
			{
				tokenType = FSQUERY_TOKEN_TYPE_GREATER_THAN;
				tokenVal = ">";
			}

			break;

		default:
			throw FSQueryException("FSQueryLexer: Unexpected character '" + std::string(1, ch) + "'");
		}
		
		token = Token(tokenType, tokenVal);
		Consume();
	}
	
	return token;
}

Token FSQueryLexer::Number(char firstChar)
{
	char ch = firstChar;
	bool foundDecimalPoint = false;
	std::string tokenVal;
	
	bool end = false;
	while (!end)
	{
		if (ch == '.')
		{
			foundDecimalPoint = true;
		}
		
		tokenVal.push_back(ch);
		Consume();
		
		if (IsAtEndOfInput())
		{
			end = true;
		}
		else
		{
			ch = GetCurrent();
			if (!(IsDigit(ch) || (ch == '.' && !foundDecimalPoint)))
			{
				end = true;
			}
		}
	}
	
	Token token(FSQUERY_TOKEN_TYPE_NUMBER, tokenVal);
	return token;
}

Token FSQueryLexer::SingleQuotedString(char firstChar)
{
	char ch = firstChar;
	bool foundClosingQuote = false;
	std::string tokenVal;
	
	bool end = false;
	while (!end)
	{
		tokenVal.push_back(ch);
		Consume();
		
		if (IsAtEndOfInput())
		{
			end = true;
		}
		else
		{
			ch = GetCurrent();
			if (ch == '\'')
			{
				tokenVal.push_back(ch);
				foundClosingQuote = true;
				end = true;
				Consume();
			}
		}
	}
	
	if (!foundClosingQuote)
	{
		throw FSQueryException("FSQueryLexer: Missing closing quote");
	}
	
	Token token(FSQUERY_TOKEN_TYPE_SINGLE_QUOTED_STRING, tokenVal.substr(1, tokenVal.length() - 2));
	return token;
}

Token FSQueryLexer::IdentifierOrKeyWord(char firstChar)
{
	char ch = firstChar;
	std::string tokenVal;
	
	bool end = false;
	while (!end)
	{
		tokenVal.push_back(ch);
		Consume();
		
		if (IsAtEndOfInput())
		{
			end = true;
		}
		else
		{
			ch = GetCurrent();
			if (!(IsDigit(ch) || IsLetter(ch)))
			{
				end = true;
			}
		}
	}
	
	int tokenType = FSQUERY_TOKEN_TYPE_IDENTIFIER;
	auto keyWordIterator = s_keyWords.find(tokenVal);

	if (keyWordIterator != s_keyWords.end())
	{
		tokenType = keyWordIterator->second;
	}
	
	Token token(tokenType, tokenVal);
	return token;
}

void FSQueryLexer::ConsumeWhiteSpaces()
{
	while (!IsAtEndOfInput() && IsWhiteSpace(GetCurrent()))
	{
		Consume();
	}
}

bool FSQueryLexer::IsDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool FSQueryLexer::IsLetter(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool FSQueryLexer::IsWhiteSpace(char ch)
{
	return ch == ' ' || ch == '\t' || ch == '\n';
}

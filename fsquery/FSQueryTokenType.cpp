
#include "FSQueryTokenType.h"

std::string TokenTypeToString(int tokenType)
{
	std::string str;
	
	switch (tokenType)
	{
	case FSQUERY_TOKEN_TYPE_SELECT:
		str = "select";
		break;

	case FSQUERY_TOKEN_TYPE_FROM:
		str = "from";
		break;

	case FSQUERY_TOKEN_TYPE_WHERE:
		str = "where";
		break;

	case FSQUERY_TOKEN_TYPE_ORDER:
		str = "order";
		break;

	case FSQUERY_TOKEN_TYPE_BY:
		str = "by";
		break;

	case FSQUERY_TOKEN_TYPE_AS:
		str = "as";
		break;

	case FSQUERY_TOKEN_TYPE_RECURSIVE:
		str = "recursive";
		break;

	case FSQUERY_TOKEN_TYPE_AND:
		str = "and";
		break;

	case FSQUERY_TOKEN_TYPE_OR:
		str = "or";
		break;

	case FSQUERY_TOKEN_TYPE_TRUE:
		str = "true";
		break;

	case FSQUERY_TOKEN_TYPE_FALSE:
		str = "false";
		break;

	case FSQUERY_TOKEN_TYPE_LIKE:
		str = "like";
		break;

	case FSQUERY_TOKEN_TYPE_IDENTIFIER:
		str = "identifier";
		break;

	case FSQUERY_TOKEN_TYPE_NUMBER:
		str = "number";
		break;

	case FSQUERY_TOKEN_TYPE_SINGLE_QUOTED_STRING:
		str = "single quoted string";
		break;

	case FSQUERY_TOKEN_TYPE_COMMA:
		str = "comma";
		break;

	case FSQUERY_TOKEN_TYPE_ASTERISK:
		str = "asterisk";
		break;

	case FSQUERY_TOKEN_TYPE_DOT:
		str = "dot";
		break;

	case FSQUERY_TOKEN_TYPE_LEFT_PAREN:
		str = "left paren";
		break;

	case FSQUERY_TOKEN_TYPE_RIGHT_PAREN:
		str = "right paren";
		break;

	case FSQUERY_TOKEN_TYPE_EQUAL:
		str = "equal";
		break;

	case FSQUERY_TOKEN_TYPE_NOT_EQUAL:
		str = "not equal";
		break;

	case FSQUERY_TOKEN_TYPE_LESS_THAN:
		str = "less than";
		break;

	case FSQUERY_TOKEN_TYPE_LESS_OR_EQUAL:
		str = "less or equal";
		break;

	case FSQUERY_TOKEN_TYPE_GREATER_THAN:
		str = "greater than";
		break;

	case FSQUERY_TOKEN_TYPE_GREATER_OR_EQUAL:
		str = "greater or equal";
		break;
	}

	return str;
}

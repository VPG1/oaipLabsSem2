#include "tokentype.h"

const string &TokenType::getRegex() const
{
    return regex;
}

TokenType::ETokenType TokenType::getETokenType() const
{
    return tokenType;
}

TokenType::TokenType(TokenType::ETokenType tokenType, const string &regex) : tokenType(tokenType),
    regex(regex)
{
}

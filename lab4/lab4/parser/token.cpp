#include "token.h"


const TokenType &Token::getTokenType() const
{
    return tokenType;
}

const string &Token::getTokenText() const
{
    return tokenText;
}

const pair<size_t, size_t> &Token::getCoords() const
{
    return coords;
}

Token::Token(const TokenType &tokenType, const string &tokenText, const pair<size_t, size_t> &coords) : tokenType(tokenType),
    tokenText(tokenText),
    coords(coords)
{
}

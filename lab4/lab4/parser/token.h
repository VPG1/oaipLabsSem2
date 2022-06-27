#ifndef TOKEN_H
#define TOKEN_H
#include "tokentype.h"
#include "../my_pair/my_pair.h"
#include <cstddef>




class Token
{
    TokenType tokenType;
    string tokenText;
    pair<size_t, size_t> coords;
public:

    Token() = default;
    Token(const TokenType &tokenType, const string &tokenText, const pair<size_t, size_t> &coords);
    const TokenType &getTokenType() const;
    const string &getTokenText() const;
    const pair<size_t, size_t> &getCoords() const;
};

#endif // TOKEN_H

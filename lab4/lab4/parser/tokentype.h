#ifndef TOKENTYPE_H
#define TOKENTYPE_H
#include "my_string.h"


class TokenType
{
public:
    enum ETokenType{
        LINE_TRANSLATION,
        WHITESPACE,
        PREPROCESSOR_DIRECTIVE,
        KEY_WORD,
        IDENTIFIER,
        STRING_LITERAL,
        DOUBLE_LITERAL,
        INTEGER_LITERAL,
        OPERATOR,
        ONE_LINE_COMMENT,
        MULTI_LINE_COMMENT,
        SPECIAL_SYMBOLS,
        NUMBER_OF_TYPES
    };

private:
    ETokenType tokenType;
    string regex;

public:
    TokenType() = default;
    TokenType(ETokenType tokenType, const string &regex);


//    static TokenType TokenTypes[TokenType::NUMBER_OF_TYPES];

    ETokenType getETokenType() const;
    const string &getRegex() const;
};

#endif // TOKENTYPE_H

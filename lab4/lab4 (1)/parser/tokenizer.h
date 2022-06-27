#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "../my_vector/my_vector.h"
#include "token.h"
#include <QDebug>
#include <regex>



class Tokenizer
{
    TokenType TokenTypes[TokenType::NUMBER_OF_TYPES] = {
        {TokenType::LINE_TRANSLATION, "\n"},
        {TokenType::WHITESPACE, "[\t ]"},
        {TokenType::PREPROCESSOR_DIRECTIVE, "#[^\n]*"},// ??
        {TokenType::KEY_WORD, "\\b(return|asm|auto|break|case|catch|class|const_cast|continue|default|delete|do|dynamic_cast|(else if)|else|if|enum|explicit|export|extern|false|for|friend|goto|inline|"
         "mutable|namespace|new|operator|private|protected|public|register|reinterpret_cast|return|sizeof|static_cast|struct|switch|template|this|throw|true|try|typedef|typeid|typename|union|using|virtual|wchar_t|while)\\b"},
        {TokenType::IDENTIFIER, "[a-zA-Z_]\\w*(\\s*<\\s*\\w+(\\s*<\\s*\\w+(\\s*,\\s*\\w+)*\\s*>\\s*)?(\\s*,\\s*\\w+(\\s*<\\s*\\w+(\\s*,\\s*\\w+)*\\s*>\\s*)?)*\\s*>\\s*)?"
         "((::)[a-zA-Z_]\\w*(\\s*<\\s*\\w+(\\s*<\\s*\\w+(\\s*,\\s*\\w+)*\\s*>\\s*)?(\\s*,\\s*\\w+(\\s*<\\s*\\w+(\\s*,\\s*\\w+)*\\s*>\\s*)?)*\\s*>\\s*)?)?"},
        {TokenType::STRING_LITERAL, R"("(\\"|[^\"])*")"},
        {TokenType::DOUBLE_LITERAL, "-?\\d+\\.\\d+"},
        {TokenType::INTEGER_LITERAL, "-?\\d+"},
        {TokenType::OPERATOR, R"(((\+\+)|(--)|(==)|(=)|(\*=)|(\/=)|(%=)|(\+=)|(-=)|(<<=)|(>>=)|(&=)|(\|=)|(\^=)))"},
        {TokenType::ONE_LINE_COMMENT, "^\\/\\/[^\n]*"},
        {TokenType::MULTI_LINE_COMMENT, "\\/\\*[\\s\\S]*\\*\\/"},
        {TokenType::SPECIAL_SYMBOLS, "\\{|\\}|\\,|\\||\\[|\\]|\\(|\\)|\\+|\\-|\\/|\\%|\\*|\\.|\\?|\\<|\\=|\\>|\\!|\\&|\\#|\\;|\\'|\\'|\\:"}
    };




    string code;
    size_t codeSize = code.size();
    size_t pos = 0;
    size_t posInLine = 1;
    size_t numOfLine = 1;
    vector<Token> tokens;

public:
    Tokenizer() = delete;
    Tokenizer(const string &code);

    vector<Token> tokenize();


    bool nextToken();
};

#endif

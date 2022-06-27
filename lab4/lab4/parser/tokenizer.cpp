#include "tokenizer.h"



Tokenizer::Tokenizer(const string &code) : code(code)
{
}

vector<Token> Tokenizer::tokenize(){
    while(nextToken());
    return tokens;
}

bool Tokenizer::nextToken(){

    if(pos >= codeSize){
        return false;
    }

    for(size_t i = 0; i < TokenType::NUMBER_OF_TYPES; ++i){;

        std::cmatch res;
        if(std::regex_search(code.c_str(), res, std::regex(("^" + TokenTypes[i].getRegex()).c_str()))){
            if(i != TokenType::WHITESPACE && i != TokenType::LINE_TRANSLATION){
                tokens.push_back(Token(TokenTypes[i], res[0].str().c_str(), pair<size_t, size_t>(numOfLine, posInLine)));
                qDebug() << res[0].str().c_str() << QString(" (%1, %2)").arg(numOfLine).arg(posInLine) << i;
            }


            pos += res[0].str().size();
            posInLine += res[0].str().size();
            code = res.suffix().str().c_str();

            if(res[0].str() == "\n"){
                posInLine = 1;
                ++numOfLine;
            }

            return true;
        }
    }
    return false;
}

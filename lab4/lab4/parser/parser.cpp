#include "parser.h"
#include <regex>


Parser::Parser()
{

}

Parser::Parser(const vector<Token> &tokens)
    : tokens(tokens)
{

}



void Parser::addVar(Type type, string identifier, pair<size_t, size_t> pos, std::optional<string> value = std::nullopt)
{
    auto findingIt = vars.find(type.getTypeString());

    if(findingIt != vars.end()){
        findingIt->second.emplace_back(type, identifier, pos, numOfNonCloseBracket != 0, value);
    }
    else{
        vars.emplace(type.getTypeString(), vector<Variable>(1, Variable(type, identifier, pos, numOfNonCloseBracket != 0, value)));
    }
}

void Parser::addFunc(Type type, string identifier, vector<Type> argsTypes, pair<size_t, size_t> pos)
{
    auto findingIt = funcs.find(type.getTypeString() + " " + identifier + "(...)");

    if(findingIt == funcs.end()){
        funcs.emplace(type.getTypeString() + " " + identifier + "(...)",
                      vector<Function>(1, Function(type, identifier, argsTypes, pos)));
    }
    else{
        for(auto el : findingIt->second){
            bool mustAdd = false;

            if(argsTypes.size() != el.getArgs().size()){
                mustAdd = true;
                continue;
            }

            for(size_t i = 0; i < argsTypes.size(); ++i){
                if(argsTypes[i].getTypeString() != el.getArgs()[i].getTypeString()){
                    mustAdd = true;
                    break;
                }
                else{
                    mustAdd = false;
                }
            }

            if(!mustAdd){
                return;
            }
        }
        findingIt->second.emplace_back(type, identifier, argsTypes, pos);


    }
}

void Parser::addLogicalError(const Token &token)
{
    if(token.getTokenText() == "true" || token.getTokenText() == "false"){
        coordsOfErrors.push_back(token.getCoords());
        return;
    }

    for(auto el1 : vars){
        for(auto el2 : el1.second){
            if((el2.getName() == token.getTokenText()) && (el2.getType().getIsConst())){
                coordsOfErrors.push_back(token.getCoords());
                return;
            }
        }
    }
}



const vector<size_t> &Parser::getDepthOfBranching() const
{
    return depthOfBranching;
}

const vector<pair<size_t, size_t> > &Parser::getCoordsOfErrors() const
{
    return coordsOfErrors;
}

std::optional<Type> Parser::expectedType(vector<Token>::iterator &currentIt)
{
    if(currentIt == tokens.end()){
        return std::nullopt;
    }
    if(currentIt->getTokenType().getETokenType() != TokenType::IDENTIFIER){
        return std::nullopt;
    }


    if(currentIt->getTokenType().getETokenType() == TokenType::IDENTIFIER || Type::isQualifacator(currentIt->getTokenText()))
    {
        Type type;
        do{
            type << currentIt->getTokenText();
            if(!Type::isQualifacator(currentIt->getTokenText())){
                ++currentIt;
                if(currentIt == tokens.end()){
                    return type;
                }

                while(Type::isPointerOrRef(currentIt->getTokenText())){
                    type << currentIt->getTokenText();
                    ++currentIt;
                    if(currentIt == tokens.end()){
                        return type;
                    }
                }
                return type;
            }
            ++currentIt;
            if(currentIt == tokens.end()){
                return type;
            }

        }while(currentIt->getTokenType().getETokenType() == TokenType::IDENTIFIER ||
               Type::isQualifacator(currentIt->getTokenText()) ||
               Type::isPointerOrRef(currentIt->getTokenText()));
        return std::optional<Type>(type);
    }

    return std::nullopt;
}

string Parser::expectedIdentifier(vector<Token>::iterator &currentIt, const string &name)
{
    if(currentIt == tokens.end()){
        return "";
    }
    if(currentIt->getTokenType().getETokenType() != TokenType::IDENTIFIER){
        return "";
    }
    if(currentIt->getTokenText() != name && !name.empty()){
        return "";
    }
    ++currentIt;

    return (currentIt - 1)->getTokenText();

}

string Parser::expectedSpecialSymbol(vector<Token>::iterator &currentIt, const string &str)
{
    if(currentIt == tokens.end()){
        return "";
    }
    if(currentIt->getTokenType().getETokenType() != TokenType::SPECIAL_SYMBOLS){
        return "";
    }
    if(currentIt->getTokenText() != str && !str.empty()){
        return "";
    }

    ++currentIt;

    return (currentIt - 1)->getTokenText();
}

bool Parser::expectedChangingOperator(vector<Token>::iterator &currentIt, const string &str)
{
    if(currentIt == tokens.end()){
        return false;
    }
    if((currentIt->getTokenType().getETokenType() != TokenType::OPERATOR)){
        return false;
    }
    else if(currentIt->getTokenText() == "=="){
        return false;
    }
    if(currentIt->getTokenText() != str && !str.empty()){
        return false;
    }

    ++currentIt;

    return true;
}

string Parser::expectedKeyWord(vector<Token>::iterator &currentIt, const string &str)
{
    if(currentIt == tokens.end()){
        return "";
    }
    if(currentIt->getTokenType().getETokenType() != TokenType::KEY_WORD){
        return "";
    }
    if(currentIt->getTokenText() != str && !str.empty()){
        return "";
    }

    ++currentIt;

    return (currentIt - 1)->getTokenText();
}

bool Parser::isChangingVariable(const string &str)
{
    return str != "==";
}



void Parser::parse()
{
    for(auto it = tokens.begin(); it != tokens.end(); ++it){


        auto savePosition = it;
        string keyWord = expectedKeyWord(it);
        if(it == tokens.end()){
            break;
        }
        if(it->getTokenText() != "class" && it->getTokenText() != "struct" && !keyWord.empty()){
            continue;
        }
        it = savePosition;

        if(it->getTokenText() == "class" || it->getTokenText() == "struct"){
            ++it;

            expectedIdentifier(it);
            expectedSpecialSymbol(it, "{");

            if(it == tokens.end()){
                break;
            }
        }

        if(it->getTokenText() == "{"){
            ++numOfNonCloseBracket;
        }
        else if(it->getTokenText() == "}"){
            ++it;

            if(it == tokens.end()){
                break;
            }
            else if(expectedSpecialSymbol(it, ";").empty()){
                --numOfNonCloseBracket;
            }

            if(it == tokens.end()){
                break;
            }
        }

        if((it->getTokenText() == "++") || (it->getTokenText() == "--")){
            ++it;
            if(it == tokens.end()){
                break;
            }
            if(!expectedIdentifier(it).empty()){
                coordsOfChanging.push_back((it - 1)->getCoords());
                continue;
            }
            else{
                --it;
            }

        }

        auto tempIt = it;

        if(!expectedIdentifier(it).empty()){
            if(!expectedSpecialSymbol(it, "[").empty()){
                while(expectedSpecialSymbol(it, "]").empty()){
                    if(it == tokens.end()){
                        break;
                    }
                    ++it;
                }
                if(it == tokens.end()){
                    break;
                }
            }
            if(expectedChangingOperator(it)){
                coordsOfChanging.push_back(it->getCoords());
            }
        }

        it = tempIt;



        pair<size_t, size_t> pos(it->getCoords()); // позиция потенциальной функции или перменной
        std::optional<Type> type = expectedType(it);
        if(type.has_value()){
            qDebug() << it->getTokenText().c_str();
            string identifier = expectedIdentifier(it);
            if(!identifier.empty()){
                qDebug() << it->getTokenText().c_str();
                string specialSymbol = expectedSpecialSymbol(it);
                if(!specialSymbol.empty()){
                    if(specialSymbol == "["){
                        while(expectedSpecialSymbol(it, ";").empty()){
                            if(it == tokens.end()){
                                break;
                            }
                            ++it;
                        }

                        ++numOfArray;

                        if(it == tokens.end()){
                            break;
                        }

                    }
                    else if(specialSymbol == ";"){ // переменная
                        // добовляем переменную
                        addVar(type.value(), identifier, pos);
                    }
//                    else if(specialSymbol == "="){ // переменная
//                        bool tokensEnded = false;
//                        while(expectedSpecialSymbol(it, ";").empty()){
//                            if(it == tokens.end()){
//                                tokensEnded = true;
//                                break;
//                            }
//                            ++it;
//                        }
//                        if(tokensEnded){
//                            break;
//                        }

//                        // добовляем перемнную
//                        addVar(type.value(), identifier, pos);
//                    }
                    else if(specialSymbol == "("){ // функция или перменная
                        std::optional<Type> firstArgType;
                        string firstArgIdentifier;

                        if(!expectedSpecialSymbol(it, ")").empty()){ // функция
                            // добовляем функцию
                            addFunc(type.value(), identifier, vector<Type>(), pos);
                        }
                        else if((firstArgType = expectedType(it)).has_value() && !(firstArgIdentifier = expectedIdentifier(it)).empty() &&
                                (!expectedSpecialSymbol(it, ",").empty() || !expectedSpecialSymbol(it, ")").empty())){ // функция
                            it -= firstArgType->getNumOfTypeTokens() + 2;

                            vector<Type> argsTypes;

                            bool tokensEnded = false;
                            while(expectedSpecialSymbol(it, ")").empty()){
                                if(it == tokens.end()){
                                    tokensEnded = true;
                                    break;
                                }
                                std::optional<Type> argType = expectedType(it);
                                string argIdentifier = expectedIdentifier(it);
                                if(argType.has_value() && !argIdentifier.empty()){
                                    argsTypes.push_back(argType.value());
                                }
                                else{
                                    ++it;
                                }
                            }

                            if(tokensEnded){
                                break;
                            }

                            // добовляем функцию
                            addFunc(type.value(), identifier, argsTypes, pos);
                        }
                        else{ // переменная
                            bool tokensEnded = false;
                            while(expectedSpecialSymbol(it, ";").empty()){
                                if(it == tokens.end()){
                                    tokensEnded = true;
                                    break;
                                }
                                ++it;
                            }
                            if(tokensEnded){
                                break;
                            }

                            // добовляем переменную
                            addVar(type.value(), identifier, pos);
                        }
                    }
                }
                else if(it != tokens.end() && it->getTokenText() == "="){
                    string temp;
                    bool tokensEnded = false;
                    while(expectedSpecialSymbol(it, ";").empty()){
                        if(it->getTokenText() != "=" && it->getTokenText() != ";"){
                            temp += it->getTokenText().c_str();
                        }
                        if(it == tokens.end()){
                            tokensEnded = true;
                            break;
                        }
                        ++it;
                    }
                    if(tokensEnded){
                        break;
                    }

                    // добовляем перемнную
                    if(std::regex_match(temp.c_str(), std::regex(R"((-?\d+(\.\d+)?)|(true)|(false))"))){
                        addVar(type.value(), identifier, pos, temp);

                    }
                    else{
                        addVar(type.value(), identifier, pos);
                    }
                }
            }
            --it;
        }
    }

    parseBranchingDepth(getBranchTokenList());

    parseLogigalErrors();
}

vector<Token> Parser::getBranchTokenList()
{
    vector<Token> branchTokenList;
    int numOfBrackets = 0;
    std::stack<int> stack;
    bool nextBracketIsBranch = false;
    for(auto it = tokens.begin(); it != tokens.end(); ++it){
        if(it->getTokenText() == "if" || it->getTokenText() == "else if" || it->getTokenText() == "else"){
            branchTokenList.push_back(*it);

            nextBracketIsBranch = true;
        }
        else if(it->getTokenText() == "{"){
            if(nextBracketIsBranch){
                branchTokenList.push_back(*it);

                stack.push(numOfBrackets);
                nextBracketIsBranch = false;
            }
            ++numOfBrackets;
        }
        else if(it->getTokenText() == "}"){
            --numOfBrackets;
            if(!stack.empty() && (stack.top() == numOfBrackets)){
                branchTokenList.push_back(*it);

                stack.pop();
            }
        }
    }

    return branchTokenList;
}



//void foo(){
//    if(true){
//        if(true){
//            if(true){

//            }
//        }
//        if(true){
//            if(true){

//            }
//            else if(true){

//            }
//            else{
//                if(true){

//                }
//            }
//        }
//        else{

//        }

//    }
//    else if(true){

//    }
//    else{

//    }
//}

void Parser::parseBranchingDepth(vector<Token> &&tokens){
    int numOfBrackets = 0;
    bool b = false;
    for(auto it = tokens.begin(); it != tokens.end(); ++it){
        if(it->getTokenText() == "{"){
            ++numOfBrackets;
            b = true;
        }
        else if(it->getTokenText() == "}"){
            if(b /*&& (numOfBrackets - 1) != 0*/){
                depthOfBranching.push_back(numOfBrackets);
                b = false;
            }
            --numOfBrackets;
        }
    }
}

void Parser::parseLogigalErrors()
{
    Token temp;
    for(auto it = tokens.begin(); it != tokens.end(); ++it){
        if(!expectedKeyWord(it, "while").empty()){
            if(!expectedSpecialSymbol(it, "(").empty()){
                if(it == tokens.end()){
                    break;
                }
                temp = *it;
                ++it;

                if(!expectedSpecialSymbol(it, ")").empty()){
                    addLogicalError(temp);
                }
            }
        }
        else if(!expectedKeyWord(it, "if").empty()){
            if(!expectedSpecialSymbol(it, "(").empty()){
                if(it == tokens.end()){
                    break;
                }
                temp = *it;
                ++it;

                if(!expectedSpecialSymbol(it, ")").empty()){
                    addLogicalError(temp);
                }
            }
        }
        else if(!expectedKeyWord(it, "else if").empty()){
            if(!expectedSpecialSymbol(it, "(").empty()){
                if(it == tokens.end()){
                    break;
                }
                temp = *it;
                ++it;

                if(!expectedSpecialSymbol(it, ")").empty()){
                    addLogicalError(temp);
                }
            }
        }
        else if(!expectedKeyWord(it, "for").empty()){
            if(!expectedSpecialSymbol(it, "(").empty()){
                while(expectedSpecialSymbol(it, ";").empty()){
                    if(it == tokens.end()){
                        break;
                    }
                    ++it;
                }
                if(it == tokens.end()){
                    break;
                }

                temp = *it;
                ++it;

                if(!expectedSpecialSymbol(it, ";").empty()){
                    addLogicalError(temp);
                }
            }
        }
    }
}





const std::map<string, vector<Variable>> &Parser::getVars() const
{
    return vars;
}

const std::map<string, vector<Function> > &Parser::getFuncs() const
{
    return funcs;
}

int Parser::getNumOfArray() const
{
    return numOfArray;
}

const vector<pair<size_t, size_t> > &Parser::getCoordsOfChanging() const
{
    return coordsOfChanging;
}

#ifndef PARSER_H
#define PARSER_H
#include <map>
#include <set>
#include "my_string.h"
#include "my_vector.h"
#include "token.h"
#include "tokenizer.h"
#include "type.h"
#include "my_pair.h"
#include "function.h"
#include <optional>
#include "variable.h"
#include <stack>

class Parser
{
    vector<Token> tokens;
    std::map<string, vector<Variable>> vars;
    std::map<string, vector<Function>> funcs;
    vector<pair<size_t, size_t>> coordsOfChanging;
    vector<pair<size_t, size_t>> coordsOfErrors;
    vector<size_t> depthOfBranching;
    int numOfNonCloseBracket = 0; // количество незакрытых фигурных скобок
    int numOfArray = 0;


    std::optional<Type> expectedType(vector<Token>::iterator &currentIt);
    string expectedIdentifier(vector<Token>::iterator &currentIt, const string &name = "");
    string epxectedArr(vector<Token>::iterator &currentIt, const string &name = "");
    string expectedSpecialSymbol(vector<Token>::iterator &currentIt, const string &str = "");
    bool expectedChangingOperator(vector<Token>::iterator &currentIt, const string &str = "");
    string expectedKeyWord(vector<Token>::iterator &currentIt, const string &str = "");
    bool isChangingVariable(const string &str);

    void addVar(Type type, string identifier, pair<size_t, size_t> pos, std::optional<string> name);
    void addFunc(Type type, string identifier, vector<Type> argsTypes, pair<size_t, size_t> pos);
    void addLogicalError(const Token &token);

public:
    Parser();
    Parser(const vector<Token> &tokens);

    void parse();
    vector<Token> getBranchTokenList();
    void parseBranchingDepth(vector<Token> &&tokens);
    void parseLogigalErrors();

    const std::map<string, vector<Variable>> &getVars() const;
    const std::map<string, vector<Function>> &getFuncs() const;
    int getNumOfArray() const;
    const vector<pair<size_t, size_t> > &getCoordsOfChanging() const;
    const vector<size_t> &getDepthOfBranching() const;
    const vector<pair<size_t, size_t> > &getCoordsOfErrors() const;
};

#endif // PARSER_H

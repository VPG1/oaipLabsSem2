#ifndef FUNCTION_H
#define FUNCTION_H
#include "type.h"
#include "token.h"
#include "../my_vector/my_vector.h"
#include "../my_pair/my_pair.h"

class Function
{
    Type funcType;
    string identifier;
    vector<Type> args;
    pair<size_t, size_t> pos;
    vector<Token> implemintation;

public:
    Function() = delete;
    Function(const Type &funcType, const string &identifier,
             const vector<Type> &args, const pair<size_t, size_t> &pos);
    Function(const Type &funcType, const string &identifier, const vector<Type> &args, const pair<size_t, size_t> &pos, const vector<Token> &implemintation);

    string getFuncString();
    const pair<size_t, size_t> &getPos() const;
    const vector<Type> &getArgs() const;
};

#endif // FUNCTION_H

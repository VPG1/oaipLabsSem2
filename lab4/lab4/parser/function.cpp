#include "function.h"
#include "../my_string/my_string.h"

const pair<size_t, size_t> &Function::getPos() const
{
    return pos;
}

const vector<Type> &Function::getArgs() const
{
    return args;
}

Function::Function(const Type &funcType, const string &identifier,
                   const vector<Type> &args, const pair<size_t, size_t> &pos) :
    funcType(funcType), identifier(identifier),
    args(args), pos(pos)
{}

string Function::getFuncString()
{
    string res;

    res += funcType.getTypeString() + " " + identifier;
    res += "(";
    for(int i = 0; i < (int)args.size() - 1; ++i){
        res += args[i].getTypeString() + ", ";
    }
    if(!args.empty())
        res += args[args.size() - 1].getTypeString();
    res += ");";

    return res;
}

Function::Function(const Type &funcType, const string &identifier, const vector<Type> &args,
                   const pair<size_t, size_t> &pos, const vector<Token> &implemintation) :
    funcType(funcType),
    identifier(identifier),
    args(args),
    pos(pos),
    implemintation(implemintation)
{}

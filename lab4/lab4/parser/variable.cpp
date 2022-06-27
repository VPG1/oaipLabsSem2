#include "variable.h"

const string &Variable::getName() const
{
    return name;
}

const pair<size_t, size_t> &Variable::getPos() const
{
    return pos;
}

bool Variable::getIsLocal() const
{
    return isLocal;
}

std::optional<string> Variable::getValue() const
{
    return value;
}

const Type &Variable::getType() const
{
    return type;
}

Variable::Variable()
{

}

Variable::Variable(const Type &type, const string &name, const pair<size_t, size_t> &pos) : type(type),
    name(name),
    pos(pos)
{}

Variable::Variable(const Type &type, const string &name, const pair<size_t, size_t> &pos, bool isLocal) : type(type),
    name(name),
    pos(pos),
    isLocal(isLocal)
{}

Variable::Variable(const Type &type, const string &name, const pair<size_t, size_t> &pos, bool isLocal, std::optional<string> value) : type(type),
    name(name),
    pos(pos),
    isLocal(isLocal),
    value(std::move(value))
{}

#ifndef VARIABLE_H
#define VARIABLE_H
#include "type.h"
#include "my_string.h"
#include "my_pair.h"
#include <optional>

class Variable
{
    Type type;
    string name;
    pair<size_t, size_t> pos;
    bool isLocal;
    std::optional<string> value = std::nullopt;

public:
    Variable();
    Variable(const Type &type, const string &name, const pair<size_t, size_t> &pos);
    Variable(const Type &type, const string &name, const pair<size_t, size_t> &pos, bool isLocal);
    Variable(const Type &type, const string &name, const pair<size_t, size_t> &pos, bool isLocal, std::optional<string> value);
    const string &getName() const;
    const pair<size_t, size_t> &getPos() const;
    bool getIsLocal() const;
    std::optional<string> getValue() const;
    const Type &getType() const;
};

#endif // VARIABLE_H


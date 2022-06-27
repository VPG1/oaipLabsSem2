#include "type.h"

size_t Type::getNumOfTypeTokens() const
{
    return numOfTypeTokens;
}

bool Type::getIsConst() const
{
    return isConst;
}

Type::Type()
    : type("int")
{
}

Type &Type::operator<<(const string &str)
{
    if(str == "const")         isConst = true;
    else if(str == "volatile") isVolatile = true;
    else if(str == "unsigned") isUnsigned = true;
    else if(str == "short")    isShort = true;
    else if(str == "long")     ++numOfLongs;
    else if(str == "*")        ++stars;
    else if(str == "&")        ++refs;
    else                       type = str;

    ++numOfTypeTokens;

    return *this;
}

string Type::getTypeString() const
{
    string res;

    if(isConst) res += "const ";
    if(isVolatile) res += "volatile ";
    if(isUnsigned && (type == "int" || type == "char")) res += "unsigned ";
    else if((type == "int") || (type == "char")) res += "signed ";
    if(isShort) res += "short ";
    else if(numOfLongs != 0){
        int temp = numOfLongs;
        while(temp--) res += "long ";
    }

    res += type;

    for(int i = 0; i < stars; ++i){
        res += "*";
    }
    for(int i = 0; i < refs; ++i){
        res += "&";
    }

    return res;
}

string Type::getOnlyType()
{
    return type;
}

bool Type::isPrimitiveType(const string &str)
{
    return (str == "void") || (str == "char") || (str == "bool") ||
            (str == "int") || (str == "float") || (str == "double");
}

bool Type::isQualifacator(const string &str)
{
    return (str == "const") || (str == "volatile") || (str == "signed") ||
            (str == "unsigned") || (str == "short") || (str == "long");
}

bool Type::isPointerOrRef(const string &str)
{
    return (str == "*") || (str == "&");
}

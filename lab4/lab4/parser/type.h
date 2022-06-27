#ifndef TYPE_H
#define TYPE_H
#include "../my_vector/my_vector.h"
#include "../my_string/my_string.h"

class Type
{
//    enum IdentifierOfTypes{
//        VOID,
//        CHAR,
//        BOOL,
//        INT,
//        FLOAT,
//        DOUBLE
//    };

    size_t numOfTypeTokens = 0;
    string type;
//    IdentifierOfTypes ident;
    bool isConst = false;
    bool isVolatile = false;
    bool isUnsigned = false;
    bool isShort = false;
    int numOfLongs = 0;
    int stars = 0;
    int refs = 0;


public:
    Type();

    Type &operator<<(const string &str);
    string getTypeString() const;
    string getOnlyType();

    static bool isPrimitiveType(const string &str);
    static bool isQualifacator(const string &str);
    static bool isPointerOrRef(const string &str);
    size_t getNumOfTypeTokens() const;
    bool getIsConst() const;
};

#endif // TYPE_H

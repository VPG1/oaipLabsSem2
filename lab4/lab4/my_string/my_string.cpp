#include "my_string.h"

string::string()
    : m_str(new char[1])
{
    m_str[0] = '\0';
}

string::string(size_t count, char ch)
{
    m_size = count;
    m_str = new char[count + 1];
    my_memset(m_str, ch, count);
    m_str[count] = '\0';
}

string::string(const char *str)
{
//    if(!str){
//        m_size = 0;
//        m_str = nullptr;
//        return;
//    }
    m_size = my_strlen(str);
    m_str = new char[m_size + 1];
    my_strcpy(m_str, str);
}
string &string::operator=(const char *str){
//    if(!str){
//        m_size = 0;
//        m_str = nullptr;
//        return *this;
//    }
    m_size = my_strlen(str);
    m_str = new char[m_size + 1];
    my_strcpy(m_str, str);

    return *this;
}

string::string(const string &other)
{
    m_size = other.m_size;
    m_str = new char[other.m_size + 1];

    my_strcpy(m_str, other.m_str);
}

string &string::operator=(const string &other)
{
    if(this == &other)
        return *this;

    delete[] m_str;

    m_size = other.m_size;

    m_str = new char[other.m_size + 1];
    my_strcpy(m_str, other.m_str);
//    if(other.m_str){
//        m_str = new char[other.m_size + 1];
//        cstr::my_strcpy(m_str, other.m_str);
//    }
//    else
//        m_str = nullptr;

    return *this;
}

string::string(string &&other)
{
    m_size = other.m_size;
    m_str = other.m_str;

    other.m_size = 0;
    other.m_str = nullptr;
}

string &string::operator=(string &&other){
    if(this == &other)
        return *this;

    m_size = other.m_size;
    m_str = other.m_str;

    other.m_size = 0;
    other.m_str = new char[1];
    other.m_str[0] = '\0';

    return *this;
}

string::~string()
{
//    char[m_size + 1] a = m_str;
    delete[] m_str;
}

char &string::operator[](int i)
{
    return m_str[i];
}
const char &string::operator[](int i) const{
    return m_str[i];
}

size_t string::size() const
{
    return m_size;
}

string string::substr(size_t pos, size_t count)
{
    string result;
    result.m_str = new char[count + 1 - pos];

    char *str = m_str;
    while(pos) ++str, --pos;

    my_memcpy(result.m_str, str, count);
    result.m_str[count - pos] = '\0';

    return result;
}

char *string::c_str() const
{
    return m_str;
}

bool string::empty() const
{
    return m_size == 0;
}

//void string::erase(const_iterator first, const_iterator last)
//{
//    int decrementation = std::distance(first, last);

//    char *newStr = new char[m_size - decrementation + 1];

//    int i = 0;
//    for(auto it = begin(); it != first; ++it, ++i){
//        newStr[i] = *it;
//    }
//    for(auto it = last; it != end(); ++it, ++i){
//        newStr[i] = *it;
//    }
//    newStr[i] = '\0';

//    delete[] m_str;
//    m_str = newStr;

////    if(m_size - decrementation){
////        char *newStr = new char[m_size - decrementation + 1];

////        int i = 0;
////        for(auto it = begin(); it != first; ++it, ++i){
////            newStr[i] = *it;
////        }
////        for(auto it = last; it != end(); ++it, ++i){
////            newStr[i] = *it;
////        }
////        newStr[i] = '\0';

////        delete[] m_str;
////        m_str = newStr;
////    }
////    else{
////        delete[] m_str;
////        m_str = nullptr;
////    }
//    m_size -= decrementation;
//}



string &string::operator+=(const string &rhs)
{
    m_size += rhs.m_size;
    char *result = new char[m_size + 1];
    my_strcpy(result, m_str);
    my_strcat(result, rhs.m_str);
    delete[] m_str;
    m_str = result;

    return *this;
}

//string operator+(const string &lhs, const string &rhs){
//    char *result;
//    result = new char[lhs.m_size + rhs.m_size + 1];

////    if(lhs.m_str || rhs.m_str){
////        int temp = lhs.m_size + rhs.m_size + 1;
////        result = new char[lhs.m_size + rhs.m_size + 1];
////        if(lhs.m_str){
////            cstr::my_strcpy(result, lhs.m_str);
////            if(rhs.m_str)
////                cstr::my_strcat(result, rhs.m_str);
////        }
////        else if(rhs.m_str)
////            cstr::my_strcpy(result, rhs.m_str);
////    }
////    else
////        result = nullptr;

//    cstr::my_strcpy(result, lhs.m_str);
//    cstr::my_strcat(result, rhs.m_str);


//    return string(result);
//}

//std::ostream &operator <<(std::ostream &out, const string &str){
//    return out << str.m_str;
//}

//bool operator<(const string &lhs, const string &rhs){
////    bool res;
////    for(auto lit = lhs.begin(), rit = rhs.begin();
////        lit != lhs.end() && rit != rhs.end();
////        ++lit, ++rit)
////    {
//////        if()
//////        res = ;
////    }
//    return cstr::my_strcmp(lhs.m_str, rhs.m_str) < 0;
//}

//bool operator==(const string &lhs, const string &rhs){
//    return cstr::my_strcmp(lhs.m_str, rhs.m_str) == 0;
//}


//bool operator!=(const string &lhs, const string &rhs){
//    return cstr::my_strcmp(lhs.m_str, rhs.m_str) != 0;
//}

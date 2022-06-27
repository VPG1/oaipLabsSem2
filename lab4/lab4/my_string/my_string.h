#ifndef MY_STRING_H
#define MY_STRING_H

#include "my_string_global.h"
#include "../my_func/my_func.h"

#include <iostream>

class MY_STRING_EXPORT string
{
    char *m_str;
    size_t m_size = 0;

//    template<class Iter>
//    struct common_iterator{
//        friend class string;

////        using iterator_type = typename std::conditional<IsConst, const T, T>::type;
//        using iterator_type = Iter;
//        using iterator_category = std::random_access_iterator_tag;
//        using value_type = iterator_type;
//        using reference = iterator_type&;
//        using pointer = iterator_type*;
//        using difference_type = std::ptrdiff_t;

//    private:
//        pointer ptr;
//        common_iterator(pointer ptr) : ptr(ptr){}
//    public:
//        common_iterator(const common_iterator &) = default;
//        common_iterator &operator=(const common_iterator &) = default;

//        operator common_iterator<const Iter>() const{
//            return common_iterator<const Iter>(ptr);
//        }


//        reference operator *(){
//            return *ptr;
//        }

//        pointer operator->(){
//            return ptr;
//        }

//        common_iterator &operator++(){
//            ++ptr;
//            return *this;
//        }

//        common_iterator operator++(int){
//            common_iterator temp = *this;
//            ++ptr;
//            return temp;

//        }

//        common_iterator &operator--(){
//            --ptr;
//            return *this;
//        }
//        common_iterator operator--(int){
//            common_iterator temp = *this;
//            --ptr;
//            return temp;
//        }

//        common_iterator operator+=(int n){
//            ptr += n;
//            return *this;
//        }
//        common_iterator operator-=(int n){
//            ptr -= n;
//            return *this;
//        }



//        friend common_iterator operator+(std::size_t n, const common_iterator &it){
//            return n + it;
//        }
//        friend common_iterator operator+(const common_iterator &it, std::size_t n){
//            return it.ptr + n;
//        }
//        friend common_iterator operator-(const common_iterator &it, std::size_t n){
//            return it.ptr - n;
//        }

//        friend int operator-(const common_iterator &leftIt,
//                                         const common_iterator &rightIt)
//        {
//            return leftIt.ptr - rightIt.ptr;
//        }


//        friend bool operator==(const common_iterator &leftIt, const common_iterator &rightIt){
//            return leftIt.ptr == rightIt.ptr;
//        }
//        friend bool operator!=(const common_iterator &leftIt, const common_iterator &rightIt){
//            return leftIt.ptr != rightIt.ptr;
//        }
//        friend bool operator>(const common_iterator &leftIt, const common_iterator &rightIt){
//            return leftIt.ptr > rightIt.ptr;
//        }
//        friend bool operator<(const common_iterator &leftIt, const common_iterator &rightIt){
//            return leftIt.ptr < rightIt.ptr;
//        }
//        friend bool operator>=(const common_iterator &leftIt, const common_iterator &rightIt){
//            return leftIt.ptr >= rightIt.ptr;
//        }
//        friend bool operator<=(const common_iterator &leftIt, const common_iterator &rightIt){
//            return leftIt.ptr <= rightIt.ptr;
//        }

//    };

public:
//    using iterator = common_iterator<char>;
//    using const_iterator = common_iterator<const char>;
//    using reverse_iterator = std::reverse_iterator<iterator>;
//    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

//    iterator begin(){
//        return iterator(m_str);
//    }
//    const_iterator begin() const{
//        return const_iterator(m_str);
//    }

//    const_iterator cbegin() const{
//        return const_iterator(m_str);
//    }

//    iterator end(){
//        return iterator(m_str + m_size);
//    }
//    const_iterator end() const{
//        return const_iterator(m_str + m_size);
//    }

//    const_iterator cend(){
//        return const_iterator(m_str + m_size);
//    }


//    reverse_iterator rbegin(){
//        return reverse_iterator(end());
//    }
//    const_reverse_iterator rbegin() const{
//        return const_reverse_iterator(end());
//    }

//    const_reverse_iterator crbegin() const{
//        return const_reverse_iterator(end());
//    }

//    reverse_iterator rend(){
//        return reverse_iterator(begin());
//    }
//    const_reverse_iterator rend() const{
//        return const_reverse_iterator(--begin());
//    }

//    const_reverse_iterator crend() const{
//        return const_reverse_iterator(--begin());
//    }


    string();
    string(size_t count, char ch);
    string(const char *str);
    string &operator=(const char *str);
    string(const string &other);
    string &operator=(const string &other);
    string(string &&string);
    string &operator=(string &&other);
    ~string();

    char &operator[](int i);
    const char &operator[](int i) const;
    size_t size() const;
    string substr(size_t pos, size_t count);

    char *c_str() const;
    bool empty() const;


//    void erase(const_iterator first, const_iterator last);


    string &operator+=(const string &rhs);

    friend string operator+(const string &lhs, const string &rhs){
        char *result;
        result = new char[lhs.m_size + rhs.m_size + 1];


        my_strcpy(result, lhs.m_str);
        my_strcat(result, rhs.m_str);

        return string(result);
    }
    friend std::ostream &operator <<(std::ostream &out, const string &str){
        return out << str.m_str;
    }
    friend std::istream &operator >>(std::istream &in, const string &str){
        return in >> str.m_str;
    }
    friend bool operator<(const string &lhs, const string &rhs){
        return my_strcmp(lhs.m_str, rhs.m_str) < 0;
    }
    friend bool operator==(const string &lhs, const string &rhs){
        return my_strcmp(lhs.m_str, rhs.m_str) == 0;
    }

    friend bool operator!=(const string &lhs, const string &rhs){
        return my_strcmp(lhs.m_str, rhs.m_str) != 0;
    }

};
#endif // MY_STRING_H

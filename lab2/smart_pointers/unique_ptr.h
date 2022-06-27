#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include "move_and_forward.h"
#include <iostream>


template<class T>
class shared_ptr;

template<typename T>
class unique_ptr{
private:
    T *m_ptr = nullptr;
public:
    unique_ptr() : m_ptr(nullptr){}

    explicit unique_ptr(T *ptr) : m_ptr(ptr){}
    unique_ptr &operator=(T *ptr)
    {
        delete m_ptr;
        m_ptr = ptr;
    }

    unique_ptr(std::nullptr_t) : m_ptr(nullptr){}
    unique_ptr &operator=(std::nullptr_t){
        delete m_ptr;
        m_ptr = nullptr;
        return *this;
    }

    unique_ptr(const unique_ptr &uPtr) = delete;
    unique_ptr &operator =(const unique_ptr &uPtr) = delete;

    unique_ptr(unique_ptr &&uPtr) : m_ptr(uPtr.m_ptr){
        if(!uPtr.m_ptr)
            return;
        uPtr.m_ptr = nullptr;
    }

    unique_ptr &operator =(unique_ptr &&uPtr){
        if(this == &uPtr || !uPtr.m_ptr){
            return *this;
        }
        m_ptr = uPtr.m_ptr;
        uPtr.m_ptr = nullptr;

        return *this;
    }

    ~unique_ptr(){
        delete m_ptr;
    }


    T *release(){
        T *tmpPtr = m_ptr;
        m_ptr = nullptr;
        return tmpPtr;
    }

    void reset(T *ptr){
        delete m_ptr;
        m_ptr = ptr;
    }

    void swap(unique_ptr<T>& other){
        unique_ptr<T> tmp = move(*this);
        *this = move(other);
        other = move(tmp);
    }


    T *get() const{
        return m_ptr;
    }

    operator bool() const{
        return m_ptr != nullptr;
    }


    T& operator*() const{
        return *m_ptr;
    }

    T* operator->() const{
        return m_ptr;
    }

    template<typename S>
    friend class shared_ptr;
};


// cпециализация для массива
template<typename T>
class unique_ptr<T[]>{
    T *m_ptr;
public:
    unique_ptr() : m_ptr(nullptr){}
    unique_ptr(T *ptr) : m_ptr(ptr){}

    unique_ptr(const unique_ptr &uPtr) = delete;
    unique_ptr &operator =(const unique_ptr &uPtr) = delete;

    unique_ptr(unique_ptr &&uPtr) : m_ptr(uPtr.m_ptr){
        uPtr.m_ptr = nullptr;
    }

    unique_ptr &operator =(unique_ptr &&uPtr){
        if(this == &uPtr){
            return *this;
        }
        m_ptr = uPtr.m_ptr;
        uPtr.m_ptr = nullptr;
    }

    ~unique_ptr(){
        delete[] m_ptr;
    }


    T *release(){
        T *tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }

    void reset(T *ptr){
        delete[] m_ptr;
        m_ptr = ptr;
    }

    void swap(unique_ptr& other){
        T *tmpPtr = m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = m_ptr;
    }


    T *get() const{
        return m_ptr;
    }

    operator bool() const{
        return m_ptr;
    }

    T& operator[](int i){
        return m_ptr[i];
    }
};



template<typename T, typename ...Args>
unique_ptr<T> make_unique(Args&&... args){
    return unique_ptr<T>(new T(forward<Args>(args)...));
}


// операторы отношения порядка
template<typename T, typename S>
bool operator==(const unique_ptr<T> &lhs, const unique_ptr<S> &rhs){
    return lhs.get() == rhs.get();
}

template<typename T, typename S>
bool operator!=(const unique_ptr<T> &lhs, const unique_ptr<S> &rhs){
    return lhs.get()!= rhs.get;
}

template<typename T, typename S>
bool operator<=(const unique_ptr<T> &lhs, const unique_ptr<S> &rhs){
    return lhs.get() <= rhs.get;
}


template<typename T, typename S>
bool operator>=(const unique_ptr<T> &lhs, const unique_ptr<S> &rhs){
    return lhs.get() >= rhs.get;
}

template<typename T, typename S>
bool operator<(const unique_ptr<T> &lhs, const unique_ptr<S> &rhs){
    return lhs.get() < rhs.get;
}

template<typename T, typename S>
bool operator>(const unique_ptr<T> &lhs, const unique_ptr<S> &rhs){
    return lhs.get() > rhs.get;
}


// операторы отношения порядка
template<typename T, typename S>
bool operator==(const unique_ptr<T> &lhs, std::nullptr_t){
    return lhs.get() == nullptr;
}
template<typename T, typename S>
bool operator==(std::nullptr_t, const unique_ptr<T> &lhs){
    return lhs.get() == nullptr;
}

template<typename T, typename S>
bool operator!=(const unique_ptr<T> &lhs, std::nullptr_t){
    return lhs.get()!= nullptr;
}
template<typename T, typename S>
bool operator!=(std::nullptr_t, const unique_ptr<T> &lhs){
    return lhs.get()!= nullptr;
}




#endif // UNIQUE_PTR_H

#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include "unique_ptr.h"
//#include "weak_ptr.h"
#include "move_and_forward.h"
#include <memory>

template<typename T>
class weak_ptr;


struct RefCounter{
    int sharedCount;
    int weakCount;

    RefCounter() : sharedCount(1), weakCount(0){}

    // деструктор сделан не виртуальным намеренно,
    // что бы делегировать уничтожение дочерней части класса методу dispose();
    virtual ~RefCounter(){}

    virtual void dispose() = 0;
};

template <typename S>
struct CounterAndPointer : RefCounter{
    S *ptr;

    explicit CounterAndPointer(S *ptr) : ptr(ptr){}

    ~CounterAndPointer(){}

    void dispose() override{
        delete ptr;
    }

};

template <typename S>
struct CounterAndObject : RefCounter{
//    std::aligned_storage<sizeof (S), alignof(S)> object;
    char object[sizeof(S)];

    template<typename ...Args>
    CounterAndObject(Args&& ...args)
    {
        new (&object) S(forward<Args>(args)...);
    }

    ~CounterAndObject(){}

    void dispose() override{
//        this->~CounterAndObject();
        reinterpret_cast<S *>(&object)->~S();
    }


    std::aligned_storage<sizeof (S), alignof(S)> &getObject()
    {
        return object;
    }
};




template <typename T>
class shared_ptr{

    T *objectPtr;
    RefCounter *refCounter;


    template<typename S, typename ...Args>
    friend  shared_ptr<S> make_shared(Args&& ...args);



    void cleaning(){
        if(!objectPtr && !refCounter)
            return;

        --refCounter->sharedCount;



        if(!refCounter->sharedCount && !refCounter->weakCount){
            refCounter->dispose();
            delete refCounter; // уничтожаем родительский класс
        }
        else if(!refCounter->sharedCount)
            refCounter->dispose(); // уничтажем дочерний класс
    }



public:

    shared_ptr()
        : objectPtr(nullptr), refCounter(nullptr){}


    shared_ptr(std::nullptr_t)
        : objectPtr(nullptr), refCounter(nullptr){}
    shared_ptr &operator=(std::nullptr_t){
        cleaning();
        objectPtr = nullptr;
        refCounter = nullptr;

        return *this;
    }


    shared_ptr(T *ptr)
        : objectPtr(ptr), refCounter(new CounterAndPointer<T>(ptr)){}
    shared_ptr &operator=(T *ptr) = delete;

    shared_ptr(const shared_ptr<T> &other)
    {
        objectPtr = other.objectPtr;
        refCounter = other.refCounter;

        if(objectPtr && refCounter)
            ++(refCounter->sharedCount);
    }
    shared_ptr &operator=(const shared_ptr<T> &other)
    {
        // проверка на самоприсваивание
        if(this == &other){
            return *this;
        }

        cleaning();

        objectPtr = other.objectPtr;
        refCounter = other.refCounter;

        if(objectPtr && refCounter)
            ++(refCounter->sharedCount);

        return *this;
    }

    shared_ptr(shared_ptr<T> &&other)
        : objectPtr(other.objectPtr), refCounter(other.refCounter)
    {
        objectPtr = other.objectPtr;
        refCounter = other.refCounter;

        other.objectPtr = nullptr;
        other.refCounter = nullptr;
    }
    shared_ptr &operator=(shared_ptr<T> &&other)
    {
        if(this == &other){
            return *this;
        }

        cleaning();

        objectPtr = other.objectPtr;
        refCounter = other.refCounter;

        other.objectPtr = nullptr;
        other.refCounter = nullptr;

        return *this;
    }

    shared_ptr(unique_ptr<T> &&uniquePtr)
    {
        objectPtr = uniquePtr.m_ptr;

        if(!uniquePtr.m_ptr){
            refCounter = nullptr;
        }
        else{
            refCounter = new CounterAndPointer<T>(uniquePtr.m_ptr);
        }

        uniquePtr.m_ptr = nullptr;
    }
    shared_ptr &operator=(unique_ptr<T> &&uniquePtr)
    {
        cleaning();

        objectPtr = uniquePtr.m_ptr;

        if(!uniquePtr.m_ptr){
            refCounter = nullptr;
        }
        else{
            refCounter = new CounterAndPointer<T>(uniquePtr.m_ptr);
        }

        uniquePtr.m_ptr = nullptr;

        return *this;
    }

    shared_ptr(const weak_ptr<T> &weakPtr){
        refCounter = weakPtr.refCounter;

        if(!refCounter){
            objectPtr = nullptr;
            return;
        }

        ++refCounter->sharedCount;

        if(dynamic_cast<CounterAndPointer<T> *>(refCounter))
            this->objectPtr = static_cast<CounterAndPointer<T> *>(refCounter)->ptr;
        else
            this->objectPtr = reinterpret_cast<T *>(&static_cast<CounterAndObject<T> *>(refCounter)->object);
    }


    T &operator*(){
        return *objectPtr;
    }
    T *operator->(){
        return objectPtr;
    }

    void reset(T *ptr){
        cleaning();

        objectPtr = ptr;

        if(!ptr)
            refCounter = nullptr;
        else
            refCounter = new CounterAndPointer<T>(ptr);
    }

    void swap(shared_ptr<T> &r){
        std::swap(objectPtr, r.objectPtr);
        std::swap(refCounter, r.refCounter);
    }

    T* get() const{
        return objectPtr;
    }

    int use_count() const{
        if(!refCounter)
            return 0;

        return refCounter->sharedCount;
    }

//    bool owner_before(const shared_ptr<T> &other){
//        return objectPtr < other.objectPtr;
//    }

    operator bool(){
        return objectPtr && refCounter;
    }


    ~shared_ptr(){
        cleaning();
    }

    template<typename S>
    friend class weak_ptr;
};

template <typename S, typename ...Args>
shared_ptr<S> make_shared(Args&& ...args){
    shared_ptr<S> result;
    auto temp = new CounterAndObject<S>(forward<Args>(args)...);
//    S *tempObjectPtr = reinterpret_cast<S * >(&temp->object);
    result.objectPtr = reinterpret_cast<S *>(&temp->object);
    result.refCounter = temp;

    return result;
}


template<typename T>
std::ostream &operator<<(std::ostream &out, shared_ptr<T> &sPtr){
    return (out << sPtr.get());
}



// операторы отношения порядка
template<typename T, typename S>
bool operator==(const shared_ptr<T> &lhs, const shared_ptr<S> &rhs){
    return lhs.get() == rhs.get();
}

template<typename T, typename S>
bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<S> &rhs){
    return lhs.get()!= rhs.get;
}

template<typename T, typename S>
bool operator<=(const shared_ptr<T> &lhs, const shared_ptr<S> &rhs){
    return lhs.get() <= rhs.get;
}


template<typename T, typename S>
bool operator>=(const shared_ptr<T> &lhs, const shared_ptr<S> &rhs){
    return lhs.get() >= rhs.get;
}

template<typename T, typename S>
bool operator<(const shared_ptr<T> &lhs, const shared_ptr<S> &rhs){
    return lhs.get() < rhs.get;
}

template<typename T, typename S>
bool operator>(const shared_ptr<T> &lhs, const shared_ptr<S> &rhs){
    return lhs.get() > rhs.get;
}


// операторы отношения порядка
template<typename T, typename S>
bool operator==(const shared_ptr<T> &lhs, std::nullptr_t){
    return lhs.get() == nullptr;
}

template<typename T, typename S>
bool operator==(std::nullptr_t, const shared_ptr<T> &lhs){
    return lhs.get() == nullptr;
}


template<typename T, typename S>
bool operator!=(const shared_ptr<T> &lhs, std::nullptr_t){
    return lhs.get()!= nullptr;
}
template<typename T, typename S>
bool operator!=(std::nullptr_t, const shared_ptr<T> &lhs){
    return lhs.get()!= nullptr;
}





#endif // SHARED_PTR_H

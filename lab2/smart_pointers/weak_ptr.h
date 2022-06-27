#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#include "shared_ptr.h"

struct RefCoutnter;

template<typename T>
class weak_ptr{
    RefCounter *refCounter = nullptr;

    void cleaning(){
//        RefCounter *temp = refCounter - 1;
        if(!refCounter)
            return;


        --refCounter->weakCount;

        if(!refCounter->sharedCount && !refCounter->weakCount)
            delete refCounter;
    }

    weak_ptr(T *value){
        if(value){
            refCounter = new CounterAndPointer(value);
        }
        else{
            refCounter = nullptr;
        }
    }

public:

    weak_ptr() = default;

//    weak_ptr(std::nullptr_t) : refCounter(nullptr){}

    weak_ptr(const shared_ptr<T> &sharedPtr)
        : refCounter(sharedPtr.refCounter)
    {
        if(refCounter)
            ++refCounter->weakCount;
    }

    weak_ptr<T> &operator=(const shared_ptr<T> &sharedPtr)
    {
        cleaning();

        refCounter = sharedPtr.refCounter;
        if(refCounter)
            ++refCounter->weakCount;

        return *this;
    }

    weak_ptr(const weak_ptr<T> &other)
        : refCounter(other.refCounter)
    {
        if(refCounter)
            ++refCounter->weakCount;
    }
    weak_ptr<T> &operator=(const weak_ptr<T> &other)
    {
        cleaning();

        refCounter = other.refCounter;
        if(refCounter)
            ++refCounter->weakCount;
    }

    weak_ptr(weak_ptr<T> &&other)
        : refCounter(other.refCounter)
    {
        other.refCounter = nullptr;
    }

    weak_ptr<T> &operator=(weak_ptr<T> &&other)
    {
        if(this == &other)
            return *this;
        cleaning();

        refCounter = other.refCounter;

        other.refCounter = nullptr;
    }

    void reset(){
        cleaning();
        refCounter = nullptr;
    }

    void swap(weak_ptr<T> &r){
        weak_ptr<T> temp = move(*this);
        *this = move(r);
        r = move(temp);
    }

    int use_count(){
        if(!refCounter)
            return 0;

        return refCounter->sharedCount;
    }

    bool expired(){
        if(!refCounter)
            return true;

        return refCounter->sharedCount == 0;
    }

    shared_ptr<T> lock() const{
        if(!refCounter)
            return shared_ptr<T>(nullptr);

        if(!refCounter->sharedCount)
            return shared_ptr<T>(nullptr);

        return shared_ptr<T>(*this);
    }


    ~weak_ptr(){
        cleaning();
    }

    template<typename S>
    friend class shared_ptr;
};


#endif // WEAK_PTR_H

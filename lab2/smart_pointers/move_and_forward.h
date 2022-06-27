#ifndef MOVE_AND_FORWARD_H
#define MOVE_AND_FORWARD_H

typedef int X;

template<typename T>
struct remove_reference{
    typedef T type;
};

template<typename T>
struct remove_reference<T&>{
    typedef T type;
};

template<typename T>
struct remove_reference<T&&>{
    typedef T type;
};

template<typename T>
T &&forward(typename remove_reference<T>::type &t){
    return static_cast<T &&>(t);
}

template<typename T>
typename remove_reference<T>::type &&move(T &&t){
    return static_cast<typename remove_reference<T>::type &&>(t);
}
#endif // MOVE_AND_FORWARD_H

#ifndef MY_PAIR_H
#define MY_PAIR_H
#include <memory>


template<typename T1, typename T2>
struct pair{
    T1 first;
    T2 second;

    pair() = default;
    pair(const pair &) = default;
    pair(pair &&) = default;

    pair(const T1 &first, const T2 &second)
        : first(first), second(second){}

    pair(T1 &&first, T2 &&second)
        : first(std::forward<T1>(first)), second(std::forward<T2>(second)){}

    template <typename U1, typename U2>
    pair(U1 &&first, U2 &&second)
        : first(std::forward<U1>(first)), second(std::forward<U2>(second)){}

    pair &operator=(const pair &other) = default;
    pair &operator=(pair &&other) = default;

    void swap(pair &other){
        pair temp = std::move(other);
        other = std::move(*this);
        *this = std::move(temp);
    }

};

template<typename T1, typename T2>
pair<T1, T2> make_pair(T1 first, T2 second){
    return pair<T1, T2>(std::move(first), std::move(second));
}

//template<typename _Tp>
//class reference_wrapper;
//   // Helper which adds a reference to a type when given a reference_wrapper
//template<typename _Tp>
//struct __strip_reference_wrapper
//{
//    typedef _Tp __type;
//};

//template<typename _Tp>
//struct __strip_reference_wrapper<reference_wrapper<_Tp> >
//{
//    typedef _Tp& __type;
//};

//template<typename _Tp>
//struct __strip_reference_wrapper<const reference_wrapper<_Tp> >
//{
//    typedef _Tp& __type;
//};

//template<typename _Tp>
//struct __decay_and_strip
//{
//    typedef typename __strip_reference_wrapper<
//    typename std::decay<_Tp>::type>::__type __type;
//};

//// NB: DR 706.
//template<class _T1, class _T2>
//inline pair<typename __decay_and_strip<_T1>::__type,
//    typename __decay_and_strip<_T2>::__type>
//make_pair(_T1&& __x, _T2&& __y)
//{
//    return pair<typename __decay_and_strip<_T1>::__type,
//typename __decay_and_strip<_T2>::__type>
//(std::forward<_T1>(__x), std::forward<_T2>(__y));
//}


#endif // MY_PAIR_H


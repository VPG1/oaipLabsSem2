#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <memory>
#include <cassert>


template<typename T>
class vector{
    T *m_arr = nullptr;
    std::size_t m_size = 0;
    std::size_t m_cap = 0;



    template<class Iter>
    struct common_iterator{
        friend class vector;

//        using iterator_type = typename std::conditional<IsConst, const T, T>::type;
        using iterator_type = Iter;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = iterator_type;
        using reference = iterator_type&;
        using pointer = iterator_type*;
        using difference_type = std::ptrdiff_t;

    private:
        pointer ptr;
        common_iterator(pointer ptr) : ptr(ptr){}
    public:
        common_iterator(const common_iterator &) = default;
        common_iterator &operator=(const common_iterator &) = default;

        operator common_iterator<const T>() const{
            return common_iterator<const T>(ptr);
        }


        reference operator *(){
            return *ptr;
        }

        pointer operator->(){
            return ptr;
        }

        common_iterator &operator++(){
            ++ptr;
            return *this;
        }

        common_iterator operator++(int){
            common_iterator temp = *this;
            ++ptr;
            return temp;

        }

        common_iterator &operator--(){
            --ptr;
            return *this;
        }
        common_iterator operator--(int){
            common_iterator temp = *this;
            --ptr;
            return temp;
        }

        common_iterator operator+=(int n){
            ptr += n;
            return *this;
        }
        common_iterator operator-=(int n){
            ptr -= n;
            return *this;
        }



        friend common_iterator operator+(std::size_t n, const common_iterator &it){
            return n + it;
        }
        friend common_iterator operator+(const common_iterator &it, std::size_t n){
            return it.ptr + n;
        }
        friend common_iterator operator-(const common_iterator &it, std::size_t n){
            return it.ptr - n;
        }

        friend int operator-(const common_iterator &leftIt,
                                         const common_iterator &rightIt)
        {
            return leftIt.ptr - rightIt.ptr;
        }


        friend bool operator==(const common_iterator &leftIt, const common_iterator &rightIt){
            return leftIt.ptr == rightIt.ptr;
        }
        friend bool operator!=(const common_iterator &leftIt, const common_iterator &rightIt){
            return leftIt.ptr != rightIt.ptr;
        }
        friend bool operator>(const common_iterator &leftIt, const common_iterator &rightIt){
            return leftIt.ptr > rightIt.ptr;
        }
        friend bool operator<(const common_iterator &leftIt, const common_iterator &rightIt){
            return leftIt.ptr < rightIt.ptr;
        }
        friend bool operator>=(const common_iterator &leftIt, const common_iterator &rightIt){
            return leftIt.ptr >= rightIt.ptr;
        }
        friend bool operator<=(const common_iterator &leftIt, const common_iterator &rightIt){
            return leftIt.ptr <= rightIt.ptr;
        }

    };

public:

    using iterator = common_iterator<T>;
    using const_iterator = common_iterator<const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    iterator begin(){
        return iterator(m_arr);
    }
    const_iterator begin() const{
        return const_iterator(m_arr);
    }

    const_iterator cbegin() const{
        return const_iterator(m_arr);
    }

    iterator end(){
        return iterator(m_arr + m_size);
    }
    const_iterator end() const{
        return const_iterator(m_arr + m_size);
    }

    const_iterator cend(){
        return const_iterator(m_arr + m_size);
    }


    reverse_iterator rbegin(){
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const{
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const{
        return const_reverse_iterator(end());
    }

    reverse_iterator rend(){
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const{
        return const_reverse_iterator(--begin());
    }

    const_reverse_iterator crend() const{
        return const_reverse_iterator(--begin());
    }







    vector() = default;

    vector(std::size_t size, const T &value = T()){
        if(!size){
            m_arr = nullptr;
            return;
        }

        m_arr = reinterpret_cast<T*>(new char[sizeof(T) * size]);
        for(std::size_t i = 0; i < size; ++i){
            new(m_arr + i) T(value);
        }
        m_size = size;
        m_cap = size;
    }

    vector(const vector &other){
        m_size = other.m_size;
        m_cap = other.m_cap;

        if(other.m_arr){
            m_arr = reinterpret_cast<T*>(new char[m_cap * sizeof(T)]);
            for(std::size_t i = 0; i < m_size; ++i){
                new(m_arr + i)T(other[i]);
            }
        }
        else
            m_arr = nullptr;
    }

    vector(vector &&other){
        m_arr = other.m_arr;
        m_size = other.m_size;
        m_cap = other.m_cap;

        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_cap = 0;
    }

    vector &operator=(const vector &other){
        if(this == &other) return *this;

        for(std::size_t i = 0; i < m_size; ++i){
            (m_arr + i)->~T();
        }
        delete[] reinterpret_cast<char *>(m_arr);


        m_size = other.m_size;
        m_cap = other.m_cap;


        if(other.m_arr){
            m_arr = reinterpret_cast<T*>(new char[sizeof(T) * other.m_cap]);
            for(std::size_t i = 0; i < other.m_size; ++i){
                new(m_arr + i) T(other.m_arr[i]);
            }
        }
        else
            m_arr = nullptr;

        return *this;
    }

    vector &operator=(vector &&other){
        if(this == &other) return *this;

        for(std::size_t i = 0; i < m_size; ++i){
            (m_arr + i)->~T();
        }
        delete[] reinterpret_cast<std::size_t *>(m_arr);

        m_arr = other.m_arr;
        m_size = other.m_size;
        m_cap = other.m_cap;

        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_cap = 0;

        return *this;
    }

    ~vector(){
        for(std::size_t i = 0; i < m_size; ++i)
            (m_arr + i)->~T();
        delete[] reinterpret_cast<char *>(m_arr);
    }


    void assign(std::size_t size, const T &value = T()){
        for(std::size_t i = 0; i < m_size; ++i){
            (m_arr + i)->~T();
        }

        if(size > m_cap){
            delete reinterpret_cast<char *>(m_arr);
            m_arr = reinterpret_cast<T *>(new char[sizeof(T) * size]);
            m_cap = size;
        }

        for(std::size_t i = 0; i < size; ++i){
            new (m_arr + i) T(value);
        }

        m_size = size;
    }



    T &operator[](std::size_t i){
        return m_arr[i];
    }
    const T &operator[](std::size_t i) const{
        return m_arr[i];
    }

    T &front(){
        return m_arr[0];
    }
    const T &front() const{
        return m_arr[0];
    }
    T &back(){
        return m_arr[m_size - 1];
    }
    const T &back() const{
        return m_arr[m_size - 1];
    }

    T *data() const{
        return m_arr;
    }

    bool empty(){
        return m_size == 0;
    }

    std::size_t size() const{
        return m_size;
    }
    std::size_t capacity() const{
        return m_cap;
    }

    std::size_t max_size() const{
        std::size_t res = 1;
        for(int i = 0; i < 63; ++i){
            res <<= 1;
        }
//        res /= sizeof(T);
        return (res - 1) / sizeof(T);
    }



    void reserve(std::size_t cap){
        if(m_cap >= cap) return;

        T *newArr = reinterpret_cast<T*>(new char[cap * sizeof(T)]);
        for(std::size_t i = 0; i < m_size; ++i){
            new(newArr + i)T(std::move(m_arr[i]));
        }

        for(std::size_t i = 0; i < m_size; ++i){
            (m_arr + i)->~T();
        }
        delete[] reinterpret_cast<char *>(m_arr);

        m_cap = cap;
        m_arr = newArr;
    }

    void shrink_to_fit(){
        if(m_size == m_cap)
            return;

        T *newArr;
        if(m_arr){
            newArr = reinterpret_cast<T*>(new char[sizeof(T) * m_size]);
            for(std::size_t i = 0; i < m_size; ++i){
                new(newArr + i)T(m_arr[i]);
            }
            for(std::size_t i = 0; i < m_size; ++i){
                (m_arr + i)->~T();
            }
            delete[] reinterpret_cast<char *>(m_arr);
        }
        else
            newArr = nullptr;


        m_arr = newArr;
        m_cap = m_size;
    }



    void clear(){
        for(std::size_t i = 0; i < m_size; ++i){
            (m_arr + i)->~T();
        }
        m_size = 0;
    }

    void push_back(const T &value){
        if(m_cap == 0) reserve(1);
        if(m_size >= m_cap) reserve(2 * m_cap);

        new(m_arr + m_size) T(value);

        ++m_size;
    }

    void push_back(T &&value){
        if(m_cap == 0) reserve(1);
        if(m_size >= m_cap) reserve(2 * m_cap);

        new(m_arr + m_size) T(std::move(value));

        ++m_size;
    }

    void pop_back(){
        (m_arr + m_size - 1)->~T();
        --m_size;
    }

    void insert(const_iterator pos, const T &value){
        if(m_size >= m_cap){
            T *newArr;

            if(m_cap == 0){
                newArr = reinterpret_cast<T *>(new char[sizeof(T)]);
                m_cap = 1;
            }
            else{
                newArr = reinterpret_cast<T *>(new char[2 * sizeof(T) * m_size]);
                m_cap = 2 * m_size;
            }

            int i = 0;
            for(; m_arr + i != pos.ptr; ++i){
                new(newArr + i) T(std::move(m_arr[i]));
            }
            new(newArr + i) T(value);
            ++i;
            for(; i < m_size; ++i){
                new(newArr + i) T(std::move(m_arr[i - 1]));
            }

            for(int i = 0; i < m_size; ++i){
                (m_arr + i)->~T();
            }
            delete[] reinterpret_cast<char*>(m_arr);

            m_arr = newArr;
        }
        else{
            int i;
            for(i = m_size + 1; i > std::distance(begin(), pos); --i){
                new(m_arr + i) T(std::move(m_arr[i - 1]));
                (m_arr + i - 1)->~T();
            }

            new(m_arr + i) T(value);
        }

        ++m_size;
    }

    void insert(const_iterator pos, T &&value){
        if(m_size >= m_cap){
            T *newArr;

            if(m_cap == 0){
                newArr = reinterpret_cast<T *>(new char[sizeof(T)]);
                m_cap = 1;
            }
            else{
                newArr = reinterpret_cast<T *>(new char[2 * sizeof(T) * m_size]);
                m_cap = 2 * m_size;
            }

            int i = 0;
            for(; m_arr + i != pos.ptr; ++i){
                new(newArr + i) T(std::move(m_arr[i]));
            }
            new(newArr + i) T(std::move(value));
            ++i;
            for(; i < m_size + 1; ++i){
                new(newArr + i) T(std::move(m_arr[i - 1]));
            }

            for(int j = 0; j < m_size; ++j){
                (m_arr + j)->~T();
            }
            delete[] reinterpret_cast<char *>(m_arr);

            m_arr = newArr;
        }
        else{
            int i;
            for(i = m_size; i > std::distance(cbegin(), pos); --i){
                new(m_arr + i) T(std::move(m_arr[i - 1]));
                (m_arr + i - 1)->~T();
            }

            new(m_arr + i) T(std::move(value));
        }

        ++m_size;
    }

    void insert(const_iterator pos, size_t count, const T &value){
        if(m_size + count - 1 >= m_cap){
            T *newArr;

            if(m_size + count <= 2 * m_size){
                m_cap = 2 * m_size;
                newArr = reinterpret_cast<T *>(new char[sizeof(T) * m_cap]);
            }
            else{
                m_cap = m_size + count;
                newArr = reinterpret_cast<T *>(new char[sizeof(T) * m_cap]);
            }


            int i = 0, j = 0;
            for(; m_arr + i != pos.ptr; ++i, ++j){
                new(newArr + j) T(std::move(m_arr[i]));
            }

            for(; j < count; ++j){
                new(newArr + j) T(value);
            }

            for(; i < m_size; ++i, ++j){
                new(newArr + j) T(std::move(m_arr[i]));
            }



            for(int i = 0; i < m_size; ++i){
                (m_arr + i)->~T();
            }
            delete[] reinterpret_cast<char*>(m_arr);


            m_arr = newArr;
        }
        else{
            int i;
            for(i = m_size + count - 1; i > std::distance(cbegin(), pos) + count - 1; --i)
            {
                new(m_arr + i) T(std::move(m_arr[i - 1]));
                (m_arr + i - 1)->~T();
            }

            for(;i >= std::distance(cbegin(), pos); --i)
                new(m_arr + i) T(value);
        }

        m_size += count;
    }


    template<typename ...Args>
    void emplace_back(Args&&... args){
        if(m_cap == 0) reserve(1);
        if(m_size >= m_cap) reserve(2 * m_cap);

        new(m_arr + m_size) T(std::forward<Args>(args)...);

        ++m_size;
    }

    template<typename ...Args>
    void emplace(const_iterator pos, Args&&... args){
        if(m_size >= m_cap){
            T *newArr;

            if(m_cap == 0){
                newArr = reinterpret_cast<T *>(new char[sizeof(T)]);
                m_cap = 1;
            }
            else{
                newArr = reinterpret_cast<T *>(new char[2 * sizeof(T) * m_size]);
                m_cap = 2 * m_size;
            }

            int i = 0;
            for(; m_arr + i != pos.ptr; ++i){
                new(newArr + i) T(std::move(m_arr[i]));
            }
            new(newArr + i) T(std::forward<Args>(args)...);
            ++i;
            for(; i < m_size + 1; ++i){
                new(newArr + i) T(std::move(m_arr[i - 1]));
            }

            for(int j = 0; j < m_size; ++j){
                (m_arr + j)->~T();
            }
            delete[] reinterpret_cast<char *>(m_arr);

            m_arr = newArr;
        }
        else{
            int i;
            for(i = m_size; i > std::distance(cbegin(), pos); --i){
                new(m_arr + i) T(std::move(m_arr[i - 1]));
                (m_arr + i - 1)->~T();
            }

            new(m_arr + i) T(std::forward<Args>(args)...);
        }

        ++m_size;
    }

    void erase(iterator pos){
        auto it = pos + 1;
        pos.ptr->~T();
        for(; it != end(); ++it){
            new ((it - 1).ptr) T(std::move(*it));
            it.ptr->~T();
        }
        --m_size;
    }




    void resize(std::size_t size, const T &value = T()){
        if(m_size == size) return;

        reserve(size);

        if(size > m_size){
            for(std::size_t i = size - m_size; i < size; ++i){
                new(m_arr + i)T(value);
            }
        }
        else{
            for(std::size_t i = m_size - size; i < m_size; ++i){
                (m_arr + i)->~T();
            }
        }

        m_size = size;
    }

    void swap(vector &other){
        std::swap(m_arr, other.m_arr);
        std::swap(m_size, other.m_size);
        std::swap(m_cap, other.m_cap);
    }


};

#endif // MY_VECTOR_H


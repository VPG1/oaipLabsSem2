#ifndef DEQUE_H
#define DEQUE_H
#include <cstddef>
#include <QApplication>

#define BLOCK_SIZE 12;


template<typename T>
class Deque{
    static size_t block_size(){
        return BLOCK_SIZE;
    }

    struct DequeIterator{

        friend class Deque;

    private:
        T *cur;
        T *first;
        T *last;
        T **node;

        void setNode(T **new_node){
            node = new_node;
            first = *new_node;
            last = first + block_size();
        }

    public:
        DequeIterator() : cur(nullptr), first(nullptr), last(nullptr), node(nullptr){}
        DequeIterator &operator=(std::nullptr_t){
            cur = nullptr;
            first = nullptr;
            last = nullptr;
            node = nullptr;

            return *this;
        }

        DequeIterator(T *cur, T **node)
            : cur(cur), first(*node), last(*node + block_size()), node(node){}

        DequeIterator(const DequeIterator &other)
            : cur(other.cur), first(other.first), last(other.last), node(other.node){}



        T &operator*() const {
            return *cur;
        }

        T *operator->()const{
            return cur;
        }

        DequeIterator &operator++(){
            ++cur;
            if(cur == last){
                setNode(node + 1);
                cur = first;
            }
            return *this;
        }

        DequeIterator operator++(int){
            auto temp = *this;
            ++*this;
            return temp;
        }

        DequeIterator &operator--(){
            if(cur == first){
                setNode(node - 1);
                cur = last;
            }
            --cur;


            return *this;
        }

        DequeIterator operator--(int){
            auto temp = *this;
            --*this;
            return temp;
        }

        DequeIterator &operator+=(std::ptrdiff_t n){
            std::ptrdiff_t offset = n + (cur - first);
            if(offset >= 0 && offset < block_size()){
                cur += n;
            }
            else{
                std::ptrdiff_t node_offset =
                        offset > 0 ? offset / block_size() :
                                     -std::ptrdiff_t((-offset - 1) / block_size()) - 1;

                node = node + node_offset;
                first = *node;
                last = first + block_size();

                cur = first + (offset - node_offset * block_size());
            }

            return *this;
        }

        DequeIterator &operator-=(std::ptrdiff_t n){
            return *this += -n;
        }

        DequeIterator operator+(std::ptrdiff_t n){
            auto tmp = *this;
            return tmp += n;
        }

        DequeIterator operator-(std::ptrdiff_t n){
            auto tmp = *this;
            return tmp -= n;
        }

        std::ptrdiff_t operator-(const DequeIterator &lhs){
            return block_size() * (node - lhs.node - 1) + (cur - first) + (lhs.last - cur);
        }

        friend bool operator== (const DequeIterator &lhs, const DequeIterator &rhs){
            return lhs.cur == rhs.cur;
        }

        friend bool operator!= (const DequeIterator &lhs, const DequeIterator &rhs){
            return lhs.cur != rhs.cur;
        }

        friend bool operator<(const DequeIterator &lhs, const DequeIterator &rhs){
            return lhs.node == rhs.node ? (lhs.cur < rhs.cur) : (lhs.node < rhs.node);
        }

    };



public:
    typedef DequeIterator iterator;

    Deque(){

    }

    size_t size() const
    {
        return m_size;
    }



    void push_back(const T &value){
        ++m_size;
        if(map == nullptr){
            ++numOfBlocks;
            map = new T*[numOfBlocks];
            map[0] = reinterpret_cast<T*>(new char[sizeof(T) * block_size()]);

            m_begin.setNode(map);
            m_begin.cur = new (&map[0][block_size() / 2]) T(value);

            m_end.setNode(map);
            m_end.cur = m_begin.cur + 1;
        }
        else if(m_end.cur != m_end.last - 1){
            new(m_end.cur) T(value);
            ++m_end;
        }
        else{
            ++numOfBlocks;
            T **newMap = new T*[numOfBlocks];
            for(int i = 0; i < numOfBlocks - 1; ++i){
                newMap[i] = map[i];
            }

            newMap[numOfBlocks - 1] = reinterpret_cast<T*>(new char[sizeof(T) * block_size()]);

            new(m_end.cur) T(value);

            m_begin.node = &newMap[0];

            m_end.node = &newMap[numOfBlocks - 2];
             ++m_end;

            delete[] map;

            map = newMap;
        }
    }

    void push_front(const T &value){
        ++m_size;
        if(map == nullptr){
            ++numOfBlocks;
            map = new T*[numOfBlocks];
            map[0] = reinterpret_cast<T*>(new char[sizeof(T) * block_size()]);

            m_begin.setNode(map);
            m_begin.cur = new (&map[0][block_size() / 2]) T(value);

            m_end.setNode(map);
            m_end.cur = m_begin.cur + 1;
        }
        else if(m_begin.cur != m_begin.first){
            --m_begin;
            new(m_begin.cur) T(value);
        }
        else{
            ++numOfBlocks;
            T **newMap = new T*[numOfBlocks];
            for(int i = 1; i < numOfBlocks; ++i){
                newMap[i] = map[i];
            }

            newMap[0] = reinterpret_cast<T *>(new char[sizeof(T) * block_size()]);

            m_begin.node = &newMap[1];
            --m_begin;

            new(m_begin.cur) T(value);

            m_end.node = &newMap[numOfBlocks - 1];

            delete[] map;

            map = newMap;
        }

    }

    void pop_back(){
        assert(map);

        --m_size;

        if(m_end.cur != m_end.first){
            --m_end;
            m_end.cur->~T();
            if(!m_size){
                delete[] reinterpret_cast<char *>(map[0]);
                delete[] map;
                map = nullptr;
                m_begin = nullptr;
                m_end = nullptr;
                numOfBlocks = 0;
            }
        }
        else{
            --m_end;
            m_end.cur->~T();
            delete[] reinterpret_cast<char*>(map[numOfBlocks - 1]);

            if(!m_size){
                delete[] reinterpret_cast<char*>(map[0]);
                delete[] map;
                map = nullptr;
                m_begin = nullptr;
                m_end = nullptr;
                numOfBlocks = 0;
            }
            else{
                --numOfBlocks;

                T **newMap = new T*[numOfBlocks];
                for(size_t i = 0; i < numOfBlocks; ++i){
                    newMap[i] = map[i];
                }

                m_begin.node = &newMap[0];
                m_end.node = &newMap[numOfBlocks - 1];

                delete[] map;

                map = newMap;
            }
        }
    }

    void pop_front(){
        assert(map);

        --m_size;

        if(m_begin.cur != m_begin.last - 1){
            m_begin->~T();
            ++m_begin;
            if(!m_size){
                delete[] reinterpret_cast<char *>(map[0]);
                delete[] map;
                map = nullptr;
                m_begin = nullptr;
                m_end = nullptr;
                numOfBlocks = 0;
            }
        }
        else{
            m_begin->~T();
            ++m_begin;
            delete[] reinterpret_cast<char*>(map[0]);

            if(!m_size){
                delete[] reinterpret_cast<char *>(map[1]);
                delete[] map;
                map = nullptr;
                m_begin = nullptr;
                m_end = nullptr;
                numOfBlocks = 0;
            }
            else{
                --numOfBlocks;

                T **newMap = new T*[numOfBlocks];
                for(int i = 0; i < numOfBlocks; ++i){
                    newMap[i] = map[i + 1];
                }

                m_begin.node = &newMap[0];
                m_end.node = &newMap[numOfBlocks - 1];

                delete[] map;

                map = newMap;
            }
        }
    }

    bool empty(){
        return !map;
    }

    void clear(){
        for(auto it = m_begin; it != m_end; ++it){
            it.cur->~T();
        }
        for(int i = 0; i < numOfBlocks; ++i){
            delete[] reinterpret_cast<char*>(map[i]);
        }
        delete[] map;

        map = nullptr;
        m_begin = nullptr;
        m_end = nullptr;
        m_size = 0;
        numOfBlocks = 0;
    }

    iterator begin(){
        return m_begin;
    }

    iterator end(){
        return m_end;
    }

    void resize(int size, const T &value = T()){
        if(size > m_size){
            while(size != m_size){
                this->push_back(value);
            }
        }
        else{
            while(size != m_size){
                this->pop_back();
            }
        }
    }


private:
    size_t numOfBlocks = 0;
    size_t m_size = 0;
    T **map = nullptr;
    iterator m_begin;
    iterator m_end;

};



#endif // DEQUE_H

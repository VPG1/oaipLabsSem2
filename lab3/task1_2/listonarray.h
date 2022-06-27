#ifndef LISTONARRAY_H
#define LISTONARRAY_H
#include <memory>
#include <cassert>

#define head m_array[m_fake].next
#define tail m_array[m_fake].prev
#define vectorSize m_size + 1

template<typename T>
class ListOnArray
{
    struct Node{
        T key;
        int next;
        int prev;
    };

    Node *m_array = nullptr;
    int m_fake = 0;
    int m_size = 0;




public:

    ListOnArray(){
        m_array = reinterpret_cast<Node*>(new char[sizeof(Node)]);
        m_array[m_fake].next = m_fake;
        m_array[m_fake].prev = m_fake;
    };

    ~ListOnArray(){
        for(int i = 1; i < vectorSize; ++i){
            m_array[i].~Node();
        }
        delete[] reinterpret_cast<char *>(m_array);
    }

    ListOnArray(const ListOnArray&) = delete;
    ListOnArray &operator=(const ListOnArray &) = delete;

    ListOnArray(ListOnArray&& other){
        m_array = other.m_array;
        m_size = other.m_size;

        other.m_array = nullptr;
        other.m_size = 0;
    }

    ListOnArray &operator=(ListOnArray&& other){
        if(this == &other)
            return *this;

        this->~ListOnArray();

        m_array = other.m_array;
        m_size = other.m_size;

        other.m_array = nullptr;

        other.m_size = 0;

        return *this;
    }

    void clear() {
      for (int i = 1; i < vectorSize; ++i) {
        m_array[i].~Node();
      }
      delete[] reinterpret_cast<char *>(m_array);

      m_array = reinterpret_cast<Node *>(new char[sizeof(Node)]);
      m_array[m_fake].next = m_fake;
      m_array[m_fake].prev = m_fake;
      m_size = 0;
    }

    void push_front(const T &key){
        Node *array = reinterpret_cast<Node*>(new char[sizeof(Node)*(vectorSize + 1)]);
        if(!m_size){
            array[0].next = 1;
            array[0].prev = 1;
//            array[1] = Node{key, m_fake, m_fake};
            new(&array[1]) Node{key, m_fake, m_fake};
        }
        else{
            array[m_fake].next = head;
            array[m_fake].prev = tail;

            for(int i = 1; i < vectorSize; ++i){
                new(&array[i]) Node{std::move(m_array[i].key),
                            m_array[i].next, m_array[i].prev};
            }

            new(&array[vectorSize]) Node{key, head, m_fake};

            array[array[m_fake].next].prev = vectorSize;
            array[m_fake].next = vectorSize;
        }

        for(int i = 1; i < vectorSize; ++i){
            m_array[i].~Node();
        }
        delete[] reinterpret_cast<char*>(m_array);
        m_array = array;

        ++m_size;
    }

    void push_front(T &&key){
        Node *array = reinterpret_cast<Node*>(new char[sizeof(Node)*(vectorSize + 1)]);
        if(!m_size){
            array[0].next = 1;
            array[0].prev = 1;
//            array[1] = Node{std::move(key), m_fake, m_fake};
            new(&array[1]) Node{std::move(key), m_fake, m_fake};
        }
        else{
            array[m_fake].next = head;
            array[m_fake].prev = tail;

            for(int i = 1; i < vectorSize; ++i){
                new(&array[i]) Node{std::move(m_array[i].key),
                            m_array[i].next, m_array[i].prev};
            }

            new(&array[vectorSize]) Node{std::move(key),
                        head, m_fake};

//            array[0].next = vectorSize;
//            array[array[vectorSize].next].prev = head;
            array[array[m_fake].next].prev = vectorSize;
            array[m_fake].next = vectorSize;
        }

        for(int i = 1; i < vectorSize; ++i){
            m_array[i].~Node();
        }
        delete[] reinterpret_cast<char*>(m_array);

        m_array = array;

        ++m_size;
    }

    void push_back(const T &key){
        Node *array = reinterpret_cast<Node*>(new char[sizeof(Node)*(vectorSize + 1)]);
        if(!m_size){
            array[0].next = 1;
            array[0].prev = 1;
            new(&array[1]) Node{key, m_fake, m_fake};
        }
        else{
            array[m_fake].next = head;
            array[m_fake].prev = tail;

            for(int i = 1; i < vectorSize; ++i){
                new(&array[i]) Node{std::move(m_array[i].key),
                            m_array[i].next, m_array[i].prev};
            }

            new(&array[vectorSize]) Node{key, m_fake, tail};
            array[array[m_fake].prev].next = vectorSize;
            array[m_fake].prev = vectorSize;
        }

        for(int i = 1; i < vectorSize; ++i){
            m_array[i].~Node();
        }
        delete[] reinterpret_cast<char*>(m_array);

        m_array = array;

        ++m_size;
    }

    void push_back(T &&key){
        Node *array = reinterpret_cast<Node*>(new char[sizeof(Node) * (vectorSize + 1)]);
        if(!m_size){
            array[0].next = 1;
            array[0].prev = 1;
//            array[1] = Node{key, m_fake, m_fake};
            new (&array[1]) Node{key, m_fake, m_fake};
        }
        else{
            array[m_fake].next = head;
            array[m_fake].prev = tail;

            for(int i = 1; i < vectorSize; ++i){
                new(&array[i]) Node{std::move(m_array[i].key),
                            m_array[i].next, m_array[i].prev};
            }

            new(&array[vectorSize]) Node{std::move(key),
                        m_fake, tail};
//            array[0].prev = vectorSize;
//            tail = vectorSize;
            array[array[m_fake].prev].next = vectorSize;
            array[m_fake].prev = vectorSize;
        }

        for(int i = 1; i < vectorSize; ++i){
            m_array[i].~Node();
        }
        delete[] reinterpret_cast<char*>(m_array);

        m_array = array;

        ++m_size;
    }


    void pop_front(){
        assert(m_size);

        head = m_array[head].next;
        m_array[head].prev = m_fake;

        --m_size;
    }

    void pop_back(){
        assert(m_size);

        tail = m_array[tail].prev;
        m_array[tail].next = m_fake;

        --m_size;
    }


    void erase(int pos){
        assert(pos >= 0 && pos < m_size);

        int erasingNode = head;
        for(int i = 0; i < pos; ++i){
            erasingNode = m_array[erasingNode].next;
        }

        m_array[m_array[erasingNode].prev].next = m_array[erasingNode].next;
        m_array[m_array[erasingNode].next].prev = m_array[erasingNode].prev;

        --m_size;
    }


    struct iterator{
    private:
        int nodeIndex;
        Node *array;
    public:
        iterator(int nodeIndex, Node *array)
            : nodeIndex(nodeIndex), array(array){}

        iterator &operator++(){
            nodeIndex = array[nodeIndex].next;
            return *this;
        }
        iterator &operator--(){
            nodeIndex = array[nodeIndex].prev;
            return *this;
        }

        T &operator*(){
            return array[nodeIndex].key;
        }
        T *operator->(){
            return &(array[nodeIndex].key);
        }

        bool operator==(const iterator &it){
            return nodeIndex == it.nodeIndex;
        }
        bool operator!=(const iterator &it){
            return nodeIndex != it.nodeIndex;
        }
    };

    iterator begin() const{
        return iterator(head, m_array);
    }

    iterator end() const{
        return iterator(m_fake, m_array);
    }
    int size() const
    {
        return m_size;
    }
};



#endif // LISTONARRAY_H

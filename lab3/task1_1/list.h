#ifndef TASK1_LIST_H
#define TASK1_LIST_H
#include <memory>
#include <cassert>

template<class T>
class List{
    struct Node{
        T key;
        Node *next;
        Node *prev;
    };

    Node *m_head = nullptr;
//    Node *m_fake->prev = nullptr;
    Node *m_fake;
    int m_size = 0;

public:
    struct iterator{
    private:
        Node *node;

    public:
        iterator(Node *ptr) : node(ptr){}

        T &operator*(){
            return node->key;
        }
        T *operator->(){
            return &node->key;
        }

        iterator &operator++(){
            node = node->next;
            return *this;
        }
        iterator &operator--(){
            node = node->prev;
            return *this;
        }

        bool operator==(const iterator &it){
            return node == it.node;
        }
        bool operator!=(const iterator &it){
            return node != it.node;
        }
    };

    iterator begin(){
        return m_head;
    }
    iterator end(){
        return m_fake;
    }

    List(){
        // выделяем память так, что бы не вызывать конструктор для T
        m_fake = reinterpret_cast<Node *>(new char[sizeof(Node)]);
        m_fake->next = nullptr;
        m_fake->prev = m_head;
    };

    List(const List &list) = delete;
    List &operator=(const List &list) = delete;

    List(List &&list){
        m_head = list.m_head;
        m_fake = list.m_fake;
        m_size = list.m_size;

        list.m_head = nullptr;
        list.m_fake = nullptr;
        list.m_size = 0;
    }
    List &operator=(List &&list){
        if(this == &list){
            return *this;;
        }

        this->~List();

        m_head = list.m_head;
        m_fake = list.m_fake;
        m_size = list.m_size;

        list.m_head = nullptr;
        list.m_fake = nullptr;
        list.m_size = 0;

        return *this;
    }

    ~List(){
        Node *deletedNode = m_head;
        for(int i = 0; i < m_size; ++i){
            auto temp = deletedNode;
            deletedNode = deletedNode->next;
            delete temp;
        }
        delete[] reinterpret_cast<char *>(m_fake);
    }

    int size() const{
        return m_size;
    }

    void push_front(const T& newKey){
        if(!m_size){
//            m_tail = m_head = new Node{newKey, nullptr, nullptr};
            m_fake->prev = m_head = new Node{newKey, m_fake, nullptr};
        }
        else{
            m_head = new Node{newKey, m_head, nullptr};
            m_head->next->prev = m_head;
        }
        ++m_size;
    }
    void push_front(T&& newKey){
        if(!m_size){
//            m_tail = m_head = new Node{std::move(newKey), nullptr, nullptr};
            m_fake->prev = m_head = new Node{std::move(newKey), m_fake, nullptr};
        }
        else{
            m_head = new Node{std::move(newKey), m_head, nullptr};
            m_head->next->prev = m_head;
        }
        ++m_size;
    }

    void push_back(const T& newKey){
        if(!m_size){
//            m_head = m_tail = new Node{newKey, nullptr, nullptr};
            m_head = m_fake->prev = new Node{newKey, m_fake, nullptr};
        }
        else{
//            m_tail = new Node{newKey, nullptr, m_tail};
//            m_tail->prev->next = m_tail;
            m_fake->prev = new Node{newKey, m_fake, m_fake->prev};
            m_fake->prev->prev->next = m_fake->prev;
        }
        ++m_size;
    }
    void push_back(T&& newKey){
        if(!m_size){
            m_head = m_fake->prev = new Node{std::move(newKey), m_fake, nullptr};
        }
        else{
//            m_tail = new Node{std::move(newKey), nullptr, m_tail};\
//            m_tail->prev->next = m_tail;
            m_fake->prev = new Node{std::move(newKey), m_fake, m_fake->prev};
            m_fake->prev->prev->next = m_fake->prev;
        }
        ++m_size;
    }


    void pop_front(){
        assert(m_size);
        if(m_size == 1){
            delete m_head;
            m_fake->prev = m_head = nullptr;
        }
        else{
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;
        }
        --m_size;
    }

    void pop_back(){
        assert(m_size);
        if(m_size == 1){
            delete m_fake->prev;
            m_head = m_fake->prev = nullptr;
        }
        else{
            m_fake->prev = m_fake->prev->prev;
            delete m_fake->prev->next;
            m_fake->prev->next = m_fake;
        }
        --m_size;
    }

    void clear(){
        while(m_size){
            pop_back();
        }
    }

    T &operator[](int i){
        assert(i >= 0 && i < m_size);
        Node *chosenNode = m_head;
        while(i){
            chosenNode = chosenNode->next;
            --i;
        }
        return  chosenNode->key;
    }

    const T &operator[](int pos) const{
        assert(pos >= 0 && pos < m_size);
        Node *chosenNode = m_head;
        for(int i = 0; i < pos; ++i){
            chosenNode = chosenNode->next;
        }
        return  chosenNode->key;
    }

    void insert(const T &newKey, int pos){
        assert(pos >= 0 && pos <= m_size);

        if(!m_size) {
            m_fake->prev = m_head = new Node{newKey, m_fake, nullptr};
            ++m_size;
            return;
        }

        Node *insertingNode = m_head;
        for(int i = 0; i < pos; ++i){
            insertingNode = insertingNode->next;
        }

        Node *newNode;
        if(insertingNode == m_fake){
            newNode = new Node{newKey, m_fake, m_fake->prev};
        }
        else{
            newNode = new Node{newKey, insertingNode, insertingNode->prev};
        }

        if(newNode->prev){
            newNode->prev->next = newNode;
        }
        else{
            m_head = newNode;
        }

        newNode->next->prev = newNode;

        ++m_size;
    }


    void erase(int pos){
        assert(pos >= 0 && pos < m_size);

        Node *erasingNode = m_head;
        for(int i = 0; i < pos; ++i){
            erasingNode = erasingNode->next;
        }

        Node *tmp = erasingNode;
        if(erasingNode->prev){
            erasingNode->prev->next = erasingNode->next;
        }
        else{
            m_head = erasingNode->next;
        }

        erasingNode->next->prev = erasingNode->prev;


        delete tmp;

        --m_size;
    }
};

#endif //TASK1_LIST_H

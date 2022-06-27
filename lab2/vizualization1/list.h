#ifndef LIST_H
#define LIST_H

#include "shared_ptr.h"
#include "weak_ptr.h"
#include <cassert>
//#include <iostream>
//using namespace std;

template<class T>
class List{

    template<class S>
    struct Node{
        shared_ptr<Node<S>> next;
        weak_ptr<Node<S>> prev;
        S value;

        Node() = default;
    };

    shared_ptr<Node<T>> m_head, m_tail;
    int m_size;

public:
    List() : m_head(nullptr), m_tail(nullptr), m_size(0){}
    ~List(){}

    List(const List &) = delete;
    List &operator=(const List &) = delete;

    int size() const {return m_size;}

    void addHead(const T &value){
        auto temp = make_shared<Node<T>>();
//        shared_ptr<Node<T>> temp = new Node<T>();

        temp->prev.reset();
        temp->value = value;
        temp->next = m_head;

        if(m_head.get() != nullptr)
            m_head->prev = temp;

        if(m_size == 0)
            m_head = m_tail = temp;
        else
            m_head = temp;

        ++m_size;

//        temp.reset(nullptr);
    }

    void addTail(const T &value){
        auto temp = make_shared<Node<T>>();
//        shared_ptr<Node<T>> temp = new Node<T>();

        temp->prev = m_tail;
        temp->value = value;
        temp->next = nullptr;

        if(m_tail.get() != nullptr)
            m_tail->next = temp;

        if(m_size == 0)
            m_tail = m_head = temp;
        else
            m_tail = temp;

        ++m_size;

//        temp.reset(nullptr);
    }

    void insert(const T &value, int pos){
        assert(pos >= 0 && pos <= m_size);

        if(pos == 0){
            addHead(value);
            return;
        }
        if(pos == m_size){
            addTail(value);
            return;
        }


        shared_ptr<Node<T>> insNode = m_head;
        for(int i = 0; i < pos; ++i){
            insNode = m_head->next;
        }

        shared_ptr<Node<T>> prevInsNode = insNode->prev;

        auto newNode = make_shared<Node<T>>(); // make
//        shared_ptr<Node<T>> newNode = new Node<T>(); // make

        newNode->value = value;

        if(prevInsNode.get() != nullptr && m_size != 1)
            prevInsNode->next = newNode;

        newNode->prev = prevInsNode;
        newNode->next = insNode;
        insNode->prev = newNode;

        ++m_size;
    }


    void del(int pos){
        if(m_size == 0)
            return;

        assert(pos >= 0 && pos < m_size);

        shared_ptr<Node<T>> delNode = m_head;
        for(int i = 0; i < pos; ++i){
            delNode = delNode->next;
        }

        shared_ptr<Node<T>> prevDelNode = delNode->prev;
        shared_ptr<Node<T>> nextDelNode = delNode->next;

        if(prevDelNode.get() != nullptr && m_size != 1)
            prevDelNode->next = nextDelNode;
        if(prevDelNode.get() == nullptr)
            m_head = nextDelNode;

        if(nextDelNode.get() != nullptr && m_size != 1)
            nextDelNode->prev = prevDelNode;
        if(nextDelNode.get() == nullptr)
            m_tail = prevDelNode;



        --m_size;
    }

    const T &getElem(int pos){
        shared_ptr<Node<T>> receivedItem = m_head;
        for(int i = 0; i < pos; ++i){
            receivedItem = receivedItem->next;
        }

        return receivedItem->value;
    }

    void print(){
        shared_ptr<Node<T>> temp = m_head;
        for(int i = 0; i < m_size; ++i){
            std::cout << temp->value << std::endl;
            temp = temp->next;
        }
    }
};

#endif // LIST_H

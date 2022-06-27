#ifndef STACK_H
#define STACK_H

//#include <iostream>
//#include <memory>
#include <cassert>
#include "unique_ptr.h"
#include "move_and_forward.h"



template<class T>
class Stack{
    struct Node{
        unique_ptr<Node> next;
        T value;
        Node(unique_ptr<Node> next, const T &value)
            : next(move(next)), value(value){}
    };

    unique_ptr<Node> m_head = nullptr;
    int m_size = 0;


public:
    Stack(){}
    ~Stack(){}

    int size() const
    {
        return m_size;
    }

    bool empty() const{
        return m_size == 0;
    }




    Stack(const Stack &) = delete;
    Stack &operator=(const Stack &) = delete;


    void push(const T &value){
        if(m_head.get() == nullptr)
        {
            m_head = make_unique<Node>(nullptr, value);
        }
        else{
            m_head = make_unique<Node>(move(m_head), value);
        }
        ++m_size;
    }


    void pop(){
        if(m_size == 0){
            return;
        }
        else if(m_size == 1){
            m_head = nullptr;

        }
        else{
            m_head = move(m_head->next);
        }

        --m_size;
    }

    T &top(){
        assert(!empty());
        return m_head->value;
    }
    const T &top() const{
        assert(!empty());
        return m_head->value;
    }



    void print(){
        std::cout << m_head->value << '\n';
    }

};

//#include <memory>

//template <typename T>
//class Stack {

//private:
//    struct pointNode {
//        T data;
//        std::unique_ptr<pointNode> next;

//        pointNode(T n_data,std::unique_ptr<pointNode> ptr) : data(std::move(n_data)), next(std::move(ptr)) {}
//    };
//    std::unique_ptr<pointNode> head;
//public:
//    Stack() : head(nullptr) {}
//    Stack(const T& data);
//    Stack(const T& data, std::unique_ptr<pointNode> ptr);
//    void push(const T& data);

//};

//template <typename T>
//void Stack<T>::push(const T& data) {
//    head = std::make_unique<pointNode>(data,nullptr);

//}

#endif // STACK_H

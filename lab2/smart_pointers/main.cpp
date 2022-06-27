//#include <QCoreApplication>
#include <iostream>
#include "shared_ptr.h"
#include "unique_ptr.h"
#include "weak_ptr.h"
#include <chrono>
//#include <memory>
//using namespace std;


class Timer
{
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};


#include <string>

class Human
{
    std::string m_name;
    weak_ptr<Human> m_partner; // обратите внимание, здесь std::weak_ptr

public:

    Human(const std::string &name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Human()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(shared_ptr<Human> &h1, shared_ptr<Human> &h2)
    {
        if (!h1 || !h2)
            return false;

        h1->m_partner = h2;
        h2->m_partner = h1;

        std::cout << h1->m_name << " is now partnered with " << h2->m_name << "\n";

        return true;
    }

    const shared_ptr<Human> getPartner() const { return m_partner.lock(); } // используем метод lock() для конвертации std::weak_ptr в std::shared_ptr
    const std::string& getName() const { return m_name; }
};

struct A{
    A(){std::cout << "A()\n";}
    ~A(){std::cout << "~A()\n";}
};


#include <iostream>

class Item
{
public:
    weak_ptr<Item> m_ptr; // изначально пустой

    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
};

//int main()
//{
//    auto ptr1 = make_shared<Item>();

//    ptr1->m_ptr = ptr1; // m_ptr теперь является владельцем Item-а, членом которого он является сам

//    return 0;
//}




template<class T>
void foo(T &&t){
    std::cout << "\n";
}


int main()
{
//    auto anton = make_shared<Human>("Anton");
////    shared_ptr<Human> anton = new Human("Antor");
//    auto ivan = make_shared<Human>("Ivan");
////    shared_ptr<Human> ivan = new Human("Ivan");




//    partnerUp(anton, ivan);

//    auto partner = ivan->getPartner(); // передаем partner-у содержимое умного указателя, которым владеет ivan
//    std::cout << ivan->getName() << "'s partner is: " << partner->getName() << '\n';

//    char *a = new char[sizeof(Item)];
//    new (a) Item();
//    reinterpret_cast<Item *>(a)->~Item();
//    delete[] a;

    long long int n = 10000000;

    Timer t1;
    for(int i = 0; i < n; ++i){
//        std::shared_ptr<int> p(new int);
        auto p = std::make_shared<int>();
    }
    std::cout << t1.elapsed() << std::endl;


    Timer t2;
    for(int i = 0; i < n; ++i){
//        shared_ptr<int> p(new int);
        auto p = make_shared<int>();
    }
    std::cout << t2.elapsed() << std::endl;



    return 0;
}




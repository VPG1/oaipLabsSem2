#include "widget.h"
#include <deque>
#include <QApplication>
#include <iostream>
#include "deque.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();

//    Deque<int> d;
//    d.push_back(12);
//    d.push_back(13);
//    d.push_back(14);
//    d.push_back(15);
//    d.push_back(16);
//    d.push_back(17);

//    for(auto it = d.begin(); it != d.end(); ++it){
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;

//    d.pop_back();
//    d.pop_back();
//    d.pop_back();
//    d.pop_back();
//    d.pop_back();
//    d.pop_back();


//    for(auto it = d.begin(); it != d.end(); ++it){
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;

//    d.push_back(12);
//    d.push_back(13);
//    d.push_back(14);
//    d.push_back(15);
//    d.push_back(16);
//    d.push_back(17);

//    for(auto it = d.begin(); it != d.end(); ++it){
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;

//    return 0;
}

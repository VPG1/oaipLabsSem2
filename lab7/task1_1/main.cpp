#include "widget.h"
#include "my_map.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();

//    map<int, int> a;

////    a.insert({12, 12});
////    a.insert({11, 1324123});

////    a.insert({15, 12});
////    a.insert({14, 1324123});
////    a.insert({13, 1324123});
////    a.insert({16, 34254});

//    a.insert({14, 14});
//    a.insert({15, 15});
//    a.insert({13, 143243});
//    a.insert({12, 12});

////    for(auto it = --a.end(); it != --(a.begin()); --it){
////        qDebug() << *it;
////    }

////    for(auto el : a){
////        qDebug() << el;
////    }

//    auto it = a.find(13);

//    qDebug() << *it;


//    return 0;
}

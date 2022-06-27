#include "widget.h"
#include "listonarray.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
//    ListOnArray<int> listOnArray;
//    listOnArray.push_back(12);
//    listOnArray.push_back(13);
//    listOnArray.push_back(14);
//    listOnArray.push_front(11);

//    listOnArray.pop_front();
//    listOnArray.pop_back();
//    listOnArray.pop_back();
//    listOnArray.pop_front();

//    for(auto it = listOnArray.begin(); it != listOnArray.end(); ++it){
//        qDebug() << *it;
//    }
//    return 0;
}

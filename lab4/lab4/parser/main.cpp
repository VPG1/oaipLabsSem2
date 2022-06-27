#include "widget.h"
#include <QApplication>
#include "my_string.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();

//    vector<A> a;
//    a.insert(a.begin(), A(12, 12, 12));
//    a.emplace(a.begin(), 12, 12, 12);

//    string str;

//    str += "qwer";

//    if(str == "qwer"){
//        std::cout << "str " + str;
//    }

//    return 0;
}

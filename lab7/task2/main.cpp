#include "widget.h"
#include "my_bitset.h"
//#include <bitset>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();

////    int x = 12;

//    bitset<5> bts1;
//    bitset<5> bts2;

//    bts1.set(2);

//    bts1[0] = true;
//    bts2[1] = true;

//    std::cout << "bts1\tbts2\n";
//    std::cout << bts1.to_string() << "\t" << bts2.to_string() << "\n";
//    std::cout << (~bts1 | bts2).to_string();

//    unsigned char arr[1];

//    size_t pos = 2;

//    arr[pos / 8] |= (1u << (pos % 8));


//    return 0;
}

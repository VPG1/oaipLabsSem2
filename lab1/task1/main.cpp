#include "ship.h"
#include <QApplication>
#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ship ship;
    ship.setFixedSize(640, 480);

    ship.show();

    return a.exec();
}

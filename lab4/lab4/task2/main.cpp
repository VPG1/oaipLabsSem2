#include <QApplication>
#include <QDebug>
#include <iostream>
#include <vector>
#include "binarynum.h"
#include "widget.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   Widget w;
   w.show();

   return a.exec();
}

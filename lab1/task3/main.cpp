#include "widget.h"
#include "date.h"

#include "inputdialog.h"
#include <QApplication>
#include <iostream>
#include <iomanip>
#include <QDir>
#include <QFileDialog>


int main(int argc, char *argv[])
{



    QApplication app(argc, argv);
    Widget window;
    window.show();
    return app.exec();

}

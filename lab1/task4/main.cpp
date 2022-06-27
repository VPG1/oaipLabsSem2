#include <QApplication>
#include <QListView>
#include <QFileSystemModel>
#include "widget.h"
#include <QDir>
#include <fstream>
#include "car.h"
#include <string>

void createAndFillFile(){
    std::ofstream fout("cars.txt");
    assert(fout.is_open());
    fout << "z qwer qwer 1000 100 123 99\n";
    fout << "z qsfdr qwer 200 200 123 12\n";
    fout << "z qfs qweasr 500 50 50 50\n";
    fout << "a qwer qwer 1000 100 100 99\n";
    fout << "a qsfdr qwer 200 20 20 12\n";
    fout << "a qfs qweasr 500 50 50 50\n";
    fout << "v qwer qwer 1000 100 100 99\n";
    fout << "v qsfdr qwer 200 20 20 12\n";
    fout << "v qfs qweasr 500 50 50 50\n";
    fout.close();
}

int main(int argc, char *argv[])
{
    createAndFillFile();
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}

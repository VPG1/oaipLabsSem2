#include "widget.h"
#include "arraydialog.h"
#include <QApplication>
#include "binary_search_tree.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

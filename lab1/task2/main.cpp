#include "widget.h"
#include "rhombus.h"
#include "fivepointedstar.h"
#include "circle.h"
#include "sixpointedstar.h"
#include "eightpointedstar.h"
#include "triangle.h"
#include "hexagon.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "matrix.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();


    return a.exec();
}

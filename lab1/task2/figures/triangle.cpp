#include "triangle.h"

QPolygonF Triangle::getTrianglePolygon(const QPointF &centerPoint, int radius)
{
    QPolygonF hexagon;
    for(int i = 0; i < 3; ++i){
        double angle = 2 * M_PI * i / 3;
        hexagon << QPointF(centerPoint.x() + radius * cos(angle),
                          centerPoint.y() + radius * sin(angle));
    }
    return hexagon;
}

Triangle::Triangle(const QPoint &A, const QPoint &B, const QPoint &C, QAbstractGraphicsShapeItem *parent)
    : Polygon(QPolygonF() << A << B << C, parent)
{

}

Triangle::Triangle(const QPointF &centerPoint, int radius,
                   QAbstractGraphicsShapeItem *parent)
    : Polygon(getTrianglePolygon(centerPoint, radius), parent)
{

}




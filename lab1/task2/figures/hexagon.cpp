#include "hexagon.h"



QPolygonF Hexagon::getHexagonPolygon(const QPointF &centerPoint, int radius)
{
    QPolygonF hexagon;
    for(int i = 0; i < 6; ++i){
        double angle = M_PI * i / 3;
        hexagon << QPointF(centerPoint.x() + radius * cos(angle),
                          centerPoint.y() + radius * sin(angle));
    }
    return hexagon;
}

Hexagon::Hexagon(const QPointF &centerPoint,
                 int radius, QAbstractGraphicsShapeItem *parent)
    : Polygon(getHexagonPolygon(centerPoint, radius), parent)
{

}

Hexagon::Hexagon(const QPoint &A, const QPoint &B, const QPoint &C,
                 const QPoint &D, const QPoint &E, const QPoint &F,
                 QAbstractGraphicsShapeItem *parent)
    : Polygon(QPolygonF() << A << B << C
                         << D << E << F,
              parent)
{

}

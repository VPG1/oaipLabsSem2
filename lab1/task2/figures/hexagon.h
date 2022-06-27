#ifndef HEXAGON_H
#define HEXAGON_H

#include "polygon.h"

class Hexagon : public Polygon
{
private:
    static QPolygonF getHexagonPolygon(const QPointF &centerPoint, int radius);
public:
    Hexagon(const QPointF &centerPoint, int radius,
            QAbstractGraphicsShapeItem *parent = nullptr);

    Hexagon(const QPoint &A, const QPoint &B, const QPoint &C,
            const QPoint &D, const QPoint &E, const QPoint &F,
            QAbstractGraphicsShapeItem *parent = nullptr);
};

#endif // HEXAGON_H

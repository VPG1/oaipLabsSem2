#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"
#include <QPolygonF>
#include <QList>

class Triangle : public Polygon
{
    QPolygonF getTrianglePolygon(const QPointF &centerPoint, int radius);
public:
//    Triangle() = default;
    Triangle(const QPoint &A, const QPoint &B, const QPoint &C,
             QAbstractGraphicsShapeItem *parent = nullptr);
    Triangle(const QPointF &centerPoint, int radius,
             QAbstractGraphicsShapeItem *parent = nullptr);
};

#endif // TRIANGLE_H

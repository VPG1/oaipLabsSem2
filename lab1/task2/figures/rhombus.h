#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "polygon.h"

class Rhombus : public Polygon
{
private:
    long double m_horizontalDiagonal;
    long double m_verticalDiagonal;
    QPointF m_centerPoint;

    static QPolygonF getRhomubusPolygon(const QPointF &centerPoint,
                                       int horizontalDiagonal,
                                       int verticalDiagonal);
public:
    Rhombus(const QPointF &centerOfRhombus,
            int horizontalDiagonal, int verticalDiagonal,
            QGraphicsItem *parent = nullptr);
    int horizontalDiagonal() const;
    int verticalDiagonal() const;
    void setHorizontalDiagonal(int newHorizontalDiagonal);
    void setVerticalDiagonal(int newVerticalDiagonal);

    void scaling(long double scalingFactor, const QPointF &markerPoint) override;
};

#endif // RHOMBUS_H

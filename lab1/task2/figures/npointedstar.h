#ifndef NPOINTEDSTAR_H
#define NPOINTEDSTAR_H

#include "polygon.h"

class NPointedStar : public Polygon
{
private:
    long double m_innerRadius;
    long double m_outerRadius;
    int m_n;
    QPointF m_center;
    static QPolygonF starPolygon(const QPointF &center, int innerRadius,
                                int outerRadius, int n);

public:
    NPointedStar(const QPointF &center,
                 int innerRadius, int outerRadius,
                 int n, QGraphicsItem *parent);
    int innerRadius() const;
    int outerRadius() const;
    void setInnerRadius(int newInnerRadius);
    void setOuterRadius(int newOuterRadius);

    void scaling(long double scalingFactor, const QPointF &markerPoint) override;
};

#endif // NPOINTEDSTAR_H

#include "npointedstar.h"
#define _USE_MATH_DEFINES
#include <cmath>


int NPointedStar::innerRadius() const
{
    return m_innerRadius;
}

int NPointedStar::outerRadius() const
{
    return m_outerRadius;
}

void NPointedStar::setInnerRadius(int newInnerRadius)
{
    m_innerRadius = newInnerRadius;
    setPolygon(starPolygon(m_center, m_innerRadius, m_outerRadius, m_n));
}

void NPointedStar::setOuterRadius(int newOuterRadius)
{
    m_outerRadius = newOuterRadius;
    setPolygon(starPolygon(m_center, m_innerRadius, m_outerRadius, m_n));
}

void NPointedStar::scaling(long double scalingFactor, const QPointF &markerPoint)
{
    m_innerRadius *= scalingFactor;
    m_outerRadius *= scalingFactor;
    Polygon::scaling(scalingFactor, markerPoint);
}

QPolygonF NPointedStar::starPolygon(const QPointF &center, int innerRadius,
                                   int outerRadius, int n)
{
    QPolygonF star;
    for(int i = 0; i < n; ++i){
        double angle = 2 * M_PI * i / n;
        star << QPointF(center.x() + innerRadius * cos(angle),
                         center.y() + innerRadius * sin(angle))
               << QPointF(center.x() + outerRadius * cos(angle + M_PI / n),
                         center.y() + outerRadius * sin(angle + M_PI / n));
    }
    return star;
}

NPointedStar::NPointedStar(const QPointF &center,
                           int innerRadius, int outerRadius,
                           int n, QGraphicsItem *parent)
    : Polygon(starPolygon(center, innerRadius, outerRadius, n), parent),
      m_innerRadius(innerRadius), m_outerRadius(outerRadius), m_n(n), m_center(center)
{
}

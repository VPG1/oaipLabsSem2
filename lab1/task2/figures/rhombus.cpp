#include "rhombus.h"
#include <QApplication>

int Rhombus::horizontalDiagonal() const
{
    return m_horizontalDiagonal;
}

int Rhombus::verticalDiagonal() const
{
    return m_verticalDiagonal;
}

void Rhombus::setHorizontalDiagonal(int newHorizontalDiagonal)
{
    m_horizontalDiagonal = newHorizontalDiagonal;
    setPolygon(getRhomubusPolygon(m_centerPoint,
                                  m_horizontalDiagonal, m_verticalDiagonal));
}

void Rhombus::setVerticalDiagonal(int newVerticalDiagonal)
{
    m_verticalDiagonal = newVerticalDiagonal;
    setPolygon(getRhomubusPolygon(m_centerPoint,
                                  m_horizontalDiagonal, m_verticalDiagonal));
}

void Rhombus::scaling(long double scalingFactor, const QPointF &markerPoint)
{
    m_horizontalDiagonal *= scalingFactor;
    m_verticalDiagonal *= scalingFactor;
    Polygon::scaling(scalingFactor, markerPoint);
}

QPolygonF Rhombus::getRhomubusPolygon(const QPointF &centerOfRhombus,
                                     int horizontalDiagonal,
                                     int verticalDiagonal)
{
    return QPolygonF()<< QPointF(centerOfRhombus.x() - horizontalDiagonal / 2, centerOfRhombus.y())
                     << QPointF(centerOfRhombus.x(), centerOfRhombus.y() - verticalDiagonal / 2)
                     << QPointF(centerOfRhombus.x() + horizontalDiagonal / 2, centerOfRhombus.y())
                     << QPointF(centerOfRhombus.x(), centerOfRhombus.y() + verticalDiagonal / 2);
}

Rhombus::Rhombus(const QPointF &centerOfRhombus,
                 int horizontalDiagonal, int verticalDiagonal,
                 QGraphicsItem *parent)
    : Polygon(getRhomubusPolygon(centerOfRhombus, horizontalDiagonal, verticalDiagonal)
              , parent), m_horizontalDiagonal(horizontalDiagonal), m_verticalDiagonal(verticalDiagonal),
      m_centerPoint(centerOfRhombus)
{

}

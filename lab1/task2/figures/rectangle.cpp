#include "rectangle.h"

int Rectangle::width() const
{
    return m_width;
}

int Rectangle::height() const
{
    return m_height;
}

void Rectangle::setWidth(int newWidth)
{
    m_width = newWidth;
    setPolygon(getRectanglePolygon(polygon()[0], m_width, m_height));
}

void Rectangle::setHeight(int newHeight)
{
    m_height = newHeight;
    setPolygon(getRectanglePolygon(polygon()[0], m_width, m_height));
}

QPolygonF Rectangle::getRectanglePolygon(const QPointF &point, int width, int height)
{
    return QPolygonF() << point
                      << QPoint(point.x(), point.y() + height)
                      << QPoint(point.x() + width, point.y() + height)
                      << QPoint(point.x() + width, point.y());
}

Rectangle::Rectangle(const QPointF &point, int width, int height, QGraphicsItem *parent)
    : Polygon(getRectanglePolygon(point, width, height), parent), m_width(width), m_height(height)
{

}

void Rectangle::scaling(long double scalingFactor, const QPointF &markerPoint)
{
    m_width *= scalingFactor;
    m_height *= scalingFactor;
    Polygon::scaling(scalingFactor, markerPoint);
}

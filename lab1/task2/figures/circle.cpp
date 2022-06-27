#include "circle.h"
#include <QPainter>


long double Circle::radius() const
{
    return m_radius;
}

void Circle::setCircleRadius(int newRadius)
{
    m_radius = newRadius;
}

QPointF Circle::center() const
{
    return m_center;
}

Circle::Circle(const QPointF &center, int radius, QGraphicsItem *parent)
    : Shape(parent), m_radius(radius), m_center(center)
{

}

double Circle::area()
{
    return M_PI * m_radius * m_radius;
}

double Circle::perimeter()
{
    return 2 * M_PI * m_radius;
}

QPointF Circle::centerOfGravity()
{
    return m_center;
}

void Circle::setMatrix(const Matrix &matrix)
{
    m_center = (matrix * Matrix(m_center)).getVectorPoint();
}

void Circle::moving(long double dx, long double dy)
{
    m_center.rx() += dx;
    m_center.ry() += dy;
}

void Circle::scaling(long double frameScalingFactor, const QPointF &markerPoint)
{
    setMatrix(Matrix(frameScalingFactor, 0, markerPoint.x() * (1 - frameScalingFactor),
                     0, frameScalingFactor, markerPoint.y() * (1 - frameScalingFactor),
                     0, 0, 1));
    m_radius *= frameScalingFactor * frameScalingFactor;
}


void Circle::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *, QWidget *)
{
    qDebug() << "paint";
    pPainter->save();
    pPainter->setPen(QPen(Qt::blue, nPenWidth));
    pPainter->drawEllipse(m_center, m_radius, m_radius);
    pPainter->restore();
}

QRectF Circle::boundingRect() const
{
    return QRect(-150, -150, 2500, 2500);
}

void Circle::updateRect(int width, int weight)
{
    update(m_center.x() - m_radius - 5, m_center.y() - m_radius - 5,
           2 * m_radius + 10 , 2 * m_radius + 10);
}

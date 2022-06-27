#include "polygon.h"
#include <QPainter>
#include <QRect>

Polygon::Polygon(const QPolygonF &polygon, QGraphicsItem *parent)
    : Shape(parent), m_polygon(polygon)
{

}

void Polygon::setPolygon(const QPolygonF &newPolygon)
{
    m_polygon = newPolygon;
}

void Polygon::fillMatrixOfPolygon(int (*matrix)[2])
{
    for(int i = 0; i < m_polygon.size() + 1; ++i){
        matrix[i][0] = m_polygon[i % m_polygon.size()].x();
        matrix[i][1] = m_polygon[i % m_polygon.size()].y();
    }
}


double Polygon::area()
{
    int matrix[m_polygon.size() + 1][2];
    fillMatrixOfPolygon(matrix);

    int firstSum = 0;
    for(int i = 0; i < m_polygon.size(); ++i){
        firstSum += matrix[i][0] * matrix[i + 1][1];
    }

    int secondSum = 0;
    for(int i = 0; i < m_polygon.size(); ++i){
        secondSum += matrix[i + 1][0] * matrix[i][1];
    }

    return 0.5 * abs(secondSum - firstSum);
}

double Polygon::perimeter()
{
    int matrix[m_polygon.size() + 1][2];
    fillMatrixOfPolygon(matrix);

    double sum = 0;
    for(int i = 0; i < m_polygon.size(); ++i){
        sum += sqrt(pow(matrix[i][0] - matrix[i + 1][0], 2)
                + pow(matrix[i][1] - matrix[i + 1][1], 2));
    }
    return sum;
}

QPointF Polygon::centerOfGravity()
{
    int matrix[m_polygon.size() + 1][2];
    fillMatrixOfPolygon(matrix);

    long double xSum = 0;
    long double ySum = 0;
    for(int i = 0; i < m_polygon.size(); ++i){
        long double  distance = sqrt(pow(matrix[i][0] - matrix[i + 1][0], 2)
                + pow(matrix[i][1] - matrix[i + 1][1], 2));
        xSum += ((matrix[i + 1][0] + matrix[i][0]) / 2.0) * distance;
        ySum += ((matrix[i + 1][1] + matrix[i][1]) / 2.0) * distance;
    }

    int perimeterValue = perimeter();
    return QPointF(xSum / perimeterValue, ySum / perimeterValue);
}

void Polygon::setMatrix(const Matrix &matrix)
{
    for(int i = 0; i < m_polygon.size(); ++i){
        m_polygon[i] = (matrix * Matrix(m_polygon[i])).getVectorPoint();
        qDebug() << Matrix(m_polygon[i]).getVectorPoint();
    }
}

void Polygon::moving(long double dx, long double dy)
{
    m_polygon.translate(dx, dy);
}

void Polygon::scaling(long double frameScalingFactor, const QPointF &markerPoint)
{
    setMatrix(Matrix(frameScalingFactor, 0, markerPoint.x() * (1 - frameScalingFactor),
                     0, frameScalingFactor, markerPoint.y() * (1 - frameScalingFactor),
                     0, 0, 1));
}



void Polygon::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *, QWidget *)
{
    pPainter->save();
    pPainter->setPen(QPen(Qt::blue, nPenWidth));
    pPainter->drawPolygon(m_polygon);
    pPainter->restore();
}

QRectF Polygon::boundingRect() const
{
//    QRectF boundingRect = m_polygon.boundingRect();
    return QRectF(-150, -150, 2500, 2500);
//    return QRectF(boundingRect.x() - 5, boundingRect.y() - 5,
//                  boundingRect.width() + 10, boundingRect.height() + 10);
}

void Polygon::updateRect(int width, int height)
{
//    QRectF boundingRect = m_polygon.boundingRect();
    update(-100, -100, width, height);
}


QPolygonF Polygon::polygon()
{
    return m_polygon;
}

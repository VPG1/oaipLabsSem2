#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
    long double m_radius;
    QPointF m_center;
public:
    Circle(const QPointF &center, int radius, QGraphicsItem *parent = nullptr);

    double area() override;
    double perimeter() override;
    QPointF centerOfGravity() override;
    void setMatrix(const Matrix& matrix) override;
    void moving(long double dx, long double dy) override;
    void scaling(long double scalingFactor, const QPointF &markerPoint) override;

    void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;
    void updateRect(int width, int height) override;

    long double radius() const;
    void setCircleRadius(int newRadius);
    QPointF center() const;
};

#endif // CIRCLE_H

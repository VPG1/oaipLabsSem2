#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
private:
    QPolygonF m_polygon;

    void fillMatrixOfPolygon(int (*matrix)[2]);

public:
    Polygon(const QPolygonF &polygon, QGraphicsItem *parent = nullptr);

    double area() override;
    double perimeter() override;
    QPointF centerOfGravity() override;
    void setMatrix(const Matrix &matrix) override;
    void moving(long double dx, long double dy) override;
    void scaling(long double scalingFactor, const QPointF &markerPoint) override;


    void paint(QPainter *pPainter,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;
    QRectF boundingRect() const override;
    void updateRect(int width, int height) override;

    QPolygonF polygon();
    void setPolygon(const QPolygonF &newPolygon);
};

#endif // POLYGON_H

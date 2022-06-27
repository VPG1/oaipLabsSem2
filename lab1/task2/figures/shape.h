#ifndef SHAPE_H
#define SHAPE_H

#include <QAbstractGraphicsShapeItem>
#include "matrix.h"

class Shape : public QAbstractGraphicsShapeItem
{
protected:
    enum{nPenWidth = 3};

public:
    enum FigureType{
        TRIANGLE,
        RECTANGLE,
        RHOMBUS,
        SQUARE,
        FIVE_POINTED_STAR,
        SIX_POINTED_STAR,
        EIGHT_POINTED_STAR,
        HEXAGON,
        CIRCLE,
        NUMBER_OF_FIGURE
    };
    enum VertexName{
        A, B, C, D, E, F
    };


    Shape(QGraphicsItem *parent = nullptr);
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual QPointF centerOfGravity() = 0;
    virtual void setMatrix(const Matrix &matrix) = 0;
    virtual void moving(long double dx, long double dy) = 0;
    virtual void scaling(long double scalingFactor, const QPointF &markerPos) = 0;

    virtual void updateRect(int width, int height) = 0;
};

#endif // SHAPE_H

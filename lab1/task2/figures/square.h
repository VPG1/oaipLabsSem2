#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle
{
public:
    Square(const QPointF &A, int length, QGraphicsItem *parent = nullptr);
    void setLength(int newLenght);
    int length();
};

#endif // SQUARE_H

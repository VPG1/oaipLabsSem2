#include "square.h"

void Square::setLength(int newLenght)
{
    setWidth(newLenght);
    setHeight(newLenght);
}

int Square::length()
{
    return width();
}

Square::Square(const QPointF &A, int length, QGraphicsItem *parent)
    : Rectangle(A, length, length, parent)
{

}

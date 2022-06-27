#include "ship.h"

Ship::Ship(QWidget *parent) : MovingRectangle(parent)
{

}

void Ship::paintEvent(QPaintEvent *event)
{
    MovingRectangle::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::black));

//    static const int startWidth = width();
//    static const int startHeight = height();
//    painter.scale(1.0 * width() / width(), 1.0 * height() / startHeight);

    QPolygon frame;
    frame << QPoint(width() / 2 - 200, height() / 2)
          << QPoint(width() / 2 - 100, height() / 2 + 100)
          << QPoint(width() / 2 + 100, height() / 2 + 100)
          << QPoint(width() / 2 + 200, height() / 2);

    painter.drawPolygon(frame);
    painter.drawRect(width() / 2 - 10, 10, 20 ,height() / 2);

}


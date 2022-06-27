#include "movingrectangle.h"



MovingRectangle::MovingRectangle(QWidget *parent)
    : QWidget(parent), rect(width() / 2 - 100, height() / 2, 100, 50)
{
}


void MovingRectangle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::black));

//    static const int startWidth = width();
//    static const int startHeight = height();
//    painter.translate(rect.x() + width() - startWidth, rect.y() + height() - startHeight);
//    painter.scale(1.0 * width() / startWidth, 1.0 * height() / startHeight);

    painter.drawRect(rect);
}

void MovingRectangle::keyPressEvent(QKeyEvent *pKeyEvent)
{
    static const int step = 10;

    if(pKeyEvent->key() == Qt::Key_Up && rect.y() > 20){
        rect.moveTo(rect.x(), rect.y() - step);
        repaint();
    }
    if(pKeyEvent->key() == Qt::Key_Down && rect.y() < (height() / 2)){
        rect.moveTo(rect.x(), rect.y() + step);
        repaint();
    }
}


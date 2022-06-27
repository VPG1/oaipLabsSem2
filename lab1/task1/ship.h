#ifndef SHIP_H
#define SHIP_H

#include "movingrectangle.h"

class Ship : public MovingRectangle
{
public:
    Ship(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *) override;

};

#endif // SHIP_H

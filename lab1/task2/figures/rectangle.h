#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

class Rectangle : public Polygon
{
private:
    long double m_width;
    long double m_height;

    static QPolygonF getRectanglePolygon(const QPointF &point, int width, int height);

public:
    Rectangle(const QPointF &point, int width, int height, QGraphicsItem *parent = nullptr);
    void scaling(long double scalingFactor, const QPointF &markerPoint) override;

    int width() const;
    int height() const;
    void setWidth(int newWidth);
    void setHeight(int newHeight);
};

#endif // RECTANGLE_H

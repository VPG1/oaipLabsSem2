#include "rect.h"

int &Rect::x() const
{
    return m_x;
}

int &Rect::y() const
{
    return m_y;
}

int &Rect::width() const
{
    return m_width;
}

int &Rect::height() const
{
    return m_height;
}

Rect::Rect(int &x, int &y, int &width, int &height)
    : m_x(x), m_y(y), m_width(width), m_height(height){}

void Rect::moveTop(int step){
    m_x -= step;
}

void Rect::moveBottom(int step){
    m_y += step;
}

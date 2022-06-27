#ifndef RECT_H
#define RECT_H


class Rect
{
private:
    int &m_x;
    int &m_y;
    int m_width;
    int m_height;
public:
    Rect() = delete;
    Rect(int &x, int &y, int &width, int &height);

    void moveTop(int step);
    void moveBottom(int step);

    int &x() const;
    int &y() const;
    int &width() const;
    int &height() const;
};

#endif // RECT_H

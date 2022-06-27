#ifndef MOVINGRECTANGLE_H
#define MOVINGRECTANGLE_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>

class MovingRectangle : public QWidget
{
    Q_OBJECT

public:
    MovingRectangle(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent* pKeyEvent) override;

private:
    QRect rect;
};

#endif // MOVINGRECTANGLE_H

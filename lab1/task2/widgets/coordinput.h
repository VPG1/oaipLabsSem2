#ifndef COORDINPUT_H
#define COORDINPUT_H

#include <QWidget>
#include <QSpinBox>
#include "abstractadjustmentwidget.h"

class CoordInput : public QWidget
{
    Q_OBJECT
private:
    Shape::VertexName m_vertex;
    QSpinBox *pSpinBoxX;
    QSpinBox *pSpinBoxY;
public:
    CoordInput(Shape::VertexName numberOfCoords, QWidget *parent = nullptr);
    void setCoordValues(int valueX, int valueY);
signals:
    void valueXChanged(int, Shape::VertexName);
    void valueYChanged(int, Shape::VertexName);
public slots:
    void intermediateXSlot(int x);
    void intermediateYSlot(int y);

};

#endif // COORDINPUT_H

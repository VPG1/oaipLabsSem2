#ifndef ABSTRACTADJUSTMENTWIDGET_H
#define ABSTRACTADJUSTMENTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>
#include "shape.h"
#include "npointedstar.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "coordinput.h"

class AbstractAdjustmentWidget : public QWidget
{
    Q_OBJECT
protected:
    Shape *m_pShape;
public:
    enum NumberOfVertexType{
        NUMBER_OF_TRIANGLE_VERTEX = 3,
        NUMBER_OF_HEXAGON_VERTEX = 6
    };

    AbstractAdjustmentWidget(Shape *pShape, QWidget *parent = nullptr);

    void repaintItem();

    virtual void updateWidget() = 0;
signals:
    void parametersIsChanged(Shape::FigureType);
};

#endif // ABSTRACTADJUSTMENTWIDGET_H

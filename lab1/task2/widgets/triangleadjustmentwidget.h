#ifndef TRIANGLEADJUSTMENTWIDGET_H
#define TRIANGLEADJUSTMENTWIDGET_H

#include "abstractadjustmentwidget.h"
#include "coordinput.h"

class TriangleAdjustmentWidget : public AbstractAdjustmentWidget
{
    Q_OBJECT
private:
    CoordInput **pCoordInputArray;
public:
    TriangleAdjustmentWidget(Shape *pShape, QWidget *parent = nullptr);

    void updateWidget() override;

public slots:
    void updateXCoord(int valueX, Shape::VertexName vertex);
    void updateYCoord(int valueY, Shape::VertexName vertex);

};

#endif // TRIANGLEADJUSTMENTWIDGET_H

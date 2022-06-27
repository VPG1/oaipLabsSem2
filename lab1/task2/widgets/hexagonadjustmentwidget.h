#ifndef HEXAGONADJUSTMENTWIDGET_H
#define HEXAGONADJUSTMENTWIDGET_H

#include "abstractadjustmentwidget.h"


class HexagonAdjustmentWidget : public AbstractAdjustmentWidget
{
    Q_OBJECT
private:
    CoordInput **pCoordInputArray;
public:
    HexagonAdjustmentWidget(Shape *shape, QWidget *parent = nullptr);

    void updateWidget() override;

public slots:
    void updateXCoord(int valueX, Shape::VertexName vertex);
    void updateYCoord(int valueY, Shape::VertexName vertex);
};

#endif // HEXAGONADJUSTMENTWIDGET_H

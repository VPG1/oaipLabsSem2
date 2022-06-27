#ifndef RECTANGLEADJUSTMENTWIDGET_H
#define RECTANGLEADJUSTMENTWIDGET_H

#include "abstractadjustmentwidget.h"

class RectangleAdjustmentWidget : public AbstractAdjustmentWidget
{
    Q_OBJECT
private:
    QSpinBox *pSpinBoxSide1;
    QSpinBox *pSpinBoxSide2;
public:
    RectangleAdjustmentWidget(Shape *pShape, QWidget *parent = nullptr);

    void updateWidget() override;

public slots:
    void updateWidth(int newWidth);
    void updateHeight(int newHeight);
};

#endif // RECTANGLEADJUSTMENTWIDGET_H

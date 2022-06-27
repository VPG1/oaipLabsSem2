#ifndef CIRCLEADJUSTMENTWIDET_H
#define CIRCLEADJUSTMENTWIDET_H

#include "abstractadjustmentwidget.h"

class CircleAdjustmentWidet : public AbstractAdjustmentWidget
{
    Q_OBJECT
private:
    QSpinBox *pSpinBoxRadius;
public:
    CircleAdjustmentWidet(Shape *shape, QWidget *parent = nullptr);

    void updateWidget() override;

public slots:
    void updateCircle(int newRadius);

};

#endif // CIRCLEADJUSTMENTWIDET_H

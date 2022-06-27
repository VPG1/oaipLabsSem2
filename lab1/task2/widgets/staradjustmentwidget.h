#ifndef STARADJUSTMENTWIDGET_H
#define STARADJUSTMENTWIDGET_H

#include "abstractadjustmentwidget.h"
#include "npointedstar.h"

class StarAdjustmentWidget : public AbstractAdjustmentWidget
{
    Q_OBJECT
private:
    QSpinBox *pSpinBoxInnerRadius;
    QSpinBox *pSpinBoxOuterRadius;
public:
    StarAdjustmentWidget(Shape *shape, QWidget *parent = nullptr);

    void updateWidget() override;

public slots:
    void updateInnerRadius(int newInnerRadius);
    void updateOuterRadius(int newOuterRadius);
};

#endif // STARADJUSTMENTWIDGET_H

#ifndef RHOMBUSADJUSTMENTWIDGET_H
#define RHOMBUSADJUSTMENTWIDGET_H

#include "abstractadjustmentwidget.h"
#include "shape.h"

class RhombusAdjustmentWidget : public AbstractAdjustmentWidget
{
    Q_OBJECT
private:
    QSpinBox *pSpinBoxDiagonal1;
    QSpinBox *pSpinBoxDiagonal2;
public:
    RhombusAdjustmentWidget(Shape *shape, QWidget *parent = nullptr);

    void updateWidget() override;

public slots:
    void updateHorizontalDiagonal(int newHorizontalDiagonal);
    void updateVerticalDiagonal(int newVerticalDiagonal);
};

#endif // RHOMBUSADJUSTMENTWIDGET_H

#ifndef SQUAREADJUSTMENTWIDGET_H
#define SQUAREADJUSTMENTWIDGET_H

#include "abstractadjustmentwidget.h"

class SquareAdjustmentWidget : public AbstractAdjustmentWidget
{
    Q_OBJECT
private:
    QSpinBox *pSpinBoxLength;
public:
    SquareAdjustmentWidget(Shape *pShape, QWidget *parent = nullptr);

    void updateWidget();

public slots:
    void updateLength(int newLenght);
};

#endif // SQUAREADJUSTMENTWIDGET_H

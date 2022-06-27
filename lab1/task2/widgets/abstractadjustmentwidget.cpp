#include "abstractadjustmentwidget.h"


AbstractAdjustmentWidget::AbstractAdjustmentWidget(Shape *pShape, QWidget *parent)
    : QWidget(parent), m_pShape(pShape)
{

}

void AbstractAdjustmentWidget::repaintItem()
{
    m_pShape->update();
}


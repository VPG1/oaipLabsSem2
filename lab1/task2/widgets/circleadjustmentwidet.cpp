#include "circleadjustmentwidet.h"
#include "circle.h"

CircleAdjustmentWidet::CircleAdjustmentWidet(Shape *pShape, QWidget *parent)
    : AbstractAdjustmentWidget(pShape, parent)
{
    QGridLayout *pMainLayout = new QGridLayout;

    Circle *pCircle = dynamic_cast<Circle *>(pShape);
    pSpinBoxRadius = new QSpinBox;
    pSpinBoxRadius->setRange(0, 1000);
    pSpinBoxRadius->setValue(pCircle->radius());

    pMainLayout->addWidget(new QLabel("radius:"), 0, 0);
    pMainLayout->addWidget(pSpinBoxRadius, 0, 1);

    setLayout(pMainLayout);

    connect(pSpinBoxRadius, SIGNAL(valueChanged(int)), SLOT(updateCircle(int)));
}

void CircleAdjustmentWidet::updateCircle(int newRadius)
{
    dynamic_cast<Circle *>(m_pShape)->setCircleRadius(newRadius);
    repaintItem();

    emit parametersIsChanged(Shape::CIRCLE);
}

void CircleAdjustmentWidet::updateWidget()
{
    pSpinBoxRadius->setValue(dynamic_cast<Circle *>(m_pShape)->radius());
}

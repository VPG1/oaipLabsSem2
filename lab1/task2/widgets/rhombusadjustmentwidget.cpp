#include "rhombusadjustmentwidget.h"
#include "rhombus.h"

RhombusAdjustmentWidget::RhombusAdjustmentWidget(Shape *pShape, QWidget *parent)
    : AbstractAdjustmentWidget(pShape, parent)
{
    QGridLayout *pMainLayout = new QGridLayout;

    Rhombus *pRhombus = dynamic_cast<Rhombus *>(pShape);

    pSpinBoxDiagonal1 = new QSpinBox;
    pSpinBoxDiagonal1->setRange(0, 1000);
    pSpinBoxDiagonal1->setValue(pRhombus->horizontalDiagonal());

    pSpinBoxDiagonal2 = new QSpinBox;
    pSpinBoxDiagonal2->setRange(0, 1000);
    pSpinBoxDiagonal2->setValue(pRhombus->verticalDiagonal());


    pMainLayout->addWidget(pSpinBoxDiagonal1, 0, 1);
    pMainLayout->addWidget(new QLabel("side 1"), 0, 0);

    pMainLayout->addWidget(pSpinBoxDiagonal2, 1, 1);
    pMainLayout->addWidget(new QLabel("side 2"), 1, 0);

    setLayout(pMainLayout);

    connect(pSpinBoxDiagonal1, SIGNAL(valueChanged(int)),
            SLOT(updateHorizontalDiagonal(int)));
    connect(pSpinBoxDiagonal2, SIGNAL(valueChanged(int)),
            SLOT(updateVerticalDiagonal(int)));
}

void RhombusAdjustmentWidget::updateHorizontalDiagonal(int newHorizontalDiagonal)
{
    dynamic_cast<Rhombus *>(m_pShape)->setHorizontalDiagonal(newHorizontalDiagonal);
    repaintItem();

    emit parametersIsChanged(Shape::RHOMBUS);
}

void RhombusAdjustmentWidget::updateVerticalDiagonal(int newVerticalDiagonal)
{
    dynamic_cast<Rhombus *>(m_pShape)->setVerticalDiagonal(newVerticalDiagonal);
    repaintItem();

    emit parametersIsChanged(Shape::RHOMBUS);
}

void RhombusAdjustmentWidget::updateWidget()
{
    pSpinBoxDiagonal1->
            setValue(dynamic_cast<Rhombus *>(m_pShape)->horizontalDiagonal());
    pSpinBoxDiagonal2->
            setValue(dynamic_cast<Rhombus *>(m_pShape)->verticalDiagonal());
}

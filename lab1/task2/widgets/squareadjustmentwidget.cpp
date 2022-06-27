#include "squareadjustmentwidget.h"
#include "square.h"

SquareAdjustmentWidget::SquareAdjustmentWidget(Shape *pShape, QWidget *parent)
    : AbstractAdjustmentWidget(pShape, parent)
{
    QGridLayout *pMainLayout = new QGridLayout;

    Square *pSquare = dynamic_cast<Square *>(pShape);
    pSpinBoxLength = new QSpinBox;
    pSpinBoxLength->setRange(0, 1000);
    pSpinBoxLength->setValue(pSquare->length());

    pMainLayout->addWidget(pSpinBoxLength, 0, 1);
    pMainLayout->addWidget(new QLabel("side"), 0, 0);

    setLayout(pMainLayout);

    connect(pSpinBoxLength, SIGNAL(valueChanged(int)), SLOT(updateLength(int)));
}

void SquareAdjustmentWidget::updateLength(int newLenght)
{
    dynamic_cast<Square *>(m_pShape)->setLength(newLenght);
    repaintItem();

    emit parametersIsChanged(Shape::SQUARE);
}

void SquareAdjustmentWidget::updateWidget()
{
    pSpinBoxLength->setValue(dynamic_cast<Square *>(m_pShape)->length());
}

#include "rectangleadjustmentwidget.h"
#include "rectangle.h"


RectangleAdjustmentWidget::RectangleAdjustmentWidget(Shape *pShape, QWidget *parent)
    : AbstractAdjustmentWidget(pShape, parent)
{
    QGridLayout *pMainLayout = new QGridLayout;


    Rectangle *pRectangle = dynamic_cast<Rectangle *>(pShape);

    pSpinBoxSide1 = new QSpinBox;
    pSpinBoxSide1->setRange(0, 1000);
    pSpinBoxSide1->setValue(pRectangle->width());

    pSpinBoxSide2 = new QSpinBox;
    pSpinBoxSide2->setRange(0, 1000);
    pSpinBoxSide2->setValue(pRectangle->height());


    pMainLayout->addWidget(pSpinBoxSide1, 0, 1);
    pMainLayout->addWidget(new QLabel("side 1"), 0, 0);

    pMainLayout->addWidget(pSpinBoxSide2, 1, 1);
    pMainLayout->addWidget(new QLabel("side 2"), 1, 0);

    setLayout(pMainLayout);

    connect(pSpinBoxSide1, SIGNAL(valueChanged(int)),
            SLOT(updateWidth(int)));
    connect(pSpinBoxSide2, SIGNAL(valueChanged(int)),
            SLOT(updateHeight(int)));
}

void RectangleAdjustmentWidget::updateWidth(int newWidth)
{
    dynamic_cast<Rectangle *>(m_pShape)->setWidth(newWidth);

    repaintItem();

    emit parametersIsChanged(Shape::RECTANGLE);
}

void RectangleAdjustmentWidget::updateHeight(int newHeight)
{
    dynamic_cast<Rectangle *>(m_pShape)->setHeight(newHeight);
    repaintItem();

    emit parametersIsChanged(Shape::RECTANGLE);
}

void RectangleAdjustmentWidget::updateWidget()
{
    pSpinBoxSide1->setValue(dynamic_cast<Rectangle*>(m_pShape)->width());
    pSpinBoxSide2->setValue(dynamic_cast<Rectangle*>(m_pShape)->height());
}

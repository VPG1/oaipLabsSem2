#include "staradjustmentwidget.h"
#include "npointedstar.h"
#include "fivepointedstar.h"
#include "sixpointedstar.h"
#include "eightpointedstar.h"

StarAdjustmentWidget::StarAdjustmentWidget(Shape *pShape, QWidget *parent)
    : AbstractAdjustmentWidget(pShape, parent)
{
    QGridLayout *pMainLayout = new QGridLayout;

    NPointedStar *pStar = dynamic_cast<NPointedStar *>(pShape);

    pSpinBoxInnerRadius = new QSpinBox;
    pSpinBoxInnerRadius->setRange(0, 1000);
    pSpinBoxInnerRadius->setValue(pStar->innerRadius());

    pSpinBoxOuterRadius = new QSpinBox;
    pSpinBoxOuterRadius->setRange(0, 1000);
    pSpinBoxOuterRadius->setValue(pStar->outerRadius());

    pMainLayout->addWidget(pSpinBoxInnerRadius, 0, 1);
    pMainLayout->addWidget(new QLabel("inner radius:"), 0, 0);

    pMainLayout->addWidget(pSpinBoxOuterRadius, 1, 1);
    pMainLayout->addWidget(new QLabel("outer radius:"), 1, 0);

    setLayout(pMainLayout);

    connect(pSpinBoxInnerRadius, SIGNAL(valueChanged(int)),
            SLOT(updateInnerRadius(int)));
    connect(pSpinBoxOuterRadius, SIGNAL(valueChanged(int)),
           SLOT(updateOuterRadius(int)));
}

void StarAdjustmentWidget::updateInnerRadius(int newInnerRadius)
{
    dynamic_cast<NPointedStar *>(m_pShape)->setInnerRadius(newInnerRadius);
    repaintItem();

    if(dynamic_cast<FivePointedStar *>(m_pShape)){
        emit parametersIsChanged(Shape::FIVE_POINTED_STAR);
    }
    else if(dynamic_cast<SixPointedStar *>(m_pShape)){
        emit parametersIsChanged(Shape::SIX_POINTED_STAR);
    }
    else if(dynamic_cast<EightPointedStar *>(m_pShape)){
        emit parametersIsChanged(Shape::EIGHT_POINTED_STAR);
    }
}

void StarAdjustmentWidget::updateOuterRadius(int newOuterRadius)
{
    dynamic_cast<NPointedStar *>(m_pShape)->setOuterRadius(newOuterRadius);
    repaintItem();

    if(dynamic_cast<FivePointedStar *>(m_pShape)){
        emit parametersIsChanged(Shape::FIVE_POINTED_STAR);
    }
    else if(dynamic_cast<SixPointedStar *>(m_pShape)){
        emit parametersIsChanged(Shape::SIX_POINTED_STAR);
    }
    else if(dynamic_cast<EightPointedStar *>(m_pShape)){
        emit parametersIsChanged(Shape::EIGHT_POINTED_STAR);
    }
}

void StarAdjustmentWidget::updateWidget()
{

    pSpinBoxInnerRadius
            ->setValue(dynamic_cast<NPointedStar*>(m_pShape)->innerRadius());
    pSpinBoxOuterRadius
            ->setValue(dynamic_cast<NPointedStar*>(m_pShape)->outerRadius());
}


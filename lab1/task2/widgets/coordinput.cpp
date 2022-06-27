#include "coordinput.h"
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>

CoordInput::CoordInput(Shape::VertexName numberOfCoords, QWidget *parent)
    : QWidget(parent), m_vertex(numberOfCoords)
{
    pSpinBoxX = new QSpinBox;
    pSpinBoxX->setRange(-1000, 1000);
    pSpinBoxY = new QSpinBox;
    pSpinBoxY->setRange(-1000, 1000);

    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addWidget(new QLabel(
                               QString(static_cast<char>('A' + numberOfCoords))
                               + ": x"));
    pMainLayout->addWidget(pSpinBoxX);

    pMainLayout->addWidget(new QLabel("y"));
    pMainLayout->addWidget(pSpinBoxY);

    setLayout(pMainLayout);

    connect(pSpinBoxX, SIGNAL(valueChanged(int)), SLOT(intermediateXSlot(int)));
    connect(pSpinBoxY, SIGNAL(valueChanged(int)), SLOT(intermediateYSlot(int)));

}

void CoordInput::setCoordValues(int valueX, int valueY)
{
    pSpinBoxX->setValue(valueX);
    pSpinBoxY->setValue(valueY);
}

void CoordInput::intermediateXSlot(int valueX)
{
    emit valueXChanged(valueX, m_vertex);
}

void CoordInput::intermediateYSlot(int valueY)
{
    emit valueYChanged(valueY, m_vertex);

}


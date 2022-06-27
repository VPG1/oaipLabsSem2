#include "hexagonadjustmentwidget.h"
#include "coordinput.h"
#include "hexagon.h"

HexagonAdjustmentWidget::HexagonAdjustmentWidget(Shape *pShape, QWidget *parent)
    : AbstractAdjustmentWidget(pShape, parent)
{
    QGridLayout *pMainLayout = new QGridLayout;

    pCoordInputArray = new CoordInput*[NUMBER_OF_HEXAGON_VERTEX];
    for(int i = 0; i < NUMBER_OF_HEXAGON_VERTEX; ++i){
        pCoordInputArray[i] = new CoordInput(static_cast<Shape::VertexName>(i));
        QPolygonF hexagonPolygon = dynamic_cast<Hexagon *>(pShape)->polygon();
        pCoordInputArray[i]->
                setCoordValues(hexagonPolygon[i].x(), hexagonPolygon[i].y());
        pMainLayout->addWidget(pCoordInputArray[i]);
    }

    setLayout(pMainLayout);

    for(int i = 0; i < NUMBER_OF_HEXAGON_VERTEX; ++i){
        connect(pCoordInputArray[i], SIGNAL(valueXChanged(int, Shape::VertexName)),
                SLOT(updateXCoord(int, Shape::VertexName)));
        connect(pCoordInputArray[i], SIGNAL(valueYChanged(int, Shape::VertexName)),
                SLOT(updateYCoord(int, Shape::VertexName)));
    }
}

void HexagonAdjustmentWidget::updateXCoord(int valueX, Shape::VertexName vertex)
{
    Hexagon *pHexagon= dynamic_cast<Hexagon *>(m_pShape);
    QPolygonF polygon = pHexagon->polygon();
    polygon[vertex].rx() = valueX;
    pHexagon->setPolygon(polygon);
    repaintItem();

    emit parametersIsChanged(Shape::HEXAGON);
}

void HexagonAdjustmentWidget::updateYCoord(int valueY, Shape::VertexName vertex)
{
    Hexagon *pHexagon= dynamic_cast<Hexagon *>(m_pShape);
    QPolygonF polygon = pHexagon->polygon();
    polygon[vertex].ry() = valueY;
    pHexagon->setPolygon(polygon);
    repaintItem();

    emit parametersIsChanged(Shape::HEXAGON);
}

void HexagonAdjustmentWidget::updateWidget()
{
    for(int i = 0; i < NUMBER_OF_HEXAGON_VERTEX; ++i){
        QPolygonF trianglePolygon = dynamic_cast<Hexagon *>(m_pShape)->polygon();
        pCoordInputArray[i]
                ->setCoordValues(trianglePolygon[i].x(), trianglePolygon[i].y());
    }
}


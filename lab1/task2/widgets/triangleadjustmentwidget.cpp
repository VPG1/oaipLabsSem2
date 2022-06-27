#include "triangleadjustmentwidget.h"
#include "coordinput.h"
#include "triangle.h"

TriangleAdjustmentWidget::TriangleAdjustmentWidget(Shape *pShape, QWidget *parent)
    : AbstractAdjustmentWidget(pShape, parent)
{
    QGridLayout *pMainLayout = new QGridLayout;

    pCoordInputArray = new CoordInput*[NUMBER_OF_TRIANGLE_VERTEX];
    for(int i = 0; i < NUMBER_OF_TRIANGLE_VERTEX; ++i){
        pCoordInputArray[i] = new CoordInput(static_cast<Shape::VertexName>(i));
        QPolygonF trianglePolygon = dynamic_cast<Triangle *>(pShape)->polygon();
        pCoordInputArray[i]->
                setCoordValues(trianglePolygon[i].x(), trianglePolygon[i].y());
        pMainLayout->addWidget(pCoordInputArray[i], i, 0);
    }

    setLayout(pMainLayout);

    for(int i = 0; i < NUMBER_OF_TRIANGLE_VERTEX; ++i){
        connect(pCoordInputArray[i], SIGNAL(valueXChanged(int, Shape::VertexName)),
                SLOT(updateXCoord(int, Shape::VertexName)));
        connect(pCoordInputArray[i], SIGNAL(valueYChanged(int, Shape::VertexName)),
                SLOT(updateYCoord(int, Shape::VertexName)));
    }
}

void TriangleAdjustmentWidget::updateXCoord(int valueX, Shape::VertexName vertex)
{
    Triangle *pTriangle = dynamic_cast<Triangle *>(m_pShape);
    QPolygonF polygon = pTriangle->polygon();
    polygon[vertex].rx() = valueX;
    pTriangle->setPolygon(polygon);

    repaintItem();

    emit parametersIsChanged(Shape::TRIANGLE);
}

void TriangleAdjustmentWidget::updateYCoord(int valueY, Shape::VertexName vertex)
{
    Triangle *pTriangle = dynamic_cast<Triangle *>(m_pShape);
    QPolygonF polygon = pTriangle->polygon();
    polygon[vertex].ry() = valueY;
    pTriangle->setPolygon(polygon);

    repaintItem();

    emit parametersIsChanged(Shape::TRIANGLE);
}

void TriangleAdjustmentWidget::updateWidget()
{
    for(int i = 0; i < NUMBER_OF_TRIANGLE_VERTEX; ++i){
        QPolygonF trianglePolygon = dynamic_cast<Triangle *>(m_pShape)->polygon();
        pCoordInputArray[i]
                ->setCoordValues(trianglePolygon[i].x(), trianglePolygon[i].y());
    }
}


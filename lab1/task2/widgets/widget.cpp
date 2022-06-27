#include "widget.h"
#include "shape.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include "triangleadjustmentwidget.h"
#include "rectangleadjustmentwidget.h"
#include "rhombusadjustmentwidget.h"
#include "squareadjustmentwidget.h"
#include "staradjustmentwidget.h"
#include "hexagonadjustmentwidget.h"
#include "circleadjustmentwidet.h"
#include <iostream>
#include <QStyleOptionGraphicsItem>

#include <QGraphicsScene>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    pScene = new GraphicsScene(this);
    pView = new QGraphicsView(pScene);
    pView->setRenderHint(QPainter::Antialiasing);


    QPoint zeroPoint = QPoint(0, 0);

    // инициализируем массив с объектами сцены
    pShapeArray = new Shape*[Shape::NUMBER_OF_FIGURE];
    pShapeArray[Shape::TRIANGLE] = new Triangle(zeroPoint, 70);

    pShapeArray[Shape::RECTANGLE] = new Rectangle(zeroPoint, 100, 50);

    pShapeArray[Shape::RHOMBUS] = new Rhombus(zeroPoint, 50, 100);

    pShapeArray[Shape::SQUARE] = new Square(zeroPoint, 70);

    pShapeArray[Shape::FIVE_POINTED_STAR] = new FivePointedStar(zeroPoint, 50, 100);

    pShapeArray[Shape::SIX_POINTED_STAR] = new SixPointedStar(zeroPoint, 50, 100);

    pShapeArray[Shape::EIGHT_POINTED_STAR] = new EightPointedStar(zeroPoint, 50, 100);

    pShapeArray[Shape::HEXAGON]  = new Hexagon(zeroPoint, 70);

    pShapeArray[Shape::CIRCLE] = new Circle(zeroPoint, 70);


    // добовляем в сцену
    for(int i = 0; i < Shape::NUMBER_OF_FIGURE; ++i){
        pScene->addItem(pShapeArray[i]);
    }

    // делаем все фигуры кроме треугольника по умолчанию невидимыми
    for(int i = 1; i < Shape::NUMBER_OF_FIGURE; ++i){
        pShapeArray[i]->hide();
    }


    pComboBoxOfFigures = new QComboBox(nullptr);
    pComboBoxOfFigures->addItems(QStringList() << "triangle" << "rectangle" << "rhombus"
                                              << "square" << "five pointed star" << "six pointed star"
                                              << "eight pointed star" << "hexagon" << "circle");

    pLabelArea = new QLabel;
    pLabelPerimeter = new QLabel;
    pLabelCenterOfGravity = new QLabel;
    setInformation(Shape::TRIANGLE);

    pStackedWidget = new QStackedWidget;

    pAdjustmentWidgetArray = new AbstractAdjustmentWidget*[Shape::NUMBER_OF_FIGURE];



    pAdjustmentWidgetArray[Shape::TRIANGLE]
            = new TriangleAdjustmentWidget(pShapeArray[Shape::TRIANGLE]);

    pAdjustmentWidgetArray[Shape::RECTANGLE]
            = new RectangleAdjustmentWidget(pShapeArray[Shape::RECTANGLE]);

    pAdjustmentWidgetArray[Shape::RHOMBUS]
            = new RhombusAdjustmentWidget(pShapeArray[Shape::RHOMBUS]);

    pAdjustmentWidgetArray[Shape::SQUARE]
            = new SquareAdjustmentWidget(pShapeArray[Shape::SQUARE]);

    pAdjustmentWidgetArray[Shape::FIVE_POINTED_STAR]
            = new StarAdjustmentWidget(pShapeArray[Shape::FIVE_POINTED_STAR]);

    pAdjustmentWidgetArray[Shape::SIX_POINTED_STAR]
            = new StarAdjustmentWidget(pShapeArray[Shape::SIX_POINTED_STAR]);

    pAdjustmentWidgetArray[Shape::EIGHT_POINTED_STAR]
            = new StarAdjustmentWidget(pShapeArray[Shape::EIGHT_POINTED_STAR]);

    pAdjustmentWidgetArray[Shape::HEXAGON]
            = new HexagonAdjustmentWidget(pShapeArray[Shape::HEXAGON]);

    pAdjustmentWidgetArray[Shape::CIRCLE]
            = new CircleAdjustmentWidet(pShapeArray[Shape::CIRCLE]);


    for(int i = 0; i < Shape::NUMBER_OF_FIGURE; ++i){
        pStackedWidget->addWidget(pAdjustmentWidgetArray[i]);
    }



    pSpinBoxdx = new QSpinBox;
    pSpinBoxdx->setRange(-1000, 1000);
    pSpinBoxdx->setPrefix("dx = ");
    pSpinBoxdx->setValue(0);
    pSpinBoxdy = new QSpinBox;
    pSpinBoxdy->setRange(-1000, 1000);
    pSpinBoxdy->setPrefix("dy = ");
    pSpinBoxdy->setValue(0);
    pPushButtonMove = new QPushButton("move");

    pSpinBoxAngle = new QSpinBox;
    pSpinBoxAngle->setRange(0, 360);
    pSpinBoxAngle->setPrefix("angle = ");
    pPushButtonRotate = new QPushButton("rotate");

    pDoubleSpinBoxFactor = new QDoubleSpinBox;
    pDoubleSpinBoxFactor->setRange(0, 100);
    pDoubleSpinBoxFactor->setValue(1);
    pPushButtonScale = new QPushButton("scale");


    // Layout setup
//    QGridLayout *pMainLayout = new QGridLayout;
//    pMainLayout->addWidget(pView, 0, 0, 5, 4);
//    pMainLayout->addWidget(pComboBoxOfFigures, 0, 4, Qt::AlignTop);
//    pMainLayout->addWidget(pLabelArea, 1, 4, Qt::AlignTop);
//    pMainLayout->addWidget(pLabelPerimeter, 2, 4, Qt::AlignTop);
//    pMainLayout->addWidget(pLabelCenterOfGravity, 3, 4, Qt::AlignTop);
//    pMainLayout->addWidget(pStackedWidget, 4, 4);

//    pMainLayout->addWidget(pPushButtonMove, 5, 0);
//    pMainLayout->addWidget(pSpinBoxdx, 6, 0);
//    pMainLayout->addWidget(pSpinBoxdy, 7, 0);

//    pMainLayout->addWidget(pPushButtonRotate, 5, 1);
//    pMainLayout->addWidget(pSpinBoxAngle, 6, 1);

//    pMainLayout->addWidget(pPushButtonScale, 5, 2);
//    pMainLayout->addWidget(pDoubleSpinBoxFactor, 6, 2);

    QVBoxLayout *pLeftLayout = new QVBoxLayout;
    pLeftLayout->addWidget(pComboBoxOfFigures);
    pLeftLayout->addWidget(pLabelArea);
    pLeftLayout->addWidget(pLabelPerimeter);
    pLeftLayout->addWidget(pLabelCenterOfGravity);
    pLeftLayout->addWidget(pStackedWidget);

    QGridLayout *pRightLayout = new QGridLayout;
    pRightLayout->addWidget(pView ,0, 0, 1, 3);

    pRightLayout->addWidget(pPushButtonMove, 1, 0);
    pRightLayout->addWidget(pSpinBoxdx, 2, 0);
    pRightLayout->addWidget(pSpinBoxdy, 3, 0);

    pRightLayout->addWidget(pPushButtonRotate, 1, 1);
    pRightLayout->addWidget(pSpinBoxAngle, 2, 1);

    pRightLayout->addWidget(pPushButtonScale, 1, 2);
    pRightLayout->addWidget(pDoubleSpinBoxFactor, 2, 2);

    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addLayout(pLeftLayout);
    pMainLayout->addLayout(pRightLayout, 1);

    setLayout(pMainLayout);

    connect(pComboBoxOfFigures, SIGNAL(currentIndexChanged(int)),
            SLOT(changeFigure(int)));
    connect(pComboBoxOfFigures, SIGNAL(currentIndexChanged(int)),
            pStackedWidget, SLOT(setCurrentIndex(int)));

    for(int i = 0; i < Shape::NUMBER_OF_FIGURE; ++i){
        connect(pAdjustmentWidgetArray[i], SIGNAL(parametersIsChanged(Shape::FigureType)),
                SLOT(setInformation(Shape::FigureType)));
    }

    connect(pPushButtonMove, SIGNAL(clicked()), SLOT(startMoving()));
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), SLOT(moving()));

    connect(pPushButtonRotate, SIGNAL(clicked()), SLOT(startRotating()));
    rotateTimer = new QTimer(this);
    connect(rotateTimer, SIGNAL(timeout()), SLOT(rotating()));

    connect(pPushButtonScale, SIGNAL(clicked()), SLOT(startScaling()));
    scaleTimer = new QTimer(this);
    connect(scaleTimer, SIGNAL(timeout()), SLOT(scaling()));


    pTimer = new QTimer;
    connect(pTimer, SIGNAL(timeout()), SLOT(slotTimer()));
    pTimer->start(1);
}

Widget::~Widget()
{
    // удаляем pShapeArray и pAdjustmentWidgetArray
    // так как  эти указатели не является ничьими потомками
    delete[] pShapeArray;
    delete[] pAdjustmentWidgetArray;
}

void Widget::makeInaccessible()
{
    pComboBoxOfFigures->setEnabled(false);

    pStackedWidget->setEnabled(false);

    pSpinBoxdx->setEnabled(false);
    pSpinBoxdy->setEnabled(false);
    pPushButtonMove->setEnabled(false);

    pSpinBoxAngle->setEnabled(false);
    pPushButtonRotate->setEnabled(false);

    pDoubleSpinBoxFactor->setEnabled(false);
    pPushButtonScale->setEnabled(false);
}

void Widget::makeAccessible()
{
    pComboBoxOfFigures->setEnabled(true);

    pStackedWidget->setEnabled(true);

    pSpinBoxdx->setEnabled(true);
    pSpinBoxdy->setEnabled(true);
    pPushButtonMove->setEnabled(true);

    pSpinBoxAngle->setEnabled(true);
    pPushButtonRotate->setEnabled(true);

    pDoubleSpinBoxFactor->setEnabled(true);
    pPushButtonScale->setEnabled(true);
}

void Widget::changeFigure(int newFigureIndex)
{
    // прячем предыдущую Фигуру
    pShapeArray[m_currentFigure]->hide();

    // показываем новую
    pShapeArray[newFigureIndex]->show();

    // обновляем информацию
    setInformation(static_cast<Shape::FigureType>(newFigureIndex));

    // обновляем индек текущей фигуры
    m_currentFigure = static_cast<Shape::FigureType>(newFigureIndex);
}


void Widget::setInformation(Shape::FigureType figure)
{
    pLabelArea->setText("area: " + QString::number(pShapeArray[figure]->area()));
    pLabelPerimeter->setText("perimeter: " + QString::number(pShapeArray[figure]->perimeter()));
    QPointF center = pShapeArray[figure]->centerOfGravity();
    pLabelCenterOfGravity->setText("center of gravity: (" + QString::number(center.x())
                                       + ", " +
                                   QString::number(center.y()) + ')');
}

void Widget::startMoving()
{
    if(pSpinBoxdx->value() == 0 && pSpinBoxdy->value() == 0){
        return;
    }

    if(abs(pSpinBoxdx->value()) >= abs(pSpinBoxdy->value())){
        deltaX = abs(pSpinBoxdx->value()) / pSpinBoxdx->value();
        deltaY = (pSpinBoxdy->value() * 1.0l
                 / abs(pSpinBoxdx->value()));

        numberOfSteps = abs(pSpinBoxdx->value());

    }else{
        deltaY = abs(pSpinBoxdy->value())/ pSpinBoxdy->value();
        deltaX = (pSpinBoxdx->value() * 1.0l
                 / abs(pSpinBoxdy->value()));

        numberOfSteps = abs(pSpinBoxdy->value());
    }

    makeInaccessible();
    moveTimer->start(20);
}

void Widget::moving()
{
    if(numberOfSteps <= 0){
        moveTimer->stop();
        makeAccessible();

        setInformation(m_currentFigure);
        pAdjustmentWidgetArray[m_currentFigure]->updateWidget();
        return;
    }
    pShapeArray[m_currentFigure]->moving(deltaX, deltaY);

    pShapeArray[m_currentFigure]->update(-100, -100, pView->width(), pView->height());

    --numberOfSteps;
}

void Widget::startRotating()
{
    m_currentMarkerPos = pScene->currentMarkerPos();

    rotatingAngle = pSpinBoxAngle->value();
    makeInaccessible();
    rotateTimer->start(20);
}

void Widget::rotating()
{
    if(rotatingAngle <= 0){
        rotateTimer->stop();
        makeAccessible();
        setInformation(m_currentFigure);
        pAdjustmentWidgetArray[m_currentFigure]->updateWidget();
        return;
    }

    static const long double angleInRad = M_PI / 180.0;
    static const long double angleCos = cos(angleInRad);
    static const long double angleSin = sin(angleInRad);

    long double x = m_currentMarkerPos.x();
    long double y = m_currentMarkerPos.y();

    pShapeArray[m_currentFigure]->setMatrix(Matrix(angleCos, -angleSin, -x * angleCos + y * angleSin + x,
                                                   angleSin, angleCos, -x * angleSin - y *angleCos + y,
                                                   0, 0, 1));
    pShapeArray[m_currentFigure]->update(-100, -100, pView->width(), pView->height());

    --rotatingAngle;
}

void Widget::startScaling()
{
    m_currentMarkerPos = pScene->currentMarkerPos();

    double value;
    if(pDoubleSpinBoxFactor->value() > 1){
        value = pDoubleSpinBoxFactor->value();
    }else{
        value = 1 / pDoubleSpinBoxFactor->value();
    }

    numberOfFrames = fabs(value - 1) * 100;
    frameScalingFactor = pow(pDoubleSpinBoxFactor->value(), 1.0 / numberOfFrames);

    makeInaccessible();
    scaleTimer->start(20);
}

void Widget::scaling()
{
    if(numberOfFrames <= 0){
        scaleTimer->stop();
        makeAccessible();
        setInformation(m_currentFigure);
        pAdjustmentWidgetArray[m_currentFigure]->updateWidget();
        return;
    }


    pShapeArray[m_currentFigure]->scaling(frameScalingFactor, m_currentMarkerPos);

    pShapeArray[m_currentFigure]->update(-100, -100, pView->width(), pView->height());

    --numberOfFrames;
}

void Widget::slotTimer()
{
    pTimer->stop();
    pScene->setSceneRect(-100, -100, pView->width() - 10, pView->height() - 10);
}

void Widget::resizeEvent(QResizeEvent *pEvent)
{
    pTimer->start(1);
    QWidget::resizeEvent(pEvent);
}





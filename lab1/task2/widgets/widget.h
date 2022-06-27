#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include "triangle.h"
#include "rectangle.h"
#include "rhombus.h"
#include "square.h"
#include "fivepointedstar.h"
#include "sixpointedstar.h"
#include "eightpointedstar.h"
#include "hexagon.h"
#include "circle.h"
#include "shape.h"
#include "shape.h"
#include <QStackedWidget>
#include "abstractadjustmentwidget.h"
#include "graphicsscene.h"
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QTransform>
#include <QTimer>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QGraphicsView *pView;
    GraphicsScene *pScene;

    QTimer *pTimer;

    Shape **pShapeArray;
    AbstractAdjustmentWidget **pAdjustmentWidgetArray;

    QComboBox *pComboBoxOfFigures;

    QLabel *pLabelArea;
    QLabel *pLabelPerimeter;
    QLabel *pLabelCenterOfGravity;
    QStackedWidget *pStackedWidget;

    QSpinBox *pSpinBoxdx;
    QSpinBox *pSpinBoxdy;
    QPushButton *pPushButtonMove;

    QSpinBox *pSpinBoxAngle;
    QPushButton *pPushButtonRotate;

    QDoubleSpinBox *pDoubleSpinBoxFactor;
    QPushButton *pPushButtonScale;

    Shape::FigureType m_currentFigure = Shape::TRIANGLE;

    QTimer *moveTimer;
    QTimer *rotateTimer;
    QTimer *scaleTimer;

    long double deltaX = 0;
    long double deltaY = 0;
    int numberOfSteps = 0;

    int rotatingAngle = 0;

    int numberOfFrames;
    long double frameScalingFactor = 1;

    QPointF m_currentMarkerPos;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void makeInaccessible();
    void makeAccessible();


public slots:
    void changeFigure(int newFigureIndex);
    void setInformation(Shape::FigureType figure);

    void startMoving();
    void moving();

    void startRotating();
    void rotating();

    void startScaling();
    void scaling();

    void slotTimer();

protected:
    void resizeEvent(QResizeEvent *pEvent) override;
};
#endif // WIDGET_H

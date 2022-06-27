#include "graphicsscene.h"



QPointF GraphicsScene::currentMarkerPos() const
{
    return m_currentMarkerPos;
}

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent), m_currentMarkerPos(0,0)
{
    m_pCurrentMarker = addEllipse(QRectF(m_currentMarkerPos + QPointF(5, 5), QSize(10, 10)),
                                  QPen(), QBrush(Qt::red));
}

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent), m_currentMarkerPos(0, 0)
{
    m_pCurrentMarker = addEllipse(QRectF(m_currentMarkerPos + QPointF(5, 5), QSize(10, 10)),
                                  QPen(), QBrush(Qt::red));
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // удаляем предыдущий маркер
    removeItem(m_pCurrentMarker);

    // устанавливаем новый
    m_currentMarkerPos = event->scenePos();
    m_pCurrentMarker = addEllipse(QRectF(m_currentMarkerPos - QPointF(5, 5), QSize(10, 10)),
                                  QPen(), QBrush(Qt::red));

    QGraphicsScene::mousePressEvent(event);
}

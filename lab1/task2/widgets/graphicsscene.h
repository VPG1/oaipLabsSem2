#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class GraphicsScene : public QGraphicsScene
{
private:
    QPointF m_currentMarkerPos;
    QGraphicsItem *m_pCurrentMarker;
public:
    GraphicsScene(QObject *parent = nullptr);
    GraphicsScene(int x, int y, int width, int height, QObject *parent = nullptr);

    QPointF currentMarkerPos() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GRAPHICSSCENE_H

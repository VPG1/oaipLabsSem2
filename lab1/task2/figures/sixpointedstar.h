#ifndef SIXPOINTEDSTAR_H
#define SIXPOINTEDSTAR_H

#include "npointedstar.h"

class SixPointedStar : public NPointedStar
{
public:
    SixPointedStar(const QPointF &center,
                   int innerRadius, int outerRadius,
                   QGraphicsItem *parent = nullptr);
};

#endif // SIXPOINTEDSTAR_H

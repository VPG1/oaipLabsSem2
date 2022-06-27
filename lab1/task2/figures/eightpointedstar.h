#ifndef EIGHTPOINTEDSTAR_H
#define EIGHTPOINTEDSTAR_H

#include "npointedstar.h"

class EightPointedStar : public NPointedStar
{
public:
    EightPointedStar(const QPointF &center,
                     int innerRadius, int outerRadius,
                     QGraphicsItem *parent = nullptr);
};

#endif // EIGHTPOINTEDSTAR_H

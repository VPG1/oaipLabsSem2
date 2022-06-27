#ifndef FIVEPOINTEDSTAR_H
#define FIVEPOINTEDSTAR_H

#include "npointedstar.h"

class FivePointedStar : public NPointedStar
{
public:
    FivePointedStar(const QPointF &center, int innerRadius,
                    int outerRadius, QGraphicsItem *parent = nullptr);
};

#endif // FIVEPOINTEDSTAR_H

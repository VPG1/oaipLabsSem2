#include "eightpointedstar.h"

EightPointedStar::EightPointedStar(const QPointF &center, int innerRadius,
                                   int outerRadius, QGraphicsItem *parent)
    : NPointedStar(center, innerRadius, outerRadius, 8, parent)
{

}

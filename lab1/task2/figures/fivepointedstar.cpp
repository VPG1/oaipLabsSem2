#include "fivepointedstar.h"

FivePointedStar::FivePointedStar(const QPointF &center, int innerRadius,
                                 int outerRadius, QGraphicsItem *parent)
    : NPointedStar(center, innerRadius, outerRadius, 5, parent)
{

}

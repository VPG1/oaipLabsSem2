#include "sixpointedstar.h"


SixPointedStar::SixPointedStar(const QPointF &center, int innerRadius,
                               int outerRadius, QGraphicsItem *parent)
    : NPointedStar(center, innerRadius, outerRadius, 6, parent)
{

}

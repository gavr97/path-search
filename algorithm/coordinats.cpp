#include "../global/globalTypes.h"
#include "../algorithm/astar.h"

unsigned AStar::key(unsigned ux, unsigned uy) const
{
    return ux * (cntRealCols + 2) + uy;
}

unsigned AStar::key(const Node &node) const
{
    return key(node.getX(), node.getY());
}

unsigned AStar::coordinateFirst(unsigned key)
{
    return key / (cntRealCols + 2);
}

unsigned AStar::coordinateSecond(unsigned key)
{
    return key % (cntRealCols + 2);
}

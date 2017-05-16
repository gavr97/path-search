#ifndef ASEARCH_THETA_H
#define ASEARCH_THETA_H

#include "../algorithm/astar.h"

class Theta : public AStar {
protected:
    using AStar::AStar;
    void setLevelPath(Output &output);
    void computeCost(const Node *const pNodeParent, Node &nodeSon, const Map &map) const;
};

#endif //ASEARCH_THETA_H

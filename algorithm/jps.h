#ifndef ASEARCH_JPS_H
#define ASEARCH_JPS_H

#include "../algorithm/astar.h"

class Jps : public AStar{
protected:
    void setLevelPath(Output &output);
    std::vector<Node> getSuccessors(const Node &node, const Map &map) const;
    bool isNatural(unsigned px, unsigned py, unsigned ux, unsigned uy, unsigned vx, unsigned vy, const Map &map) const;
    bool isForced(unsigned px, unsigned py, unsigned ux, unsigned uy, unsigned vx, unsigned vy, const Map &map) const;
    std::pair<bool, Node> jump(unsigned ux, unsigned uy, int dx, int dy, const Map &map) const;
    void getCoordinats(unsigned &px, unsigned &py, unsigned &ux, unsigned &uy, unsigned &vx, unsigned &vy,
                            int &dx1, int &dy1, int &dx2, int &dy2) const;
};

#endif //ASEARCH_JPS_H

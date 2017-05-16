#include "heuristics.h"
#include <ctime>
#include "../algorithm/jps.h"

void Jps::setLevelPath(Output &output)
{
    output.isLowLevel = false;
}

std::vector<Node> Jps::getSuccessors(const Node &node, const Map &map) const
{
    // p -> u -> v
    std::vector<Node> successors;
    unsigned ux = node.getX();
    unsigned uy = node.getY();
    unsigned px, py;
    if (node != nodeStart) {
        px = node.getParent()->getX();
        py = node.getParent()->getY();
    }
    for (unsigned indDirection = 0; indDirection != dyVec.size(); ++indDirection) {
        unsigned vx = ux + dxVec[indDirection];
        unsigned vy = uy + dyVec[indDirection];
        if (!map.isObstacle(vx, vy) && map.isAllowedFromTo(ux, uy, vx, vy))
        {
            if (node != nodeStart && !isNatural(px, py, ux, uy, vx, vy, map) &&
                !isForced(px, py, ux, uy, vx, vy, map))
            {
                // prune;
                continue;
            }

            std::pair<bool, Node> jumpRes = jump(ux, uy, dxVec[indDirection], dyVec[indDirection], map);
            if (jumpRes.first && close.find(jumpRes.second) == close.end())
                successors.push_back(jumpRes.second);
        }
    }
    return successors;
}

bool Jps::isNatural(unsigned px, unsigned py, unsigned ux, unsigned uy, unsigned vx, unsigned vy, const Map &map) const
{
    // p ->(dx1, dy1)-> u ->(dx2, dy2)-> v
    if (map.isObstacle(vx, vy)) {
        return false;
    }

    int dx1, dx2, dy1, dy2;
    getCoordinats(px, py, ux, uy, vx, vy, dx1, dy1, dx2, dy2);

    if (dx1 * dy1 != 0) {  // from p to u diagonal move
        return (px != vx && py != vy);
    } else { // from p to u straight
        return (dx1 == dx2 && dy1 == dy2);
    }
}

bool Jps::isForced(unsigned px, unsigned py, unsigned ux, unsigned uy, unsigned vx, unsigned vy, const Map &map) const
{
    // p ->(dx1, dy1)-> u ->(dx2, dy2)-> v
    if (map.isObstacle(vx, vy)) {
        return false;
    }

    int dx1, dx2, dy1, dy2;
    getCoordinats(px, py, ux, uy, vx, vy, dx1, dy1, dx2, dy2);

    if (dx1 * dy1 != 0) {  // from p to u diagonal move
        if ((px + 2 * dx1 == vx) && (py == vy) && map.isObstacle(px + dx1, py)) {
            return true;
        } else if ((py + 2 * dy1 == vy) && (px == vx) && map.isObstacle(px, py + dy1)) {
            return true;
        } else {
            return false;
        }
    } else { // from p to u straight
        if ((px + 2 * dx2 == vx) && (py + dy2 == vy) && map.isObstacle(px + dx2, py + dy2)) {
            return true;
        } else if ((py + 2 * dy2 == vy) && (px + dx2 == vx) && map.isObstacle(px + dx2, py + dy2)) {
            return true;
        } else {
            return false;
        }
    }
}

std::pair<bool, Node> Jps::jump(unsigned ux, unsigned uy, int dx, int dy, const Map &map) const
{
    unsigned vx = ux + dx;
    unsigned vy = uy + dy;
    if (map.isObstacle(vx, vy)) {
        return {false, Node{0, 0}};
    }
    if (nodeFinish == Node{vx, vy}) {
        return {true, Node{vx, vy}};
    }

    bool isThereForcedNeig = false;
    for (unsigned indDirection = 0; indDirection != dyVec.size(); ++indDirection) {
        unsigned zx = vx + dxVec[indDirection];
        unsigned zy = vy + dyVec[indDirection];
        if (isForced(ux, uy, vx, vy, zx, zy, map)) {
            isThereForcedNeig = true;
            break;
        }
    }
    if (isThereForcedNeig) {
        return {true, Node{vx, vy}};
    }

    if (dx * dy != 0) {  // diagonal move from u to v
        std::pair<bool, Node> jumpRes = jump(vx, vy, dx, 0, map);
        if (jumpRes.first) {
            return {true, Node{vx, vy}};
        }
        jumpRes = jump(vx, vy, 0, dy, map);
        if (jumpRes.first) {
            return {true, Node{vx, vy}};
        }
    }
    return jump(vx, vy, dx, dy, map);
}

void Jps::getCoordinats(unsigned &px, unsigned &py, unsigned &ux, unsigned &uy, unsigned &vx, unsigned &vy,
                          int &dx1, int &dy1, int &dx2, int &dy2) const
{
    // p ->(dx1, dy1)-> u ->(dx2, dy2)-> v
    dx1 = ux - px;
    dy1 = uy - py;
    // now normalize towards 1
    if (dx1 > 0)
        dx1 = 1;
    else if (dx1 < 0)
        dx1 = -1;
    if (dy1 > 0)
        dy1 = 1;
    else if (dy1 < 0)
        dy1 = -1;

    // respevtively
    dx2 = vx - ux;
    dy2 = vy - uy;
    if (dx2 > 0)
        dx2 = 1;
    else if (dx2 < 0)
        dx2 = -1;
    if (dy2 > 0)
        dy2 = 1;
    else if (dy2 < 0)
        dy2 = -1;

    // consider parent to just near in right direction
    px = ux - dx1;
    py = uy - dy1;
}
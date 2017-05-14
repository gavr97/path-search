#include <ctime>
#include "heuristics.h"
#include "../algorithm/astar.h"

TypeValue AStar::heuristic(const Node &node1, const Node &node2) const
{
    return heuristicHide(node1.getX(), node1.getY(), node2.getX(), node2.getY());
}

inline unsigned AStar::key(unsigned ux, unsigned uy) const
{
    return ux * (cntRealCols + 2) + uy;
}

inline unsigned AStar::key(const Node &node) const
{
    return key(node.getX(), node.getY());
}

inline unsigned AStar::coordinateFirst(unsigned key)
{
    return key / (cntRealCols + 2);
}

inline unsigned AStar::coordinateSecond(unsigned key)
{
    return key % (cntRealCols + 2);
}

int AStar::init(const Task &task)
{
    //_____define heuristic_____
    if (task.metricType == "manhattan")
        heuristicHide = &manhattan;
    else if (task.metricType == "euclid")
        heuristicHide = &euclid;
    else if (task.metricType == "chebyshev"){
        heuristicHide = &straight;
        if (task.allowDiag == 1) {
            std::cout << "error: straight is inadmissible heiristic when allowdiag = 1\n";
            return 1;
        }
    } else {
        std::cout << "warning: metrictype is incorrect. By default, euclid is assigned\n";
        heuristicHide = &euclid;
    }

    //______init start and finish_____
    nodeStart = Node{task.startX, task.startY};
    nodeFinish = Node{task.finishX, task.finishY};

    //_____init containers open and close____
    open.init(task.cntRealRows, task.cntRealCols);
    close.init(task.cntRealRows, task.cntRealCols);

    //_____define sizes of map (astar needs it)
    cntRealCols = task.cntRealCols;
    cntRealRows = task.cntRealRows;
    startX = task.startX;
    startY = task.startY;
    finishX = task.finishX;
    finishY = task.finishY;

    //_____define dx and dy weights______
    if (task.allowDiag == 1) {
        dxVec = {0, 0, 1, -1, 1, -1, -1, 1};
        dyVec = {1, -1, 0, 0, 1, -1, 1, -1 };
        weightVec = {task.lineCost, task.lineCost, task.lineCost, task.lineCost,
                     task.diagCost, task.diagCost, task.diagCost, task.diagCost};
    } else {
        dxVec = {0, 0, 1, -1};
        dyVec = {1, -1, 0, 0};
        weightVec = {task.lineCost, task.lineCost, task.lineCost, task.lineCost};
    }
    return 0;
}

int AStar::solve(const Map &map, Output &output)
{
    setLevelPath(output);
    unsigned int start_time = clock();
    unsigned int end_time, search_time;
    if (computeGValues(map, output)) {
        if (constructPath(output)) {
            end_time = clock();
            search_time = end_time - start_time;
            output.time = (double)search_time / CLOCKS_PER_SEC;
            if (!output.isLowLevel) {
                highToLow(output.path, output.weightMovements, output.otherPath, output.otherWeightMovements);
            }
            else {
                lowToHigh(output.path, output.weightMovements, output.otherPath, output.otherWeightMovements);
            }
            return 0;
        } else {
            end_time = clock();
            search_time = end_time - start_time;
            std::cout << "error: failure during constructing path\n";
            return 1;
        }
    } else {
        return 1;
    }
}

bool AStar::computeGValues(const Map &map, Output &output)
{
    // open, close are inside AStar astar
    // open is a set of (f-val, Node)
    // close is a set of (Node, g-val);
    // open: (f-val, node)

    Node nodeNow(startX, startY, (TypeValue)0, 0 + heuristic(nodeNow, nodeFinish));
    nodeNow.setParent(nullptr);
    if (!map.isObstacle(nodeNow)) {
        open.push(nodeNow);
    } else {
        std::cout << "warning: start is obstacle\n";
        return false;
    }

    ++output.numberOfNodesCreated;
    // output.nodesCreated.push_back(nodeNow);
    while (!open.empty()) {
        ++output.numberOfSteps;
        nodeNow = open.pop();
        const Node* pNodeNow = close.push(nodeNow);
        nodeNow = *pNodeNow;  // for correct adress of nodeNow in memory;
        if (nodeNow == nodeFinish) {
            return true;
        }

        for (Node &nodeSuccessor : getSuccessors(nodeNow, map)) {
            bool wasCreated;
            computeCost(pNodeNow, nodeSuccessor, map);  // make nodeSuccessor a pretendent(set gVal, ..., parent)
            open.update(nodeSuccessor, wasCreated); // wasCreated - reference passing arg
            if (!wasCreated) {
                ++output.numberOfNodesCreated;
                // output.nodesCreated.push_back(nodeNow);
            }
        }
    }
    return false;  // goal is not reached
}

bool AStar::constructPath(Output &output)
{
    Node nodeStart = close[key(startX, startY)];
    unsigned keyNow = key(finishX, finishY);
    Node nodeNow = close[keyNow];
    TypeValue gValNow = nodeNow.getGVal();
    output.numberOfMovements = 0;
    output.lengtnPath = 0;
    while (nodeNow != nodeStart) {
        Node nodeNext = *(nodeNow.getParent());
        TypeValue gValNext = nodeNext.getGVal();
        output.lengtnPath += gValNow - gValNext;
        output.weightMovements.push_back(gValNow - gValNext);
        ++output.numberOfMovements;
        output.path.push_back(nodeNow);

        nodeNow = nodeNext;
        gValNow = gValNext;
    }
    output.path.push_back(nodeNow);
    return true;
}

void AStar::computeCost(const Node *const pNodeParent, Node &nodeSon, const Map &map) const
{
    const Node nodeParent = *pNodeParent;
    const Node * pNodePretendent = pNodeParent;
    Node nodePretendent = *pNodePretendent;

    TypeValue  gVal = nodePretendent.getGVal() + heuristic(nodePretendent, nodeSon);
    nodeSon.setGVal(gVal);
    nodeSon.setFVal(gVal + heuristic(nodeSon, nodeFinish));
    nodeSon.setParent(pNodePretendent);
}

void AStar::setLevelPath(Output &output)
{
    output.isLowLevel = true;
}

void AStar::lowToHigh
        (
                const std::vector<Node> &path,
                const std::vector<TypeValue> &weightMovements,
                std::vector<Node> &otherPath,
                std::vector<TypeValue> &otherWeightMovements
        ) const
{
    otherPath.clear();
    unsigned ind = 0;
    while (ind < path.size()) {
        unsigned x1 = path[ind].getX();
        unsigned y1 = path[ind].getY();
        otherPath.push_back(Node{x1, y1});
        ++ind;
        if (ind == path.size()) {
            break;
        }
        int deltaX = path[ind].getX() - x1;
        int deltaY = path[ind].getY() - y1;
        int deltaNowX = deltaX;
        int deltaNowY = deltaY;
        unsigned xPrev = path[ind].getX();
        unsigned yPrev = path[ind].getY();
        while (ind < path.size() && deltaNowX == deltaX && deltaNowY == deltaY) {
            ++ind;
            if (ind == path.size()) {
                break;
            }
            deltaNowX = path[ind].getX() - xPrev;
            deltaNowY = path[ind].getY() - yPrev;
            xPrev = path[ind].getX();
            yPrev = path[ind].getY();
        }
        unsigned x2 = xPrev;
        unsigned y2 = yPrev;
        TypeValue weightSection = heuristic(Node{x1, y1}, Node{x2, y2});
        otherWeightMovements.push_back(weightSection);
        --ind;
    }
}

void AStar::highToLow
        (
                const std::vector<Node> &path,
                const std::vector<TypeValue> &weightMovements,
                std::vector<Node> &otherPath,
                std::vector<TypeValue> &otherWeightMovements
        ) const
{
    bool isFirst = true;
    for (unsigned ind_to = 1; ind_to != path.size(); ++ind_to) {
        unsigned ind_from = ind_to - 1;
        int x1 = path[ind_from].getX(); int y1 = path[ind_from].getY();
        int x2 = path[ind_to].getX(); int y2 = path[ind_to].getY();

        const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = x1 < x2 ? 1 : -1;
        const int signY = y1 < y2 ? 1 : -1;
        int error = deltaX - deltaY;

        while(x1 != x2 || y1 != y2)
        {
            //setPixel(x1, y1);
            otherPath.push_back(Node{static_cast<unsigned>(x1), static_cast<unsigned>(y1)});

            const int error2 = error * 2;
            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }
            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
            isFirst = false;
        }
        //setPixel(x2, y2);  it will be taken in next iteration;
    }
    // in this case next iteration has not happened
    //setPixel(x1, y1);
    otherPath.push_back(path.back());
}

std::vector<Node> AStar::getSuccessors(const Node &node, const Map &map) const
{
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
        if (!map.isObstacle(vx, vy)  && close.find(vx, vy) == close.end() &&
            map.isAllowedFromTo(ux, uy, vx, vy))
        {
            if (node != nodeStart && !isNatural(px, py, ux, uy, indDirection, map) &&
                !isForced(px, py, ux, uy, indDirection, map))
            {
                // prune;
                continue;
            }

            std::pair<bool, Node> jumpRes = jump(ux, uy, dxVec[indDirection], dyVec[indDirection], map);
            if (jumpRes.first)
                successors.push_back(jumpRes.second);
        }
    }
    return successors;
}

bool AStar::isNatural(unsigned px, unsigned py, unsigned ux, unsigned uy, unsigned indDirection, const Map &map) const
{
    unsigned vx = ux + dxVec[indDirection];
    unsigned vy = uy + dyVec[indDirection];
    if (map.isObstacle(vx, vy)) {
        return false;
    }

    // indDirection is from u to v;
    // determine indDirection from p to u;
    // p ->(dx1, dy1)-> u ->(dx2, dy2)-> v
    int dx1 = ux - px;
    int dy1 = uy - py;
    int dx2 = vx - ux;
    int dy2 = vy - uy;
    if (dx1 * dy1 != 0) {  // from p to u diagonal move
        return (px != vx && py != vy);
    } else { // from p to u straight
        return (dx1 == dx2 && dy1 == dy2);
    }
}

bool AStar::isForced(unsigned px, unsigned py, unsigned ux, unsigned uy, unsigned indDirection, const Map &map) const
{
    unsigned vx = ux + dxVec[indDirection];
    unsigned vy = uy + dyVec[indDirection];
    if (map.isObstacle(vx, vy)) {
        return false;
    }

    // indDirection is from u to v;
    // determine indDirection from p to u;
    // p ->(dx1, dy1)-> u ->(dx2, dy2)-> v
    int dx1 = ux - px;
    int dy1 = uy - py;
    int dx2 = vx - ux;
    int dy2 = vy - uy;
    if (dx1 * dy1 != 0) {  // from p to u diagonal move
        if ((px + 2 * dx1 == vx) && (py == vy) && map.isObstacle(px + dx1, py)) {
            return true;
        } else if ((py + 2 * dy1 == vy) && (px == vx) && map.isObstacle(px, py + dy1)) {
            return true;
        } else {
            return false;
        }
    } else { // from p to u straight
        if ((px + 2 * dx1 == vx) && (py + dy2 == vy) && map.isObstacle(px + dx2, py + dy2)) {
            return true;
        } else if ((py + 2 * dy1 == vy) && (px + dx2 == vx) && map.isObstacle(px + dx2, py + dy2)) {
            return true;
        } else {
            return false;
        }
    }
}

std::pair<bool, Node> AStar::jump(unsigned ux, unsigned uy, int dx, int dy, const Map &map) const
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
        if (isForced(ux, uy, vx, vy, indDirection, map)) {
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

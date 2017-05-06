#include <cmath>
#include <ctime>
#include "../algorithm/theta.h"

inline int my_Max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

inline TypeValue straight(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    TypeValue ret = my_Max(abs((int)ux - (int)vx), abs((int)uy - (int)vy));
    return ret;
}

inline TypeValue euclid(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    return sqrt(pow(((int)ux - (int)vx), 2) + pow(((int)uy - (int)vy), 2));
}

inline TypeValue manhattan(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    TypeValue ret = abs((int)ux - (int)vx) + abs((int)uy - (int)vy);
    return ret;
}

inline TypeValue zero(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    return 0;
}

TypeValue Theta::heuristic(const Node &node1, const Node &node2) const
{
    return heuristicHide(node1.getX(), node1.getY(), node2.getX(), node2.getY());
}

inline unsigned Theta::key(unsigned ux, unsigned uy) const
{
    return ux * (cntRealCols + 2) + uy;
}

inline unsigned Theta::key(const Node &node) const
{
    return key(node.getX(), node.getY());
}

inline unsigned Theta::coordinateFirst(unsigned key)
{
    return key / (cntRealCols + 2);
}

inline unsigned Theta::coordinateSecond(unsigned key)
{
    return key % (cntRealCols + 2);
}

int Theta::init(const Task &task)
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

int Theta::solve(const Map &map, Output &output)
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
            //else {
            //    lowTpHigh(output.path, output.weightMovements, output.otherPath, output.otherWeightMovements);
            //}
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

bool Theta::computeGValues(const Map &map, Output &output)
{
    // open, close are inside Theta astar
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
        unsigned ux = nodeNow.getX(), uy = nodeNow.getY();
        for (unsigned ind = 0; ind != dyVec.size(); ++ind) {
            unsigned vx = ux + dxVec[ind];
            unsigned vy = uy + dyVec[ind];
            bool wasCreated;
            Node nodeNeig{vx, vy};
            if (!map.isObstacle(vx, vy)  && close.find(nodeNeig) == close.end() &&
                map.isAllowedFromTo(ux, uy, vx, vy)) {
                computeCost(pNodeNow, nodeNeig, map);  // make nodeNeig a pretendent(set gVal, ..., parent)
                open.update(nodeNeig, wasCreated); // wasCreated - reference passing arg
                if (!wasCreated) {
                    ++output.numberOfNodesCreated;
                    // output.nodesCreated.push_back(nodeNow);
                }
            }
        }
    }
    return false;  // goal is not reached
}

bool Theta::constructPath(Output &output)
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

void Theta::computeCost(const Node *const pNodeParent, Node &nodeSon, const Map &map) const
{
    const Node nodeParent = *pNodeParent;
    const Node * const pNodeGrandParent = nodeParent.getParent();

    const Node * pNodePretendent;
    Node nodePretendent;
    if (pNodeGrandParent != nullptr && map.lineOfSight(*pNodeGrandParent, nodeSon)) {
        pNodePretendent = pNodeGrandParent;
        nodePretendent = *pNodePretendent;
    } else {
        pNodePretendent = pNodeParent;
        nodePretendent = *pNodePretendent;
    }

    TypeValue  gVal = nodePretendent.getGVal() + heuristic(nodePretendent, nodeSon);
    nodeSon.setGVal(gVal);
    nodeSon.setFVal(gVal + heuristic(nodeSon, nodeFinish));
    nodeSon.setParent(pNodePretendent);
}

void Theta::setLevelPath(Output &output)
{
    output.isLowLevel = false;
}

void Theta::lowToHigh
        (
        const std::vector<Node> &path,
        const std::vector<TypeValue> &weightMovements,
        std::vector<Node> &otherPath,
        std::vector<TypeValue> &otherWeightMovements
        ) const
{

}

void Theta::highToLow
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


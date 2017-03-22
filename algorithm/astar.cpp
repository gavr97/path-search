//
// Created by alexgavr on 07.01.17.
//

#include <cmath>
#include "../algorithm/astar.h"

// for debug
void AStar::printClose()
{
    for (unsigned indRow = 1; indRow != cntRealRows + 1; ++indRow) {
        for (unsigned indCol = 1; indCol != cntRealCols + 1; ++indCol) {
            Node node{indRow, indCol, key(indRow, indCol)};
            if (close.find(node) == close.end()) {
                printf("%*.2f", 6, -12);
            } else {
                printf("%*.2f", 6, (close.find(node)->second).getGVal());
            }
        }
        printf("\n");
    }
}

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

TypeValue AStar::heuristic(Node node1, Node node2)
{
    return heuristicHide(node1.getX(), node1.getY(), node2.getX(), node2.getY());
}

inline unsigned AStar::key(unsigned ux, unsigned uy)
{
    return ux * (cntRealCols + 2) + uy;
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

    //_____define sizes of map (astar needs it)
    cntRealCols = task.cntRealCols;
    cntRealRows = task.cntRealRows;
    startX = task.startX;
    startY = task.startY;
    finishX = task.finishX;
    finishY = task.finishY;

    allowDiag = task.allowDiag;
    allowSqueeze = task.allowSqueeze;
    cutCorners = task.cutCorners;

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
    if (computeGValues(map, output)) {
        if (constructPath(output)) {
            //std::cout << "path is succesfully found\n";
            return 0;
        } else {
            std::cout << "error: failure during constructing path\n";
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}

bool AStar::computeGValues(const Map &map, Output &output)
{
    // open, close are inside AStar astar
    // open is a set of (f-val, Node)
    // close is a set of (Node, g-val);
    // open: (f-val, node)
    unsigned keyNow = key(startX, startY);
    Node nodeFinish{finishX, finishY, key(finishX, finishY)};
    Node nodeNow(startX, startY, keyNow,  (TypeValue)0, 0 + heuristic(nodeNow, nodeFinish));
    open.push(nodeNow);
    ++output.numberOfNodesCreated;
    // output.nodesCreated.push_back(nodeNow);
    while (!open.empty()) {
        ++output.numberOfSteps;
        nodeNow = open.pop();
        close.push(nodeNow);
        if (nodeNow == nodeFinish) {
            return true;  // returned value;
        }
        
        unsigned ux = nodeNow.getX(), uy = nodeNow.getY();
        for (unsigned ind = 0; ind != dyVec.size(); ++ind) {
            unsigned vx = ux + dxVec[ind];
            unsigned vy = uy + dyVec[ind];
            unsigned keyNeig = key(vx, vy);
            Node nodeNeig{vx, vy, keyNeig};
            if (open.find(nodeNeig) != open.end()) {  // if is already created
                nodeNeig = open[nodeNeig];
            }
            if (!map.isObstacle(vx, vy)  && close.find(nodeNeig) == close.end() &&
                    map.isAllowed(ux, uy, vx, vy)) {
                if (open.find(nodeNeig) == open.end()) {
                    ++output.numberOfNodesCreated;
                    //output.nodesCreated.push_back(nodeNeig);
                    TypeValue  gVal = nodeNow.getGVal() + weightVec[ind];
                    nodeNeig.setGVal(gVal);
                    nodeNeig.setFVal(gVal + heuristic(nodeNeig, nodeFinish));
                    open.push(nodeNeig);
                } else {
                    TypeValue  gVal = nodeNow.getGVal() + weightVec[ind];
                    TypeValue  gOldVal = nodeNeig.getGVal();
                    if (gVal < gOldVal) {
                        TypeValue hVal = heuristic(nodeNeig, nodeFinish);
                        if (open.decreaseVal(nodeNeig, gVal, gVal + hVal)) {
                            std::cout << "error: failure during computation g-values\n"
                                      << "astar attempted to modify f-val in open but did not find it\n"
                                      << std::endl;
                            return false;
                        }
                    }
                }
            }
        }
    }
    return false;  // goal is not reached, thus situation is bad and true is returned
}

bool AStar::constructPath(Output &output)
{
    Node nodeStart{startX, startY, key(startX, startY)};
    unsigned keyNow = key(finishX, finishY);
    Node nodeNow{finishX, finishY, keyNow};
    output.numberOfMovements = 0;
    output.lengtnPath = 0;
    while (nodeNow != nodeStart) {
        output.path.push_back(nodeNow);
        ++output.numberOfMovements;
        Node nodeNext;
        TypeValue minVal;
        bool isInited = false;
        unsigned bestIndMovement;
        for (unsigned ind = 0; ind != weightVec.size(); ++ind) {
            unsigned x1 = nodeNow.getX() + dxVec[ind], y1 = nodeNow.getY() + dyVec[ind];
            Node nodeNeig(x1, y1, key(x1, y1));
            if (close.find(nodeNeig) != close.end()) {
                nodeNeig = close[nodeNeig];
            }
            if (close.find(nodeNeig) != close.end() && (!isInited || nodeNeig.getGVal() < minVal)) {
                nodeNeig = close[nodeNeig];
                nodeNext = nodeNeig;
                minVal = nodeNeig.getGVal();
                isInited = true;
                bestIndMovement = ind;
            }
        }
        if (!isInited) {
            return false;
        }
        output.weightMovements.push_back(weightVec[bestIndMovement]);
        output.lengtnPath += weightVec[bestIndMovement];
        nodeNow = nodeNext;
    }
    return true;
}

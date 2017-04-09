//
// Created by alexgavr on 07.01.17.
//

#include <cmath>
#include <ctime>
#include "../algorithm/astar.h"


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

    //_____define sizes of map (astar needs it)
    open.setMapSizes(task.cntRealRows, task.cntRealCols);
    close.setMapSizes(task.cntRealRows, task.cntRealCols);
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
    unsigned int start_time = clock();
    unsigned int end_time, search_time;
    if (computeGValues(map, output)) {
        if (constructPath(output)) {
            end_time = clock();
            search_time = end_time - start_time;
            output.time = (double)search_time / CLOCKS_PER_SEC;
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
    unsigned keyNow = key(startX, startY);
    Node nodeFinish{finishX, finishY};
    Node nodeNow(startX, startY, (TypeValue)0, 0 + heuristic(nodeNow, nodeFinish));
    nodeNow.setKeyParent(keyNow);
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
        close.push(nodeNow);
        if (nodeNow == nodeFinish) {
            return true;  // returned value;
        }
        
        unsigned ux = nodeNow.getX(), uy = nodeNow.getY();
        for (unsigned ind = 0; ind != dyVec.size(); ++ind) {
            unsigned vx = ux + dxVec[ind];
            unsigned vy = uy + dyVec[ind];
            unsigned keyNeig = key(vx, vy);
            Node nodeNeig{vx, vy};
            if (open.find(nodeNeig) != open.end()) {  // if is already created
                nodeNeig = open[nodeNeig];
            }
            if (!map.isObstacle(vx, vy)  && close.find(nodeNeig) == close.end() &&
                    map.isAllowedFromTo(ux, uy, vx, vy)) {
                if (open.find(nodeNeig) == open.end()) {
                    ++output.numberOfNodesCreated;
                    //output.nodesCreated.push_back(nodeNeig);
                    TypeValue  gVal = nodeNow.getGVal() + weightVec[ind];
                    nodeNeig.setGVal(gVal);
                    nodeNeig.setFVal(gVal + heuristic(nodeNeig, nodeFinish));
                    nodeNeig.setKeyParent(key(nodeNow));
                    open.push(nodeNeig);
                } else {
                    TypeValue  gVal = nodeNow.getGVal() + weightVec[ind];
                    TypeValue  gOldVal = nodeNeig.getGVal();
                    if (gVal < gOldVal) {
                        TypeValue hVal = heuristic(nodeNeig, nodeFinish);
                        if (open.decreaseVal(nodeNeig, gVal, gVal + hVal, key(nodeNow), weightVec[ind])) {
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
    Node nodeStart = close[key(startX, startY)];
    unsigned keyNow = key(finishX, finishY);
    Node nodeNow = close[keyNow];
    TypeValue gValNow = nodeNow.getGVal();
    output.numberOfMovements = 0;
    output.lengtnPath = 0;
    while (nodeNow != nodeStart) {
        Node nodeNext = close[nodeNow.getKeyParent()];
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

//
// Created by alexgavr on 07.01.17.
//

#include <vector>
#include <cmath>
#include <string>
#include "myTask.h"
#include "myLog.h"
#include "myHeap.h"
#include "astar.h"
#include "myOutput.h"

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
    return heuristicHide(node1.x, node1.y, node2.x, node2.y);
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

int AStar::solve(const Task &task, Output &output)
{
    //_____define heuristic_____
    if (task.metricType == "manhattan")
        heuristicHide = &manhattan;
    else if (task.metricType == "euclid")
        heuristicHide = &euclid;
    else {
        heuristicHide = &straight;
        if (task.allowDiag == 1) {
            std::cout << "error: straight is inadmissible heiristic when allowdiag = 1\n";
            exit(0);
        }
    }

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

    //_____algorithm AStar______
    if (!computeGValues(task, output)) {
        if (!constructPath(task, output)) {
            std::cout << "path is succesfully found\n" << std::endl;
            return 0;
        } else {
            std::cout << "error: failure during constructing path\n" << std::endl;
            return 1;
        }
    } else {
        std::cout << "goal is not reached during computation of g-values\n" << std::endl;
        return 1;
    }
    return 0;
}

bool AStar::computeGValues(const Task &task, Output &output)
{
    // open, close are inside AStar astar
    // open is a set of (f-val, Node)
    // close is a set of (Node, g-val);
    // gTable is a local variable
    // gTable is a set of (Node, g-val)

    // gTable and open contain the same nodes;
    // gTable: node -> g-val
    // open: (f-val, node)
    std::map<Node, TypeValue> gTable;
    unsigned startX = task.startX;
    unsigned startY = task.startY;
    unsigned finishX = task.finishX;
    unsigned finishY = task.finishY;
    unsigned keyNow = key(startX, startY);
    Node nodeNow{startX, startY, keyNow};
    Node nodeFinish{finishX, finishY, key(finishX, finishY)};

    open.push(0 + heuristic(nodeNow, nodeFinish), nodeNow);
    gTable[nodeNow] = 0;
    ++output.numberOfNodesCreated;
    // output.nodesCreated.push_back(nodeNow);
    while (!open.empty()) {
        ++output.numberOfSteps;
        nodeNow = open.pop();
        close[nodeNow] = gTable[nodeNow];
        gTable.erase(nodeNow);  // its g-val is not neccessary anymore
        if (nodeNow.key == nodeFinish.key)
            return false;  // returned value is whether situation is bad or not

        unsigned ux = nodeNow.x, uy = nodeNow.y;
        for (unsigned ind = 0; ind != dyVec.size(); ++ind) {
            unsigned vx = ux + dxVec[ind];
            unsigned vy = uy + dyVec[ind];
            unsigned keyNeig = key(vx, vy);
            Node nodeNeig{vx, vy, keyNeig};

            // nodeNeig is not in close
            if (task.map[vx][vy] == 0  && close.find(nodeNeig) == close.end()) {
                if (gTable.find(nodeNeig) == gTable.end()) {
                    ++output.numberOfNodesCreated;
                    //output.nodesCreated.push_back(nodeNeig);
                    TypeValue  gVal = gTable[nodeNow] + weightVec[ind];
                    gTable[nodeNeig] = gVal;
                    open.push(gVal + heuristic(nodeNeig, nodeFinish), nodeNeig);
                } else {
                    TypeValue  gVal = gTable[nodeNow] + weightVec[ind];
                    TypeValue  gOldVal = gTable[nodeNeig];
                    if (gVal < gOldVal) {
                        gTable[nodeNeig] = gVal;
                        TypeValue hVal = heuristic(nodeNeig, nodeFinish);
                        if (open.decreaseVal(gOldVal + hVal, nodeNeig, gVal + hVal)) {
                            std::cout << "error: failure during computation g-values\n"
                                      << "astar attempted to modify f-val in open but did not find it\n"
                                      << std::endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return true;  // goal is not reached, thus situation is bad and true is returned
}

int AStar::constructPath(const Task &task, Output &output)
{
    Node nodeStart{startX, startY, key(startX, startY)};
    unsigned keyNow = key(finishX, finishY);
    Node nodeNow{finishX, finishY, keyNow};
    output.numberOfMovements = 0;
    while (nodeNow.key != nodeStart.key) {
        output.path.push_back(nodeNow);
        ++output.numberOfMovements;
        Node nodeNext;
        TypeValue minVal;
        bool isInited;
        unsigned bestIndMovement;
        for (unsigned ind = 0; ind != weightVec.size(); ++ind) {
            Node nodeNeig;
            nodeNeig.x = nodeNow.x + dxVec[ind];
            nodeNeig.y = nodeNow.y + dyVec[ind];
            nodeNeig.key = key(nodeNeig.x, nodeNeig.y);
            if (close.find(nodeNeig) != close.end() && (!isInited || close[nodeNeig] < minVal)) {
                nodeNext = nodeNeig;
                minVal = close[nodeNeig];
                isInited = true;
                bestIndMovement = ind;
            }
        }
        if (!isInited) {
            return 1;
        }
        output.weightMovements.push_back(weightVec[bestIndMovement]);
        nodeNow = nodeNext;
    }
    return 0;
}

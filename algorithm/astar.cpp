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
    Node nodeFinish{finishX, finishY};
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
                TypeValue  gVal = nodeNow.getGVal() + weightVec[ind];
                nodeNeig.setGVal(gVal);
                nodeNeig.setFVal(gVal + heuristic(nodeNeig, nodeFinish));
                nodeNeig.setParent(pNodeNow);
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

//
// Created by alexgavr on 07.01.17.
//

#include <vector>
#include <cmath>
#include <string>
#include "myTask.h"
#include "myHeap.h"
#include "astar.h"


typedef double TypeValue;

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

inline unsigned AStar::key(unsigned ux, unsigned uy)
{
    return ux * (task.cntRealCols + 2) + uy;
}

inline unsigned AStar::coordinateFirst(unsigned key)
{
    return key / (task.cntRealCols + 2);
}

inline unsigned AStar::coordinateSecond(unsigned key)
{
    return key % (task.cntRealCols + 2);
}


int AStar::solve(const Task &task)
{
    this->task = task;
    //_____define heuristic_____
    if (task.metricType == "manhattan")
        heuristic = &manhattan;
    else if (task.metricType == "euclid")
        heuristic = &euclid;
    else
        heuristic = &straight;


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
    if (computeGValues()) {
        path = constructPath();
        return 0;
    } else {
        std::cout << "\nThere is no any path to goal\n";
        return 1;
    }

}

bool AStar::computeGValues()
{
    Heap opened;  // conceptually Heap is a set of pairs (f-value, key)
    std::map<unsigned, bool> visited;
    std::map<unsigned, bool> closed;
    unsigned startX = task.startX;
    unsigned startY = task.startY;
    unsigned finishX = task.finishX;
    unsigned finishY = task.finishY;
    unsigned keyNow = key(startX, startY);

    opened.push(0 + heuristic(startX, startY, finishX, finishY), keyNow);
    prevTable[keyNow] = keyNow;
    gTable[keyNow] = 0;
    visited[keyNow] = true;
    while (!opened.empty()) {
        keyNow = opened.pop();
        closed[keyNow] = true;
        if (keyNow == key(finishX, finishY))
            return true;

        unsigned ux = coordinateFirst(keyNow), uy = coordinateSecond(keyNow);
        for (unsigned ind = 0; ind != dyVec.size(); ++ind) {
            unsigned vx = ux + dxVec[ind];
            unsigned vy = uy + dyVec[ind];
            unsigned keyNeig = key(vx, vy);
            if (task.map[vx][vy] == 0) {
                if (!visited[keyNeig]) {  // we must init gvalue of keyNeig
                    visited[keyNeig] = true;
                    TypeValue gVal = gTable[keyNow] + weightVec[ind];
                    opened.push(gVal + heuristic(vx, vy, finishX, finishY), keyNeig);
                    gTable[keyNeig] = gVal;
                    prevTable[keyNeig] = keyNow;
                } else if (!closed[keyNeig]) {  // we must update gvalue
                    TypeValue gOld = gTable[keyNeig];
                    TypeValue gPretendent = gTable[keyNow] + weightVec[ind];
                    if (gOld > gPretendent) {
                        if (!opened.decreaseVal(gOld + heuristic(vx, vy, finishX, finishY),
                                                keyNeig, gPretendent + heuristic(vx, vy, finishX, finishY))) {
                            prevTable[keyNeig] = keyNow;
                            gTable[keyNeig] = gPretendent;
                        } else {
                            std::cout << "error: failure during computation g-values\n";
                        }
                    }
                }
            }
        }
    }
    return false;
}

std::vector<unsigned> AStar::constructPath()
{
    unsigned now = key(task.finishX, task.finishY);
    while (now != key(task.startX, task.startY)) {
        path.push_back(now);
        now = prevTable[now];
    }
    return path;
}

void AStar::printPath()
{
    if (path.size() == 0) {
        std::cout << "error: there is no inited path\n";
        return;
    } else {
        for (int ind = path.size() - 1; ind != -1; --ind) {
            std::cout << "number " << path.size() - ind << ": "
                      << coordinateFirst(path[ind]) << ' ' << coordinateSecond(path[ind]) << '\n';
        }
    }
}
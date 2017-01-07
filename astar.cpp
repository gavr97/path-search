//
// Created by alexgavr on 07.01.17.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "myMap.h"
#include "astar.h"

void astar(const Task &task, std::vector<std::vector<std::pair<short, short>>> &adjTable)
{
    // ... alg

}

void solve(const Task &task)
{
    std::vector<std::vector<std::pair<short, short>>>
            adjTable(task.cntRealRows + 2,
            std::vector<std::pair<short, short>>(task.cntRealCols + 2, {0, 0}));
    astar(task, adjTable);
    // reestablish path with adjTable;
}
#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "myMap.h"
#include "astar.h"

int main() {
    int myeResult = 0;
    Task task;
    myeResult = task.myLoad("input/3664933.xml");  // char* ! not std::string
    task.print();

    AStar astar;
    myeResult = astar.solve(task);  // myeResult == 1 if no path found; else 0;
    if (!myeResult) {
        astar.printPath();
    }
    return 0;
}
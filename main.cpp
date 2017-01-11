#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "myMap.h"
#include "astar.h"

int main() {
    int myeResult = 0;
    Task task;
    myeResult = task.myLoad("input/3622198.xml");  // char* ! not std::string
    task.print();

    AStar astar;
    vector<unsigned> path = astar.solve(task);
    std::cout << "size of found best path is " << path.size();
    return 0;
}
#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "myTask.h"
#include "astar.h"

int main() {
    std::vector<char*> list = {"input/3622198.xml", "input/3664933.xml", "input/3839748.xml", "input/4123378.xml",
                                "input/4226598.xml", "input/4320060.xml"};

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
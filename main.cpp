#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "myTask.h"
#include "astar.h"

#include <fstream>
#include <ctime>

int main() {
    std::vector<const char*> list = {"input/3622198.xml", "input/3664933.xml","input/3839748.xml", "input/4123378.xml",
                                "input/4226598.xml", "input/4320060.xml"};
    std::fstream F;
    F.open("time.txt");
    unsigned int start_time = clock();
    for (const char *name : list) {
        int myeResult = 0;
        Task task;
        myeResult = task.myLoad(name);  // char* ! not std::string
        task.print();

        AStar astar;
        myeResult = astar.solve(task);  // myeResult == 1 if no path found; else 0;
        if (!myeResult) {
            //astar.printPath();
        }
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    F << search_time << "\t";
    return 0;
}
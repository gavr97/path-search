#include <iostream>
#include <vector>
#include "dataCode/task.h"
#include "logger/log.h"
#include "dataCode/output.h"
#include "algorithm/astar.h"

#include <fstream>
#include <ctime>

int main(int argc, char *argv[]) {
    int RES = 0;
    //________specify input and output names________
    if (argc == 1) {
        std::cout << "error: input XML is not specified\n";
        return 1;
    }
    const char *nameIn = argv[1];
    const char *nameOut;
    if (argc > 2) {
        nameOut = argv[2];
    } else {
        nameOut = "out.xml";
    }
    std:: cout << "name of input = " << nameIn << std::endl;
    std:: cout << "name of output = " << nameOut << std::endl << std::endl;

    //________Init Task________
    int myeResult = 0;
    Task task; Output output; Log log;
    myeResult = task.myLoad(nameIn);  // char* ! not std::string;
    if (myeResult) {
        std::cout << "task: " << nameIn << " is skipped\n";
        return 1;
    }
    task.print();

    //_______Init AStar and Map_____
    Map map(task.grid);
    AStar astar;
    myeResult = astar.init(task);
    if (myeResult) {
        std::cout << "error: failure during initializing astar\n";
        return 1;
    }

    //_______Solve Task_________
    myeResult = astar.solve(map, output);  // myeResult == 1 if no path found; else 0;
    if (myeResult) {
        std::cout << "no path found in task\n"
                  << "Naturally, Path is not saved in output\n";
        RES = 1;
    } else {
        std::cout << "path is found\n";
        RES = 0;
    }

    //_____Save results and write_____
    myeResult = log.saveData(nameIn, output, map);  // arg-map is neccessary because of drawing map with path
    log.write(nameOut);
    // на данный момент логгер уже ПРИВЯЗАН к текущей задаче(имеет поле xmlDoc, соответствующее этой задаче)
    // log.clean()??
    return RES;
}

#include <iostream>
#include <vector>
#include "dataCode/task.h"
#include "logger/log.h"
#include "dataCode/output.h"
#include "algorithm/astar.h"
#include "algorithm/theta.h"

#include <fstream>
#include <ctime>

int main(int argc, char *argv[]) {
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

    //________Init Task________  reads everything except GRID. It is for Map
    int myeResult = 0;
    Task task;
    myeResult = task.myLoad(nameIn);  // char* ! not std::string;
    if (myeResult) {
        std::cout << "task: " << nameIn << " is skipped\n"
                  << "out XML is not generated\n";
        return 1;
    }

    //_______Init Map_____
    Map map;
    myeResult = map.readMap(nameIn);
    if (myeResult) {
        std::cout << "task: " << nameIn << " is skipped\n"
                  << "out XML is not generated\n";
        return 1;
    }
    task.allowSqueeze = 1;
    task.allowDiag = 1;
    task.cutCorners = 1;
    task.print();
    map.print();

    task.searchType = "jp_search";

    if (task.searchType == THETA) {
        std::cout << "THETA is working\n";
        Theta solver;
        myeResult = solver.init(task);
        if (myeResult) {
            std::cout << "error: failure during initializing solver\n"
                      << "out XML is not generated\n";
            return 1;
        }
        //_______Solve Task_________
        Output output;
        myeResult = solver.solve(map, output);  // myeResult == 1 if no path found; else 0;
        if (myeResult) {
            std::cout << "no path found in task\n"
                      << "out XML is not generated\n";
            return 1;
        } else {
            std::cout << "path is found\n";
            //_____Save results and write_____
            Log log;
            myeResult = log.saveData(nameIn, output, map);  // arg-map is neccessary because of drawing map with path
            log.write(nameOut);
            return 0;
        }
    } else if (task.searchType == ASTAR || task.searchType == JPS){
        std::cout << "ASTAR or JPS is working\n";
        AStar solver;
        myeResult = solver.init(task);
        if (myeResult) {
            std::cout << "error: failure during initializing solver\n"
                      << "out XML is not generated\n";
            return 1;
        }
        //_______Solve Task_________
        Output output;
        myeResult = solver.solve(map, output);  // myeResult == 1 if no path found; else 0;
        if (myeResult) {
            std::cout << "no path found in task\n"
                      << "out XML is not generated\n";
            return 1;
        } else {
            std::cout << "path is found\n";
            //_____Save results and write_____
            Log log;
            myeResult = log.saveData(nameIn, output, map);  // arg-map is neccessary because of drawing map with path
            log.write(nameOut);
            return 0;
        }
    } else {
        std::cout << "error: task is inited incorrectly: search type is specified badly\n";
        return 1;
    }
}

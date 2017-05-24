#include <iostream>
#include <vector>
#include "dataCode/task.h"
#include "logger/log.h"
#include "dataCode/output.h"
#include "algorithm/astar.h"
#include "algorithm/theta.h"
#include "algorithm/jps.h"

#include <fstream>
#include <ctime>

int main(int argc, char *argv[]) {
    //________specify input and output names________
    if (argc == 1) {
        std::cout << "error: input XML is not specified\n";
        return 1;
    }
    std::string nameIn = argv[1];
    std::string nameOut;
    std:: cout << "name of input = " << nameIn << std::endl;

    //________Init Task________  reads everything except GRID and allowDiag,.., cutCorners. It is for Map
    int myeResult = 0;
    Task task;
    myeResult = task.myLoad(nameIn);  // char* ! not std::string;
    if (myeResult) {
        std::cout << "task: " << nameIn << " is skipped\n"
                  << "out XML is not generated\n";
        return 1;
    }
    // TODO
    if (argc >= 3)
        nameOut = argv[2];
    else
        nameOut = "out.xml";

    //_______Init Map_____
    Map map;
    myeResult = map.readMap(nameIn);
    if (myeResult) {
        std::cout << "task: " << nameIn << " is skipped\n"
                  << "out XML is not generated\n";
        return 1;
    }
    task.print();
    map.print();

    //______Init Solver_____
    AStar *pSolver;
    try {
        if (task.searchType == THETA) {
            pSolver = new Theta(task, map);
            std::cout << "Theta is working\n";
        } else if (task.searchType == JPS) {
            pSolver = new Jps(task, map);
            std::cout << "Jps is working\n";
        } else if (task.searchType == ASTAR) {
            pSolver = new AStar(task, map);
            std::cout << "AStar is working\n";
        } else {
            throw 1;
        }
    } catch (int e) {
        std::cout << "error: solver is not inited\n";
        return 1;
    }
    //pSolver->init(task, map);

    //_______Solve Task_________
    Output output(task.cellSize);
    myeResult = pSolver->solve(map, output);  // myeResult == 1 if no path found; else 0;
    if (myeResult) {
        std::cout << "no path found in task\n"
                  << "out XML is not generated\n";
        delete pSolver;
        return 1;
    } else {
        std::cout << "path is found\n";
        std::cout << "len of path " << output.lengtnPath << '\n';
        //_____Save results and write_____
        Log log;
        myeResult = log.saveData(nameIn, output, map);
        log.write(nameOut);
        delete pSolver;
        return 0;
    }
}

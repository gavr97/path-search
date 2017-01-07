#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "myMap.h"
//#include "astar.h"

void printTask(Task task)
{
    std::cout << "\nTask:\n";
    std::cout << "size: " << task.cntRealRows << ' ' << task.cntRealCols << std::endl;
    std::cout << "map\n";
    //for (const auto &row : task.map) {
    //    for (const auto &elem : row) {
    //        std::cout << elem << ' ';
    //    }
    //    std::cout << std::endl;
    //}
    std::cout << '\n';
    std::cout << "costs of movements: " << task.lineCost << " and " << task.diagCost << std::endl;
    printf("start and end: %u %u and %u %u\n", task.startX, task.startY, task.finishX, task.finishY);
    std::cout << "search type and metric type: " << task.searchType << " and " << task.metricType << std::endl;
    std::cout << "about movements: " << task.allowDiag << ' ' << task.allowSqueeze << ' ' << task.cutCorners << std::endl;
}

int main() {
    int myeResult = 0;
    Task task;
    myeResult = myLoad("input/my.xml", task);
    //myeResult = myLoad("my.xml", task);

    printTask(task);
    return 0;
}
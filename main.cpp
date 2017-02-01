#include <iostream>
#include <vector>
#include "myTask.h"
#include "myLog.h"
#include "myOutput.h"
#include "astar.h"

#include <fstream>
#include <ctime>

int main() {
    std::vector<const char*> list = {"input/my1.xml"};//, "example.xml", "input/3622198.xml","input/3664933.xml"};//,"input/3839748.xml", "input/4123378.xml",
                                 //"input/4226598.xml", "input/4320060.xml"};
    //std::fstream F;
    //F.open("time.txt");
    unsigned int start_time = clock();
    for (const char *name : list) {
        int myeResult = 0;
        Task task;
        Output output;
        Log log;
        myeResult = task.myLoad(name, log);  // char* ! not std::string;
                                            // log is sent as an argument for storing XMLDoc for future out to a user
        if (myeResult) {
            std::cout << "task: " << name << " is skipped\n\n";
            continue;
        }
        task.print();
        AStar astar;
        myeResult = astar.solve(task, output);  // myeResult == 1 if no path found; else 0;
        if (!myeResult) {
            output.printPath(output.path);
        }
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    //F << search_time << "\t";
    return 0;
}
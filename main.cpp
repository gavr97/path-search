#include <iostream>
#include <vector>
#include "dataCode/myTask.h"
#include "logger/myLog.h"
#include "dataCode/myOutput.h"
#include "algorithm/astar.h"

#include <fstream>
#include <ctime>
#include <cstring>

int main() {
    std::vector<const char*> list = {"smallWithoutPath.xml", "withoutPath.xml"}; //{"my1.xml", "example.xml", "3622198.xml","3664933.xml", "withoutPath.xml"};//,"input/3839748.xml", "input/4123378.xml",
                                 //"input/4226598.xml", "input/4320060.xml"};
    //std::fstream F;
    //F.open("time.txt");
    unsigned int start_time = clock();
    for (const char *name : list) {
        std::cout << std::endl << "\n" << "NEXT TASK\n";
        int myeResult = 0;
        Task task; Output output; Log log;
        //_____Load Task_____
        char nameIn[strlen(name) + 12] = "input/";
        strcat(nameIn, name);
        myeResult = task.myLoad(nameIn, log);  // char* ! not std::string;
                                            // log is sent as an argument for storing XMLDoc for future out to a user
        if (myeResult) {
            std::cout << "task: " << name << " is skipped\n\n";
            continue;
        }
        task.print();

        //____Solve Task______
        AStar astar;
        myeResult = astar.solve(task, output);  // myeResult == 1 if no path found; else 0;
        if (myeResult) {
            std::cout << "no path found in task\n"
                      << "this task is skipped. Naturally, Path is not saved in output\n";
        } else {
            output.printPath(output.path);
        }

        //_____Save results and write____
        myeResult = log.saveData(output, nameIn);
        char nameOut[strlen(name) + 12] = "./myLogs/";
        strcat(nameOut, name);
        log.write(nameOut);
        // на данный момент логгер уже ПРИВЯЗАН к текущей задаче(имеет поле xmlDoc, соответствующее этой задаче)
        // log.clean()???
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    //F << search_time << "\t";
    return 0;
}
//
// Created by alexgavr on 01.02.17.
//

#include <iostream>
#include "myOutput.h"

Output::Output()
{
    time = 0;
    numberOfNodesCreated = 0;
    numberOfSteps = 0;
}

void Output::printPath(const std::vector<Node> &path)
{
    if (path.size() == 0) {
        std::cout << "error: there is no inited path\n";
        return;
    } else {
        for (int ind = path.size() - 1; ind != -1; --ind) {
            std::cout << "number " << path.size() - ind - 1 << ": "
                      << path[ind].y - 1 << ' ' << path[ind].x - 1 << '\n';
            // again transposing and --
            // for user
        }
    }
}

//
// Created by alexgavr on 01.02.17.
//

#ifndef REPO_MYRESULT_H
#define REPO_MYRESULT_H

#include "../global/globalTypes.h"

// contains neccessary dataCode for output for one task
class Output {
public:
    double time;
    unsigned numberOfNodesCreated;
    unsigned numberOfSteps;
    unsigned numberOfMovements;
    std::vector<Node> nodesCreated;
    std::vector<Node> path;  // reversed;
    std::vector<double> weightMovements;  // if we consider vec reversed, i.e. index == vec.size()-1 is 0, then
                                        // vec[index] contains weight from node == path[index] to node == path[index-1]
                                        // and thus conceptually indexing of vec begins from 1!

    Output();
    void printPath(const std::vector<Node> &path);
};

#endif //REPO_MYRESULT_H

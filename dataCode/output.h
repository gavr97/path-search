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
    double lengtnPath;
    std::vector<Node> nodesCreated;
    std::vector<Node> path;  // reversed;
    std::vector<double> weightMovements;  // size of weightMovements is less by 1 thah path
                                        // if we look at vectors from ends then nowWeight if for
                                        // edge from now to next
                                        // formally: weightMovements[ind] is for edge from path[ind+1] to path[ind]


    Output();
    void printPath(const std::vector<Node> &path);
};

#endif //REPO_MYRESULT_H

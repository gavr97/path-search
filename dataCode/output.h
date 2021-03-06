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
    double cellSize;
    double lineCost;
    std::vector<Node> nodesCreated;
    std::vector<Node> path;  // reversed;
    std::vector<Node> otherPath;  // reversed;

    // size of weightMovements is less by 1 thah path
    // if we look at vectors from ends then nowWeight if for
    // edge from now to next
    // formally: weightMovements[ind] is for edge from path[ind+1] to path[ind]
    std::vector<TypeValue> weightMovements;
    std::vector<TypeValue> otherWeightMovements;

    bool isLowLevel;

    Output(double cellSize, double lineCost);
    void printPath(const std::vector<Node> &path);
};

#endif //REPO_MYRESULT_H

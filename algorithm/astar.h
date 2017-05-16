#ifndef REPO_ASTAR_H
#define REPO_ASTAR_H

#include <iostream>
#include <vector>
#include "../global/globalTypes.h"
#include "../dataCode/task.h"
#include "../dataCode/output.h"
#include "../dataCode/map.h"
#include "open.h"
#include "close.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::pair;

class AStar {
protected:
    //____members that define features of algorithm(object)_____
    TypeValue (*heuristicHide)(unsigned ux, unsigned uy, unsigned vx, unsigned vy);
    TypeValue heuristic(const Node &node1, const Node &node2) const;
    std::vector<short> dxVec;
    std::vector<short> dyVec;
    std::vector<TypeValue> weightVec;

    //____ commom members______
    unsigned cntRealCols;
    unsigned cntRealRows;
    unsigned startX;
    unsigned startY;
    unsigned finishX;
    unsigned finishY;
    Node nodeStart;
    Node nodeFinish;

    Close close; //std::unordered_map<unsigned, Node> close;  // node->g-value
    Open open;  // a set of pairs(f-value, Node)

    unsigned key(unsigned ux, unsigned uy) const;
    unsigned key(const Node &node) const;
    unsigned coordinateFirst(unsigned key);
    unsigned coordinateSecond(unsigned key);

    bool computeGValues(const Map &map, Output &output);
    bool constructPath(Output &output);
    virtual void computeCost(const Node *const pNodeParent, Node &nodeSon, const Map &map) const;
    virtual std::vector<Node> getSuccessors(const Node &node, const Map &map) const;
    virtual void setLevelPath(Output &output);  // if JPS or Theta then output.isLowLevel := false;
    void lowToHigh
            (const std::vector<Node> &path,
             const std::vector<TypeValue> &weightMovements,
             std::vector<Node> &otherPath,
             std::vector<TypeValue> &otherWeightMovements
            ) const;
    void highToLow
            (const std::vector<Node> &path,
             const std::vector<TypeValue> &weightMovements,
             std::vector<Node> &otherPath,
             std::vector<TypeValue> &otherWeightMovements
            ) const;

public:
    int init(const Task &task);
    int solve(const Map &map, Output &output);
};

#endif //REPO_ASTAR_H

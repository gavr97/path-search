#ifndef ASEARCH_THETA_H
#define ASEARCH_THETA_H

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include "../dataCode/task.h"
#include "../global/globalTypes.h"
#include "../dataCode/output.h"
#include "../dataCode/map.h"
#include "open.h"
#include "close.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::pair;

class Theta {
private:
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

    inline unsigned key(unsigned ux, unsigned uy) const;
    inline unsigned key(const Node &node) const;
    inline unsigned coordinateFirst(unsigned key);
    inline unsigned coordinateSecond(unsigned key);

    bool computeGValues(const Map &map, Output &output);
    bool constructPath(Output &output);
    // the best best path for nodeSon across nodeParent or nodeGrandParent
    void computeCost(const Node *const pNodeParent, Node &nodeSon, const Map &map) const;

    void setLevelPath(Output &output);
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
    int init (const Task &task);
    int solve(const Map &map, Output &output);
};



#endif //ASEARCH_THETA_H
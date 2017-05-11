#include "heuristics.h"
#include <ctime>
#include "../algorithm/theta.h"

void Theta::computeCost(const Node *const pNodeParent, Node &nodeSon, const Map &map) const
{
    const Node nodeParent = *pNodeParent;
    const Node * const pNodeGrandParent = nodeParent.getParent();

    const Node * pNodePretendent;
    Node nodePretendent;
    if (pNodeGrandParent != nullptr && map.lineOfSight(*pNodeGrandParent, nodeSon)) {
        pNodePretendent = pNodeGrandParent;
        nodePretendent = *pNodePretendent;
    } else {
        pNodePretendent = pNodeParent;
        nodePretendent = *pNodePretendent;
    }

    TypeValue  gVal = nodePretendent.getGVal() + heuristic(nodePretendent, nodeSon);
    nodeSon.setGVal(gVal);
    nodeSon.setFVal(gVal + heuristic(nodeSon, nodeFinish));
    nodeSon.setParent(pNodePretendent);
}

void Theta::setLevelPath(Output &output)
{
    output.isLowLevel = false;
}

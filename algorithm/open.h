//
// Created by alexgavr on 14.03.17.
//

#ifndef REPO_OPEN_H
#define REPO_OPEN_H

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "../global/globalTypes.h"

class Open {
private:
    std::set<Node> set;
    std::unordered_map<unsigned, Node> hash_table;

    unsigned cntRealCols;
    unsigned cntRealRows;
    inline unsigned key(unsigned x, unsigned y) const;
    inline unsigned key(const Node &node) const;

public:
    void push(const Node &node);
    Node pop();
    bool decreaseVal(Node &node, TypeValue gVal, TypeValue fVal, unsigned keyNewParent, TypeValue weightMovement);
    Node getNode(unsigned x, unsigned y, bool &wasCreated);

    std::unordered_map<unsigned, Node>::const_iterator find(const Node &node) const;
    std::unordered_map<unsigned, Node>::const_iterator end() const;

    Node operator[](const Node &node) const;
    bool empty() const;
    unsigned size() const;
    void setMapSizes(unsigned cntRealRows, unsigned cntRealCols);
};


#endif //REPO_OPEN_H

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

public:
    void push(const Node &node);
    Node pop();
    bool decreaseVal(Node &node, TypeValue gVal, TypeValue fVal, unsigned keyNewParent, TypeValue weightMovement);

    std::unordered_map<unsigned, Node>::const_iterator find(const Node &node) const;
    std::unordered_map<unsigned, Node>::const_iterator end() const;

    Node operator[](const Node &node) const;
    bool empty() const;
    unsigned size() const;
};


#endif //REPO_OPEN_H

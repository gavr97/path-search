#ifndef REPO_MYHEAP_H
#define REPO_MYHEAP_H

#include <iostream>
#include <vector>
#include <set>
#include "globalTypes.h"

typedef double TypeValue;

class Heap {
private:
    std::set<std::pair<TypeValue, Node>> set;

public:
    void push(TypeValue val, Node node)
    {
        set.insert({val, node});
    }

    Node pop()
    {
        Node node = set.begin()->second;
        set.erase(set.begin());
        return node;
    }

    bool decreaseVal(TypeValue oldVal, Node node, TypeValue newVal)
    {
        auto ptr = set.find({oldVal, node});
        if (ptr == set.end())
            return true;  // an error occured
        set.erase(ptr);
        set.insert({newVal, node});
        return false;
    }

    bool empty()
    {
        return set.empty();
    }
};


#endif //REPO_MYHEAP_H

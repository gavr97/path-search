#ifndef REPO_MYHEAP_H
#define REPO_MYHEAP_H

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "../global/globalTypes.h"

typedef double TypeValue;

class Heap {
private:
    std::set<Node> set;
    std::unordered_map<unsigned, Node> hash_table;

public:
    void push(Node node)
    {
        set.insert(node);
        hash_table.[node.key] = node;
    }

    Node pop()
    {
        Node node = *(set.begin());
        set.erase(set.begin());
        hash_table.erase(node.key);
        return node;
    }

    bool decreaseVal(Node node, TypeValue newVal)
    {
        auto ptr = set.find(node);
        if (ptr == set.end())
            return true;  // an error occured
        set.erase(ptr);
        node.fVal = newVal;
        set.insert(node);
        return false;
    }

    bool empty()
    {
        return set.empty();
    }
};


#endif //REPO_MYHEAP_H

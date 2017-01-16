#ifndef REPO_MYHEAP_H
#define REPO_MYHEAP_H

#include <iostream>
#include <vector>
#include <set>

typedef double TypeValue;

class Heap {
private:
    std::set<std::pair<TypeValue, unsigned>> set;

public:
    void push(TypeValue val, unsigned key)
    {
        set.insert({val, key});
    }

    unsigned pop()
    {
        unsigned key = set.begin()->second;
        set.erase(set.begin());
        return key;
    }

    bool decreaseVal(TypeValue oldVal, unsigned key, TypeValue newVal)
    {
        auto ptr = set.find({oldVal, key});
        if (ptr == set.end())
            return true;
        set.erase(ptr);
        set.insert({newVal, key});
        return false;
    }

    bool empty()
    {
        return set.empty();
    }
};


#endif //REPO_MYHEAP_H
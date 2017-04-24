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
#include <list>
#include "../global/globalTypes.h"

class Open {
private:
    Node nodeMin;
    bool _empty;

    unsigned cntRealCols;
    unsigned cntRealRows;
    std::vector<std::list<Node> > lists;

    inline unsigned key(unsigned x, unsigned y) const;
    inline unsigned key(const Node &node) const;

public:
    void push(const Node &node);
    bool update(const Node &node, bool &wasCreated);  // returned val is whether is pushed or not
                                                                    // wasCreated for countind created nodes
    Node pop();
    Node getNode(unsigned x, unsigned y, bool &wasCreated);
    bool empty() const;
    void init(unsigned cntRealRows, unsigned cntRealCols);  // in other words it is constructor for Open
};

#endif //REPO_OPEN_H

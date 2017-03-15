//
// Created by alexgavr on 15.03.17.
//

#ifndef REPO_NODE_H
#define REPO_NODE_H

struct Node{
    unsigned x;
    unsigned y;
    unsigned key;
    TypeValue gVal;
    TypeValue fVal;

    bool operator == (const Node &right) const;
    bool operator <(const Node &right) const;
    bool operator != (const Node &right) const;
};

#endif //REPO_NODE_H

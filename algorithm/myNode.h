//
// Created by alexgavr on 01.02.17.
//

#ifndef REPO_MYNODE_H
#define REPO_MYNODE_H

struct Node{
    unsigned x;
    unsigned y;
    unsigned key;
    double gVal;
    double fVal;
    bool isCreated;

    bool operator <(const Node &right) const;
    bool operator <(Node &right);
};

#endif //REPO_MYNODE_H

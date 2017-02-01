//
// Created by alexgavr on 01.02.17.
//

#ifndef REPO_MYNODE_H
#define REPO_MYNODE_H

struct Node{
    unsigned x;
    unsigned y;
    unsigned key;

    bool operator <(const Node &right);
};

#endif //REPO_MYNODE_H
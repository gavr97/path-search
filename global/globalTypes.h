//
// Created by alexgavr on 29.01.17.
//

#ifndef REPO_CONSTANTTYPES_H
#define REPO_CONSTANTTYPES_H

#include <vector>

typedef double TypeValue;

struct Node{
    unsigned x;
    unsigned y;
    unsigned key;
    TypeValue gVal;
    TypeValue fVal;

    bool operator == (const Node &right) const;
    bool operator <(const Node &right) const;
    bool operator <(Node &right);
};

typedef std::vector<Node> Path;
typedef std::vector<char> GridRow;
typedef std::vector<GridRow> Grid;

#endif //REPO_CONSTANTTYPES_H
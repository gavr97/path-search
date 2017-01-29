//
// Created by alexgavr on 29.01.17.
//

#ifndef REPO_CONSTANTTYPES_H
#define REPO_CONSTANTTYPES_H

#include <vector>

typedef std::vector<unsigned> Path;
typedef unsigned  Node;
typedef double TypeValue;

struct Tripple{  // for storing data about nodes in prevTable
    unsigned ux;
    unsigned uy;
    TypeValue length;
};


#endif //REPO_CONSTANTTYPES_H
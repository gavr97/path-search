//
// Created by alexgavr on 20.02.17.
//

#ifndef REPO_MAP_H
#define REPO_MAP_H

#include <vector>
#include "../algorithm/myNode.h"

class Map {
public:
    std::vector<GridRow> grid;

public:
    Map(std::vector<GridRow> grid);
    bool isObstacle(Node node) const;
    bool isObstacle(unsigned x, unsigned y) const;
};


#endif //REPO_MAP_H

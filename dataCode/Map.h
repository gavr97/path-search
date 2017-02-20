//
// Created by alexgavr on 20.02.17.
//

#ifndef REPO_MAP_H
#define REPO_MAP_H

#include <vector>
#include "../algorithm/myNode.h"

typedef std::vector<char> MapRow;

class Map {
public:
    std::vector<MapRow> grid;

public:
    Map(std::vector<MapRow> grid);
    bool isObstacle(Node node) const;
    bool isObstacle(unsigned x, unsigned y) const;
};


#endif //REPO_MAP_H

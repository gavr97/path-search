//
// Created by alexgavr on 20.02.17.
//

#include "map.h"

Map::Map(std::vector<MapRow> grid)
{
    this->grid = grid;
}

bool Map::isObstacle(Node node) const
{
    return grid[node.x][node.y] == '1';
}

bool Map::isObstacle(unsigned x, unsigned y) const
{
    return grid[x][y] == '1';
}
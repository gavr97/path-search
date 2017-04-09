//
// Created by alexgavr on 20.02.17.
//

#ifndef REPO_MAP_H
#define REPO_MAP_H

#include <vector>
#include "../tinyxml/tinyxml2.h"
#include "../global/globalTypes.h"

using namespace tinyxml2;

class Map {

private:
    unsigned cntRealRows;
    unsigned cntRealCols;
    bool allowDiag;
    bool allowSqueeze;
    bool cutCorners;

    int readInt(XMLNode *pRoot, const char *tag, unsigned int &destination, unsigned int DEFAULT, bool obligatory);
    int readGrid(XMLNode *pRoot, Grid &grid);

public:
    std::vector<GridRow> grid;
    Map();

    Map(const char *nameIn);
    bool isObstacle(const Node &node) const;
    bool isObstacle(unsigned x, unsigned y) const;
    bool isAllowedFromTo(unsigned ux, unsigned uy, unsigned vx, unsigned vy) const;
    int readMap(const char *nameIn);
};


#endif //REPO_MAP_H

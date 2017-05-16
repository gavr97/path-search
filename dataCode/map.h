#ifndef REPO_MAP_H
#define REPO_MAP_H

#include "../tinyxml/tinyxml2.h"
#include "../global/globalTypes.h"

using namespace tinyxml2;

class Map {
private:
    unsigned cntRealRows;
    unsigned cntRealCols;

    int readInt(XMLNode *pRoot, const char *tag, unsigned int &destination, unsigned int DEFAULT, bool obligatory);
    int readStr(XMLNode *pRoot, const char *tag, std::string &destination, const std::string DEFAULT, bool obligatory);
    int readGrid(XMLNode *pRoot, Grid &grid);

public:
    bool allowDiag;
    bool allowSqueeze;
    bool cutCorners;

    std::vector<GridRow> grid;
    Map();

    Map(const char *nameIn);
    bool isObstacle(const Node &node) const;
    bool isObstacle(unsigned x, unsigned y) const;
    bool isAllowedFromTo(unsigned ux, unsigned uy, unsigned vx, unsigned vy) const;
    int readMap(std::string nameIn);
    bool lineOfSight(const Node &node1, const Node &node2) const;
    bool lineOfSight(unsigned ux, unsigned uy, unsigned vx, unsigned vy) const;
    void print() const;
};


#endif //REPO_MAP_H

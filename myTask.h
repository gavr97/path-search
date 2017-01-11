//
// Created by alexgavr on 07.01.17.
//

#ifndef REPO_MYMAP_H
#define REPO_MYMAP_H

#include <vector>
#include "tinyxml2.h"
#include <string>

using namespace tinyxml2;


class Task{
public:
    unsigned int cntRealRows;
    unsigned int cntRealCols;
    std::vector<std::vector<short>> map;
    double lineCost;
    double diagCost;
    unsigned int allowDiag;
    unsigned int allowSqueeze;
    unsigned int cutCorners;

    std::string searchType;
    unsigned int startX;
    unsigned int startY;
    unsigned int finishX;
    unsigned int finishY;
    std::string metricType;

    int myLoad(const char *path);

    void print() const;

private:
    int readInt(XMLNode *pRoot, const char *tag, unsigned int &destination, unsigned int DEFAULT, bool obligatory);

    int readDouble(XMLNode *pRoot, const char *tag, double &destination, double DEFAULT, bool obligatory);

    int readStr(XMLNode *pRoot, const char *tag, std::string &destination, const std::string DEFAULT, bool obligatory);

    int readMap(XMLNode *pRoot, std::vector<std::vector<short>> &map);
};




#endif //REPO_MYMAP_H

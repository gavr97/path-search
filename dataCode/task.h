#ifndef REPO_MYMAP_H
#define REPO_MYMAP_H

#include "../tinyxml/tinyxml2.h"
#include <string>
#include "../global/globalTypes.h"
#include "../global/globalVars.h"

using namespace tinyxml2;

class Task{
public:
    unsigned int cntRealRows;
    unsigned int cntRealCols;
    Grid grid;
    double lineCost;
    double diagCost;

    std::string searchType;
    unsigned int startX;
    unsigned int startY;
    unsigned int finishX;
    unsigned int finishY;
    std::string metricType;

    int myLoad(const char *nameIn);
    void print() const;

private:
    int readInt(XMLNode *pRoot, const char *tag, unsigned int &destination, unsigned int DEFAULT, bool obligatory);

    int readDouble(XMLNode *pRoot, const char *tag, double &destination, double DEFAULT, bool obligatory);

    int readStr(XMLNode *pRoot, const char *tag, std::string &destination, const std::string DEFAULT, bool obligatory);
};

#endif //REPO_MYMAP_H

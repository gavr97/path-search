#ifndef REPO_MYLOG_H
#define REPO_MYLOG_H

#include <vector>
#include "../tinyxml/tinyxml2.h"
#include "../global/globalTypes.h"
#include "../global/globalVars.h"
#include "../dataCode/output.h"
#include "../dataCode/map.h"

using namespace tinyxml2;

class Log {
private:
    XMLDocument xmlDoc;
    unsigned rememberedX;
    unsigned rememberedY;
    XMLElement *pLog;
    XMLElement *pMapFileName;
    XMLElement *pSummary;
    XMLNode *pPath;  // here map with drawn path;
    XMLNode *pLowLevel;
    XMLNode *pHighLevel;
public:
    int saveData(std::string nameIn, const Output &output, const Map &task);
    int write(std::string nameOut);
private:
    int saveMap(const std::vector<Node> &path, const Map &map);

    int savePath(const std::vector<Node> &path, const std::vector<double> &weightMovements);
    int initPath(unsigned ux, unsigned uy, unsigned number);
    int addNode(unsigned toX, unsigned toY, unsigned number);

    int savePathHigh(const std::vector<Node> &path, const std::vector<double> &weightMovements);
    int initPathHigh(unsigned ux, unsigned uy, unsigned number);
    int addNodeHigh(unsigned toX, unsigned toY, TypeValue length, unsigned number);

};

#endif //REPO_MYLOG_H

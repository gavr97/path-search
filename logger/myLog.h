//
// Created by alexgavr on 11.01.17.
//

#ifndef REPO_MYLOG_H
#define REPO_MYLOG_H

#include <vector>
#include <string>
#include "../tinyxml/tinyxml2.h"
#include "../global/globalTypes.h"
#include "../global/globalVars.h"
#include "../dataCode/myTask.h"
#include "../dataCode/myOutput.h"



using namespace tinyxml2;


class Log {
private:
    unsigned rememberedX;
    unsigned rememberedY;
    XMLNode *pLowLevel;
    XMLNode *pHighLevel;
    XMLElement *pMapFileName;
    XMLElement *pSummary;
public:
    XMLDocument xmlDoc;
    int saveData(const Output &output);
    int write(const char *fileName);
private:
    int savePath(const std::vector<Node> &path, const std::vector<double> &weightMovements);
    int finishSaving();
    int initPath(unsigned ux, unsigned uy, unsigned number);
    int addNode(unsigned toX, unsigned toY, TypeValue length, unsigned number);
};

#endif //REPO_MYLOG_H

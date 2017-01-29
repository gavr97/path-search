//
// Created by alexgavr on 11.01.17.
//

#ifndef REPO_MYLOG_H
#define REPO_MYLOG_H

#include <vector>
#include <string>
#include "myTask.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class Log {
public:
    XMLDocument xmlDoc;
    XMLNode *plowLevelRoot;
    XMLNode *phighLevelRoot;

    int addNode(unsigned ux, unsigned uy);
};



#endif //REPO_MYLOG_H

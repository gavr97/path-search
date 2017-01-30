//
// Created by alexgavr on 11.01.17.
//

#ifndef REPO_MYLOG_H
#define REPO_MYLOG_H

#include <vector>
#include <string>
#include "myTask.h"
#include "tinyxml2.h"
#include "constantTypes.h"
//#include "tagNames.h"

using namespace tinyxml2;


class Log {
private:
    unsigned rememberedX;
    unsigned rememberedY;
    XMLNode *pLowLevel;
    XMLNode *pHighLevel;

public:
    // summary numberofsteps="33708" nodescreated="34731" length="382.99" time="0.13"/>
    XMLDocument xmlDoc;
    int finish();
    unsigned numberOfSteps;
    //nodesCreated???
    //time???
    unsigned length;
    int initPath(unsigned ux, unsigned uy, unsigned number);
    int addNode(unsigned ux, unsigned uy, TypeValue length, unsigned number);
};

#endif //REPO_MYLOG_H

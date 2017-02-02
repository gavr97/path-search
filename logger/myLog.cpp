//
// Created by alexgavr on 11.01.17.
//

#include "../dataCode/myTask.h"
#include "../logger/myLog.h"
#include "../dataCode/myOutput.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("TinyXML Error: %i\n", a_eResult); return a_eResult; }
#endif

int Log::initPath(unsigned startX, unsigned startY, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed transposing and shift -1 is required
    std::swap(startX, startY);
    --startX, --startY;

    pLowLevel = xmlDoc.NewElement("lplevel");
    pHighLevel = xmlDoc.NewElement("hplevel");
    XMLElement *pElement = xmlDoc.NewElement("node");
    pElement->SetAttribute("x", startX);
    pElement->SetAttribute("y", startY);
    pElement->SetAttribute("number", number);
    pLowLevel->InsertEndChild(pElement);

    rememberedX = startX;
    rememberedY = startY;
    return 0;
}

int Log::addNode(unsigned toX, unsigned toY, TypeValue weightMovement, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed transposing and shift -1 is required
    std::swap(toX, toY);
    --toX, --toY;

    XMLElement *pElement = xmlDoc.NewElement("node");
    pElement->SetAttribute("x", toX);
    pElement->SetAttribute("y", toY);
    pElement->SetAttribute("number", number);
    pLowLevel->InsertEndChild(pElement);

    pElement = xmlDoc.NewElement("section");
    pElement->SetAttribute("number", number - 1);  // CHANGE. -1 because pHighLevel has less nodes by 1
    pElement->SetAttribute("start.x", rememberedX);
    pElement->SetAttribute("start.y", rememberedY);
    pElement->SetAttribute("finish.x", toX);
    pElement->SetAttribute("finish.y", toY);
    pElement->SetAttribute("length", weightMovement);
    pHighLevel->InsertEndChild(pElement);

    rememberedX = toX;
    rememberedY = toY;
    return 0;
}

int Log::savePath(const std::vector<Node> &path, const std::vector<double> &weightMovements)
{
    // remeber that vectors path and weightMovements are reversed
    // size of weightMovements is lower by 1;
    int ind = path.size() - 1;
    this->initPath(path[ind].x, path[ind].y, 0);
    for (ind = path.size() - 2; ind >= 0; --ind) {
        unsigned number = path.size() - ind - 1;
        this->addNode(path[ind].x, path[ind].y, weightMovements[ind], number);
    }
    return 0;
}

int Log::saveData(const Output &output, const char *nameIn) {
    pLog = xmlDoc.NewElement("log");
    pMapFileName = xmlDoc.NewElement("mapfilename");
    pMapFileName->SetText(nameIn);
    pLog->InsertFirstChild(pMapFileName);
    pSummary = xmlDoc.NewElement("summary");
    pSummary->SetAttribute("numberofsteps", output.numberOfSteps);
    pSummary->SetAttribute("nodescreated", output.numberOfNodesCreated);
    pSummary->SetAttribute("length", output.numberOfMovements);
    pSummary->SetAttribute("time", "?");
    pLog->InsertEndChild(pSummary);

    // map with drawn path willbe accessable via pPath - Log's member
    //this->saveMap;
    //pLog->InsertEndChild(pPath);

    // consequence of nodes will be accessable via pHighLevel and pLowLevel - Log's members
    if (this->savePath(output.path, output.weightMovements)) return 1;
    pLog->InsertEndChild(pLowLevel);
    pLog->InsertEndChild(pHighLevel);
    XMLNode *pRoot = xmlDoc.FirstChild();
    pRoot->InsertEndChild(pLog);
    return 0;
}

int Log::write(const char *nameOut)
{
    XMLError eResult = xmlDoc.SaveFile(nameOut);
    if (eResult == XML_SUCCESS) {
        printf("Success during saving XML\n");
        return 0;
    } else {
        printf("not! success during saving XML\n");
        return 1;
    }
}

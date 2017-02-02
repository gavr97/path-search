//
// Created by alexgavr on 11.01.17.
//

#include "../dataCode/myTask.h"
#include "../logger/myLog.h"
#include "../dataCode/myOutput.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("TinyXML Error: %i\n", a_eResult); return a_eResult; }
#endif

int Log::initPath(unsigned finishX, unsigned finishY, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed transposing and shift -1 is required
    std::swap(finishX, finishY);
    --finishX, --finishY;

    pLowLevel = xmlDoc.NewElement("lplevel");
    pHighLevel = xmlDoc.NewElement("hplevel");
    XMLElement *pElement = xmlDoc.NewElement("node");
    pElement->SetAttribute("x", finishX);
    pElement->SetAttribute("y", finishY);
    pElement->SetAttribute("number", number);
    pLowLevel->InsertFirstChild(pElement);

    rememberedX = finishX;
    rememberedY = finishY;
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
    pElement->SetAttribute("number", number);
    pElement->SetAttribute("start.x", rememberedX);
    pElement->SetAttribute("start.y", rememberedY);
    pElement->SetAttribute("finish.x", toX);
    pElement->SetAttribute("finish.y", toY);
    pElement->SetAttribute("length", weightMovement);
    pHighLevel->InsertFirstChild(pElement);

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
        unsigned number = path.size() - ind + 1;
        this->addNode(path[ind].x, path[ind].y, weightMovements[ind], number);
    }
    return 0;
}

int Log::saveData(const Output &output) {
    pSummary = xmlDoc.NewElement("summary");
    pSummary->SetAttribute("numberofsteps", output.numberOfSteps);
    pSummary->SetAttribute("nodescreated", output.numberOfNodesCreated);
    pSummary->SetAttribute("length", output.numberOfMovements);
    pSummary->SetAttribute("time", "?");
    // path will be accessable via pHighLevel and pLowLevel - Log's members
    if (this->savePath(output.path, output.weightMovements)) return 1;
    return 0;
}

int Log::finishSaving()
{
    XMLNode *pRoot = xmlDoc.FirstChild();
    XMLElement *pLog = xmlDoc.NewElement("log");
    //pMapFileName = xmlDoc.NewElement("mapfilename");
    //pMapFileName->SetText("./Log.xml");
    pLog->InsertEndChild(pMapFileName);
    pLog->InsertEndChild(pSummary);

    XMLElement *pPath = xmlDoc.NewElement("path");
    // insert here table with indexed rows
    pLog->InsertEndChild(pPath);
    pLog->InsertEndChild(pLowLevel);
    pLog->InsertEndChild(pHighLevel);
    pRoot->InsertEndChild(pLog);
    XMLError eResult = xmlDoc.SaveFile("Log.xml");
    if (eResult == XML_SUCCESS)
        printf("Success during saving XML\n");
    else
        printf("not! success during saving XML\n");
    return 0;
}

int Log::write(const char *fileName)
{

    return 0;
}

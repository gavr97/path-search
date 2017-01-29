//
// Created by alexgavr on 11.01.17.
//

#include "myTask.h"
#include "myLog.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("TinyXML Error: %i\n", a_eResult); return a_eResult; }
#endif

int Log::initPath(unsigned finishX, unsigned finishY, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed shift -1 is required
    std::swap(finishX, finishY);
    --finishX, --finishY;

    XMLNode *pRoot = xmlDoc.FirstChild();
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

int Log::addNode(unsigned fromX, unsigned fromY, TypeValue length, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed shift -1 is required
    std::swap(fromX, fromY);
    --fromX, --fromY;
    XMLElement *pElement = xmlDoc.NewElement("node");
    pElement->SetAttribute("x", fromX);
    pElement->SetAttribute("y", fromY);
    pElement->SetAttribute("number", number);
    pLowLevel->InsertFirstChild(pElement);

    pElement = xmlDoc.NewElement("section");
    pElement->SetAttribute("number", number);
    pElement->SetAttribute("start.x", fromX);
    pElement->SetAttribute("start.y", fromY);
    pElement->SetAttribute("finish.x", rememberedX);
    pElement->SetAttribute("finish.y", rememberedY);
    pElement->SetAttribute("length", length);
    pHighLevel->InsertFirstChild(pElement);

    rememberedX = fromX;
    rememberedY = fromY;
    return 0;
}

int Log::finish()
{
    XMLNode *pRoot = xmlDoc.FirstChild();
    XMLElement *pLog = xmlDoc.NewElement("log");
    XMLElement *pMapFileName = xmlDoc.NewElement("mapfilename");
    pMapFileName->SetText("./Log.xml");
    pLog->InsertEndChild(pMapFileName);

    XMLElement *pSummary = xmlDoc.NewElement("summary");
    pSummary->SetAttribute("numberofsteps", numberOfSteps);
    pSummary->SetAttribute("nodescreated", "?");
    pSummary->SetAttribute("length", length);
    pSummary->SetAttribute("time", "?");
    pLog->InsertEndChild(pSummary);

    XMLElement *pPath = xmlDoc.NewElement("path");
    // insert here table with indexed rows

    pLog->InsertEndChild(pPath);
    pLog->InsertEndChild(pLowLevel);
    pLog->InsertEndChild(pHighLevel);
    pRoot->InsertEndChild(pLog);
    XMLError eResult = xmlDoc.SaveFile("Log.xml");
    if (eResult == XML_SUCCESS)
        printf("Success\n");
    else
        printf("not! success\n");
    return 0;
}
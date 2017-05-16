#include <iostream>
#include "log.h"

void const printMap(const Grid &grid)
{
    std::cout << "\nMAP with drawn path\n";
    for (const auto &row : grid) {
        for (const auto &elem : row)
            std::cout << elem;
        std::cout << std::endl;
    }
}

int Log::initPath(unsigned startX, unsigned startY, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed transposing and shift -1 is required
    std::swap(startX, startY);
    --startX, --startY;

    pLowLevel = xmlDoc.NewElement("lplevel");
    XMLElement *pElement = xmlDoc.NewElement("node");
    pElement->SetAttribute("x", startX);
    pElement->SetAttribute("y", startY);
    pElement->SetAttribute("number", number);
    pLowLevel->InsertEndChild(pElement);
    return 0;
}

int Log::addNode(unsigned toX, unsigned toY, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed transposing and shift -1 is required
    std::swap(toX, toY);
    --toX, --toY;
    XMLElement *pElement = xmlDoc.NewElement("node");

    pElement->SetAttribute("x", toX);
    pElement->SetAttribute("y", toY);
    pElement->SetAttribute("number", number);
    pLowLevel->InsertEndChild(pElement);
    return 0;
}

int Log::savePath(const std::vector<Node> &path, const std::vector<double> &weightMovements)
{
    // remeber that vectors path and weightMovements are reversed
    // size of weightMovements is lower by 1;
    int ind = path.size() - 1;
    this->initPath(path[ind].getX(), path[ind].getY(), 0);
    for (ind = path.size() - 2; ind >= 0; --ind) {
        unsigned number = path.size() - ind - 1;
        this->addNode(path[ind].getX(), path[ind].getY(), number);
    }
    return 0;
}

int Log::initPathHigh(unsigned startX, unsigned startY, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed transposing and shift -1 is required
    std::swap(startX, startY);
    --startX, --startY;

    pHighLevel = xmlDoc.NewElement("hplevel");
    XMLElement *pElement = xmlDoc.NewElement("node");
    rememberedX = startX;
    rememberedY = startY;
    return 0;
}

int Log::addNodeHigh(unsigned toX, unsigned toY, TypeValue weightMovement, unsigned number)
{
    // REMEMBER about transposing map and shift +1; so inversed transposing and shift -1 is required
    std::swap(toX, toY);
    --toX, --toY;

    XMLElement *pElement = xmlDoc.NewElement("section");
    pElement->SetAttribute("number", number);  // CHANGE. -1 because pHighLevel has less nodes by 1
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

int Log::savePathHigh(const std::vector<Node> &path, const std::vector<double> &weightMovements)
{
    // remeber that vectors path and weightMovements are reversed
    // size of weightMovements is lower by 1;
    int ind = path.size() - 1;
    this->initPathHigh(path[ind].getX(), path[ind].getY(), 0);
    for (ind = path.size() - 2; ind >= 0; --ind) {
        unsigned number = path.size() - ind - 1;
        this->addNodeHigh(path[ind].getX(), path[ind].getY(), weightMovements[ind], number);
    }
    return 0;
}

int Log::saveMap(const std::vector<Node> &path, const Map &map)
{
    Grid gridRes = map.grid;
    for (const auto &node : path) {
        unsigned x = node.getX();
        unsigned y = node.getY();
        // at the moment coordinates are considered to be as inside representation(not graphical system)
        gridRes[x][y] = '*';
    }

    unsigned bufSize = gridRes[0].size() * 3 + 1;
    pPath = xmlDoc.NewElement("path");
    for (unsigned indRow = 1; indRow != gridRes.size() - 1; ++indRow) {
        XMLElement *cell = xmlDoc.NewElement("row");
        cell->SetAttribute("number", indRow - 1);
        char str[bufSize];
        unsigned indStr = 0;
        for (unsigned indCol = 1; indCol != gridRes[0].size() - 1; ++indCol) {
            str[indStr] = gridRes[indRow][indCol];
            str[indStr + 1] = ' ';
            indStr += 2;
        }
        str[indStr] = '\0';
        cell->SetText(str);
        pPath->InsertEndChild(cell);
    }
    return 0;
}

int Log::saveData(const char *nameIn, const Output &output, const Map &map) {
    xmlDoc.LoadFile(nameIn);
    pLog = xmlDoc.NewElement("log");
    pMapFileName = xmlDoc.NewElement("mapfilename");
    pMapFileName->SetText(nameIn);
    pLog->InsertFirstChild(pMapFileName);
    pSummary = xmlDoc.NewElement("summary");
    pSummary->SetAttribute("numberofsteps", output.numberOfSteps);
    pSummary->SetAttribute("nodescreated", output.numberOfNodesCreated);
    pSummary->SetAttribute("length", output.lengtnPath);
    pSummary->SetAttribute("time", output.time);
    pLog->InsertEndChild(pSummary);
    // map with drawn path will be accessible via pPath - Log's member
    if (output.isLowLevel) {
        this->saveMap(output.path, map);
    } else {
        this->saveMap(output.otherPath, map);
    }
    pLog->InsertEndChild(pPath);
    if (output.path.size() != 0) {  // if there is found path
        // consequence of nodes will be accessible via pHighLevel and pLowLevel - Log's members
        if (output.isLowLevel) {
            if (this->savePath(output.path, output.weightMovements)) return 1;
            if (this->savePathHigh(output.otherPath, output.otherWeightMovements)) return 1;
        } else {
            if (this->savePathHigh(output.path, output.weightMovements)) return 1;
            if (this->savePath(output.otherPath, output.otherWeightMovements)) return 1;
        }
        pLog->InsertEndChild(pLowLevel);
        pLog->InsertEndChild(pHighLevel);
    }

    XMLNode *pRoot = xmlDoc.FirstChildElement("root");
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
        printf("failure during saving XML\n");
        printf("possibly incorrecnt path to file\n");
        return 1;
    }
}

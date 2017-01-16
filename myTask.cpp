//
// Created by alexgavr on 07.01.17.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "tinyxml2.h"
#include "myTask.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("TinyXML Error: %i\n", a_eResult); return a_eResult; }
#endif
#ifndef MYCheckResult
#define MYCheckResult(eResult) if (eResult != 0) {printf("MY Error: %i\n", eResult); return eResult; }
#endif

using namespace tinyxml2;


static double CELLSIZE_DEFAULT = 1;
static double LINE_COST_DEFAULT = 1;
static double DIAG_COST_DEFAULT = 1.414;
static unsigned int STARTX_DEFAULT = 0;
static unsigned int STARTY_DEFAULT = 0;
static unsigned int FINISHX_DEFAULT = 0;
static unsigned int FINISHY_DEFAULT = 0;
static const std::string SEARCH_TYPE_DEFAULT = "astar";
static const std::string METRIC_TYPE_DEFAULT = "euclid";
static unsigned int ALLOW_DIAG_DEFAULT = 0;
static unsigned int ALLOW_SQUEEZE_DEFAULT = 0;
static unsigned int CUT_CORNERS_DEFAULT = 0;

bool isValidSizes(Task task)
{
    bool positive1 = (task.cntRealCols > 0 && task.cntRealRows > 0);
    bool positive2 = (task.finishY > 0 && task.finishX > 0 && task.startX > 0 && task.startY > 0);
    return positive1 && positive2 &&
           task.startX <= task.cntRealRows && task.startY <= task.cntRealCols &&
           task.finishX <= task.cntRealRows && task.finishY <= task.cntRealCols;
}

int Task::readInt(XMLNode *pRoot, const char *tag, unsigned int &destination, unsigned int DEFAULT = 0, bool obligatory = 0)  // code of error is returned
{
    XMLError eResult;
    XMLElement * pElement = pRoot->FirstChildElement(tag);
    if (pElement == nullptr) {
        if (obligatory) {
            std::cout << "error: obligatory tag " << tag << " is not found\n";
            exit(1);
        } else {
            destination = DEFAULT;
            std::cout << tag << " is assigned by default " << DEFAULT << "\n";
            return 0;
        }
    } else {
        eResult = pElement->QueryUnsignedText(&destination);
        if (eResult != XML_SUCCESS) {
            std::cout << "error: format of " << tag << " is incorrect\n";
            exit(1);
        }
        //std::cout << tag << " is saved correctly\n";
    }
    return 0;
}

int Task::readDouble(XMLNode *pRoot, const char *tag, double &destination, double DEFAULT = 0, bool obligatory = 0)  // code of error is returned
{
    XMLError eResult;
    XMLElement * pElement = pRoot->FirstChildElement(tag);
    if (pElement == nullptr) {
        if (obligatory) {
            std::cout << "error: obligatory tag " << tag << " is not found\n";
            exit(1);
        } else {
            destination = DEFAULT;
            std::cout << tag << " is assigned by default " << DEFAULT << "\n";
            return 0;
        }
    } else {
        eResult = pElement->QueryDoubleText(&destination);
        if (eResult != XML_SUCCESS) {
            std::cout << "error: format of " << tag << " is incorrect\n";
            exit(1);
        }
        //std::cout << tag << " is saved correctly\n";
    }
    return 0;
}

int Task::readStr(XMLNode *pRoot, const char *tag, std::string &destination, const std::string DEFAULT = 0,
            bool obligatory = 0)  // code of error is returned
{
    XMLError eResult;
    XMLElement * pElement = pRoot->FirstChildElement(tag);
    if (pElement == nullptr) {
        if (obligatory) {
            std::cout << "error: obligatory tag " << tag << " is not found\n";
            exit(1);
        } else {
            destination = DEFAULT;
            std::cout << tag << " is assigned by default " << DEFAULT << "\n";
            return 0;
        }
    } else {
        if (pElement->GetText() == nullptr) {
            std::cout << "error: empty " << tag << std::endl;
            exit(1);
        }
        destination = pElement->GetText();
    }
    return 0;
}

int Task::readMap(XMLNode * pRoot, std::vector<std::vector<bool>> &map)
{
    int height = map.size() - 2;  // h = size - 2 because there is extra rows and cols for boundary
    int width = map[0].size() - 2;
    int indRow = 0;
    int indCol = 0;

    //_____init boundaries______
    for (indRow : std::vector<int> {0, height + 1})
        for (indCol = 0; indCol <= width + 1; ++indCol)
            map[indRow][indCol] = 1;
    std::cout << "boundaries are inited\n";

    //_____init grid____________
    XMLElement *pGrid = pRoot->FirstChildElement("grid");
    if (pGrid == nullptr) {
        std:: cout << "error: incorrect structure of XML file: failure during finding tag grid\n";
        exit(1);
    }
    XMLElement *pRow = pGrid->FirstChildElement();

    indCol = 1;
    while (pRow != nullptr) {
        if (indCol == width + 1) {
            std::cout << "warning: too many rows in physical XML\n";
            break;
        }
        const char *buf = pRow->GetText();
        map[0][indCol] = 1;
        map[height + 1][indCol] = 1;
        indRow = 1;
        while (*buf) {
            if (*buf == '0') {
                if (indRow == height + 1) {
                    std::cout << "warning: too many cells in row in physical XML\n";
                    break;
                }
                map[indRow][indCol] = 0;
                ++indRow;
            } else if (*buf == '1') {
                if (indRow == height + 1) {
                    std::cout << "warning: too many cells in row in physical XML\n";
                    break;
                }
                map[indRow][indCol] = 1;
                ++indRow;
            }
            ++buf;
        }
        if (indRow < height + 1) {
            std::cout << "error: too few cells in row in physical XML" << indCol << "\n";
            exit(1);
            //return 1;
        }
        pRow = pRow->NextSiblingElement("row");
        ++indCol;
    }
    if (indCol < width + 1) {
        std::cout << "error: too few rows in physical XML\n";
        exit(1);
        //return 1;
    }
    return 0;
}

int Task::myLoad(const char *path)
{
    // ____load xml tree____
    XMLError eResult;
    int myeResult;
    XMLDocument xmlDoc;
    eResult = xmlDoc.LoadFile(path);
    if (eResult != XML_SUCCESS) {
        std::cout << "error: incorrect xml file\n";
        exit(1);
    }
    XMLNode *pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr){
        std::cout << "error: empty xml file\n";
        exit(1);
    }
    std::cout << "XML has been read\n";

    // _______init dimensions of map and other information________
    if (pRoot->FirstChildElement("map") == nullptr) {
        std::cout << "error: incorrect structure of xml file: trere is no tag map\n";
        exit(1);
    }
    if (pRoot->FirstChildElement("algorithm") == nullptr) {
        std::cout << "error: incorrect structure of xml file: trere is no tag algorithm\n";
        exit(1);
    }
    myeResult = readInt(pRoot->FirstChildElement("map"), "height", this->cntRealRows, 0, 1);  // 0 is incidential; 1 means obligatory
    myeResult = readInt(pRoot->FirstChildElement("map"), "width", this->cntRealCols, 0, 1);
    myeResult = readInt(pRoot->FirstChildElement("map"), "startx", this->startX, STARTX_DEFAULT);
    myeResult = readInt(pRoot->FirstChildElement("map"), "starty", this->startY, STARTY_DEFAULT);
    myeResult = readInt(pRoot->FirstChildElement("map"), "finishx", this->finishX, FINISHX_DEFAULT);
    myeResult = readInt(pRoot->FirstChildElement("map"), "finishy", this->finishY, FINISHY_DEFAULT);
    ++startX;  // because it is comfortable for numerating real rows and cols from 1 (0 for abstract bound)
    ++startY;
    ++finishX;
    ++finishY;
    unsigned tmp = this->cntRealCols;  // because we store transposed matrix
    this->cntRealCols = cntRealRows;
    this->cntRealRows = tmp;

    if (!isValidSizes(*this)) {
        std::cout << "error: start or finish are inappropriate for these sizes\n";
        exit(1);
    }
    myeResult = readDouble(pRoot->FirstChildElement("algorithm"), "linecost", lineCost, LINE_COST_DEFAULT);
    myeResult = readDouble(pRoot->FirstChildElement("algorithm"), "diagonalcost", this->diagCost, DIAG_COST_DEFAULT);
    myeResult = readStr(pRoot->FirstChildElement("algorithm"), "searchtype", this->searchType, SEARCH_TYPE_DEFAULT);
    myeResult = readStr(pRoot->FirstChildElement("algorithm"), "metrictype", this->metricType, METRIC_TYPE_DEFAULT);

    myeResult = readInt(pRoot->FirstChildElement("algorithm"), "allowdiagonal", this->allowDiag, ALLOW_DIAG_DEFAULT);
    myeResult = readInt(pRoot->FirstChildElement("algorithm"), "allowsqueeze", this->allowSqueeze, ALLOW_SQUEEZE_DEFAULT);
    myeResult = readInt(pRoot->FirstChildElement("algorithm"), "cutcorners", this->cutCorners, CUT_CORNERS_DEFAULT);
    std::cout << "task has been read succesfully\n";

    // _______read map___________
    unsigned int height = this->cntRealRows;
    unsigned int width = this->cntRealCols;
    std::vector<std::vector<bool>> map(height + 2, std::vector<bool>(width + 2));
    this->map = map;
    myeResult = readMap(pRoot->FirstChildElement("map"), this->map);
    std::cout << "map has been read successfully\n";
    return 0;
}

void Task::print() const
{
    std::cout << "\nTask:\n";
    std::cout << "size: " << this->cntRealRows << ' ' << this->cntRealCols << std::endl;
    //std::cout << "map\n";
    //for (const auto &row : this->map) {
    //    for (const auto &elem : row) {
    //        std::cout << elem << ' ';
    //    }
    //    std::cout << std::endl;
    //}
    std::cout << "allow diag " << this->allowDiag << "\n";
    std::cout << "costs of movements: " << this->lineCost << " and " << this->diagCost << std::endl;
    printf("start and end: %u %u and %u %u\n", this->startX, this->startY, this->finishX, this->finishY);
    std::cout << "search type and metric type: " << this->searchType << " and " << this->metricType << std::endl;
    std::cout << "about movements: " << this->allowDiag << ' ' << this->allowSqueeze << ' ' << this->cutCorners << std::endl;
}


//
// Created by alexgavr on 07.01.17.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "../tinyxml/tinyxml2.h"
#include "../dataCode/myTask.h"
#include "../logger/myLog.h"
#include "../global/globalVars.h"

using namespace tinyxml2;

bool isValidSizes(const Task &task)
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
            return 1;  // exit(1);
        } else {
            destination = DEFAULT;
            std::cout << tag << " is assigned by default " << DEFAULT << "\n";
            return 0;
        }
    } else {
        eResult = pElement->QueryUnsignedText(&destination);
        if (eResult != XML_SUCCESS) {
            std::cout << "error: format of " << tag << " is incorrect\n";
            return 1;  // exit(1);
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
            return 1;  // exit(1);
        } else {
            destination = DEFAULT;
            std::cout << tag << " is assigned by default " << DEFAULT << "\n";
            return 0;
        }
    } else {
        eResult = pElement->QueryDoubleText(&destination);
        if (eResult != XML_SUCCESS) {
            std::cout << "error: format of " << tag << " is incorrect\n";
            return 1;  // exit(1);
        }
        //std::cout << tag << " is saved correctly\n";
    }
    return 0;
}

int Task::readStr(XMLNode *pRoot, const char *tag, std::string &destination, const std::string DEFAULT = 0, bool obligatory = 0)  // code of error is returned
{
    XMLError eResult;
    XMLElement * pElement = pRoot->FirstChildElement(tag);
    if (pElement == nullptr) {
        if (obligatory) {
            std::cout << "error: obligatory tag " << tag << " is not found\n";
            return 1;  // exit(1);
        } else {
            destination = DEFAULT;
            std::cout << tag << " is assigned by default " << DEFAULT << "\n";
            return 0;
        }
    } else {
        if (pElement->GetText() == nullptr) {
            std::cout << "error: empty " << tag << std::endl;
            return 1;  // exit(1);
        }
        destination = pElement->GetText();
    }
    return 0;
}

int Task::readMap(XMLNode * pGrid, Map &map)
{
    int height = map.size() - 2;  // h = size - 2 because there is extra rows and cols for boundary
    int width = map[0].size() - 2;
    int indRow = 0;
    int indCol = 0;

    //_____init boundaries______
    for (indCol = 0; indCol <= width + 1; ++indCol)
        map[0][indCol] = '1';
    indRow = height + 1;
    for (indCol = 0; indCol <= width + 1; ++indCol)
        map[height + 1][indCol] = OBSTACLE;
    std::cout << "boundaries are inited\n";

    //______read map_______
    XMLElement *pRow = pGrid->FirstChildElement();
    indRow = 1;
    while (pRow != nullptr) {
        if (indRow == height + 1) {
            std::cout << "warning: too many rows\n";
            break;
        }
        const char *buf = pRow->GetText();
        map[indRow][0] = OBSTACLE;
        map[indRow][width + 1] = OBSTACLE;
        indCol = 1;
        while (*buf) {
            if (*buf == NO_OBSTACLE) {
                if (indCol == width + 1) {
                    std::cout << "warning: too many cells in row\n";
                    break;
                }
                map[indRow][indCol] = NO_OBSTACLE;
                ++indCol;
            } else if (*buf == OBSTACLE) {
                if (indCol == width + 1) {
                    std::cout << "warning: too many cells in row\n";
                    break;
                }
                map[indRow][indCol] = OBSTACLE;
                ++indCol;
            }
            ++buf;
        }
        if (indCol < width + 1) {
            std::cout << "error: too few cells in row " << indRow << "\n";
            return 1;
        }
        pRow = pRow->NextSiblingElement("row");
        ++indRow;
    }
    if (indRow < height + 1) {
        std::cout << "error: too few rows\n";
        return 1;
    }
    return 0;
}

int Task::myLoad(const char *nameIn)
{
    // ____load xml tree____
    XMLDocument xmlDoc;
    XMLError eResult;
    int myeResult;
    eResult = xmlDoc.LoadFile(nameIn);
    if (eResult != XML_SUCCESS) {
        std::cout << "error: incorrect xml file\n";
        return 1;
        //exit(1);
    }
    XMLNode *pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr){
        std::cout << "error: empty xml file\n";
        return 1;
        //exit(1);
    }
    std::cout << "XML has been read\n";

    // _______check obligatory tags________
    XMLNode *pMap = pRoot->FirstChildElement(TAG_MAP);
    if (pMap == nullptr) {
        std::cout << "error: incorrect structure of xml file: trere is no tag map\n";
        return 1;
        // exit(1);
    }
    XMLNode *pGrid = pMap->FirstChildElement(TAG_GRID);
    if (pGrid == nullptr) {
        std::cout << "error: incorrect structure of xml file: trere is no tag grid in subtree map\n";
        return 1;
    }
    XMLNode *pAlgorithm = pRoot->FirstChildElement(TAG_ALGORITHM);
    if (pAlgorithm == nullptr) {
        std::cout << "error: incorrect structure of xml file: trere is no tag algorithm\n";
        return 1;
        // exit(1);
    }
    // two last arguments: default_value AND whether obligatory or not
    if(readInt(pMap, TAG_HEIGHT, this->cntRealRows, 0, 1)) return 1;
    if(readInt(pMap, TAG_WIDTH, this->cntRealCols, 0, 1)) return 1;
    if(readInt(pMap, TAG_STARTX, this->startX, STARTX_DEFAULT)) return 1;
    if(readInt(pMap, TAG_STARTY, this->startY, STARTY_DEFAULT)) return 1;
    if(readInt(pMap, TAG__FINISHX, this->finishX, FINISHX_DEFAULT)) return 1;
    if(readInt(pMap, TAG_FINISHY, this->finishY, FINISHY_DEFAULT)) return 1;
    ++startX;  // because it is comfortable for numerating real rows and cols from 1 (0 for abstract bound)
    ++startY;
    ++finishX;
    ++finishY;

    unsigned temp = startX;  // cause in programm it is easier to consider x as the first coordinate of node(ind of row)
    startX = startY;  // and y as the second. But input has graphical system coordinates
    startY = temp;
    temp = finishX;
    finishX = finishY;
    finishY = temp;

    if (!isValidSizes(*this)) {
        std::cout << "error: start or finish are inappropriate for these sizes\n";
        return 1;
        // exit(1);
    }
    if(readDouble(pAlgorithm, TAG_LINECOST, lineCost, LINE_COST_DEFAULT)) return 1;
    if(readDouble(pAlgorithm, TAG_DIAGONALCONST, this->diagCost, DIAG_COST_DEFAULT)) return 1;
    if(readStr(pAlgorithm, TAG_SEARCHTYPE, this->searchType, SEARCH_TYPE_DEFAULT)) return 1;
    if(readStr(pAlgorithm, TAG_METRICTYPE, this->metricType, METRIC_TYPE_DEFAULT)) return 1;

    if(readInt(pAlgorithm, TAG_ALLOWDIAGONAL, this->allowDiag, ALLOW_DIAG_DEFAULT)) return 1;
    if(readInt(pAlgorithm, TAG_ALLOWSQUEEZE, this->allowSqueeze, ALLOW_SQUEEZE_DEFAULT)) return 1;
    if(readInt(pAlgorithm, TAG_CUTCORNERS, this->cutCorners, CUT_CORNERS_DEFAULT)) return 1;
    this->allowDiag = 1;  // TODO разобраться с allowdiag, allowsqueeze and cuncorners
    this->allowSqueeze = 1;
    this->cutCorners = 1;
    std::cout << "specific information about task has been read succesfully\n";

    // _______read map___________
    Map map(this->cntRealRows + 2, MapRow(this->cntRealCols + 2));
    this->map = map;
    if(readMap(pGrid, this->map)) return 1;
    std::cout << "map has been read successfully\n" << std::endl;
    return 0;
}

void Task::print() const
{
    std::cout << "Task:\n";
    std::cout << "size: " << this->cntRealRows << ' ' << this->cntRealCols << std::endl;
    //std::cout << "map\n";
    //for (const auto &row : this->map) {
        //for (const auto &elem : row) {
            //std::cout << elem << ' ';
        //}
        //std::cout << std::endl;
    //}
    std::cout << "allow diag " << this->allowDiag << "\n";
    std::cout << "costs of movements: " << this->lineCost << " and " << this->diagCost << std::endl;
    // do not forget about transposing and shift
    printf("start and end: %u %u and %u %u\n", this->startY - 1, this->startX - 1, this->finishY - 1, this->finishX - 1);
    std::cout << "search type and metric type: " << this->searchType << " and " << this->metricType << std::endl;
    std::cout << "about movements: " << "allow diagonal, allow squeeze, cut corners: "
              << this->allowDiag << " " << this->allowSqueeze << ' ' << this->cutCorners << std::endl;
    std::cout << std::endl;
}


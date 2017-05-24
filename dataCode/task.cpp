#include <iostream>
#include "task.h"

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

int Task::myLoad(std::string nameIn)
{
    //_____ define outName_____
    std::string str = nameIn;
    size_t found = str.find_last_of(".");
    if (found != std::string::npos)
        str.insert(found, "_log");
    else
        str.append("_log");
    nameOut = str;

    // ____load xml tree____
    XMLDocument xmlDoc;
    XMLError eResult;
    int myeResult;
    eResult = xmlDoc.LoadFile(nameIn.c_str());
    if (eResult != XML_SUCCESS) {
        std::cout << "error: incorrect xml file\n";
        return 1;
        //exit(1);
    }
    XMLNode *pRoot = xmlDoc.FirstChildElement("root");
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
    if (cntRealCols > 1000000 || cntRealRows > 1000000) {
        std::cout << "error: height and width of map are too big\n";
        return 1;
    }
    if(readInt(pMap, TAG_STARTX, this->startX, STARTX_DEFAULT)) return 1;
    if(readInt(pMap, TAG_STARTY, this->startY, STARTY_DEFAULT)) return 1;
    if(readInt(pMap, TAG_FINISHX, this->finishX, FINISHX_DEFAULT)) return 1;
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
    if(readDouble(pMap, TAG_CELLSIZE, this->cellSize, CELLSIZE_DEFAULT)) return 1;
    if(readDouble(pAlgorithm, TAG_H_WEIGHT, hWeight, H_WEIGHT_DEFAULT)) return 1;
    if(readDouble(pAlgorithm, TAG_LINECOST, lineCost, LINE_COST_DEFAULT)) return 1;
    if(readDouble(pAlgorithm, TAG_DIAGONALCONST, this->diagCost, DIAG_COST_DEFAULT)) return 1;
    if(readStr(pAlgorithm, TAG_SEARCHTYPE, this->searchType, SEARCH_TYPE_DEFAULT)) return 1;
    if(readStr(pAlgorithm, TAG_METRICTYPE, this->metricType, METRIC_TYPE_DEFAULT)) return 1;
    if (this->searchType != ASTAR && this->searchType != THETA && this->searchType != JPS) {
        std::cout << "error: incorrect search type\n";
        return 1;
    }
    
    //grid, allowDiag,.., cutcorners are not read here. it is in map.read()
    return 0;
}

void Task::print() const
{
    std::cout << "Task:\n";
    std::cout << "size: " << this->cntRealRows << ' ' << this->cntRealCols << std::endl;
    std::cout << "costs of movements: " << this->lineCost << " and " << this->diagCost << std::endl;
    std::cout << "cell size: " << this->cellSize << std::endl;
    // do not forget about transposing and shift
    printf("start and end: %u %u and %u %u\n", this->startY - 1, this->startX - 1, this->finishY - 1, this->finishX - 1);
    std::cout << "search type and metric type: " << this->searchType << " and " << this->metricType << std::endl;
    std::cout << "out filename:" << nameOut << std::endl;
    std::cout << std::endl;
}

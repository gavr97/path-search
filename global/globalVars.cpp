//
// Created by alexgavr on 30.01.17.
//
#include "globalVars.h"
#include <string>

const char *TAG_HEIGHT;
const char *TAG_WIDTH;
const char *TAG_STARTX;
const char *TAG_STARTY;
const char *TAG__FINISHX;
const char *TAG_FINISHY;
const char *TAG_LINECOST;
const char *TAG_DIAGONALCONST;
const char *TAG_SEARCHTYPE;
const char *TAG_METRICTYPE;
const char *TAG_ALLOWDIAGONAL;
const char *TAG_ALLOWSQUEEZE;
const char *TAG_CUTCORNERS;
const char *TAG_CELLSIZE;

double CELLSIZE_DEFAULT;
double LINE_COST_DEFAULT;
double DIAG_COST_DEFAULT;
unsigned int STARTX_DEFAULT;
unsigned int STARTY_DEFAULT;
unsigned int FINISHX_DEFAULT;
unsigned int FINISHY_DEFAULT;
std::string SEARCH_TYPE_DEFAULT;
std::string METRIC_TYPE_DEFAULT;
unsigned int ALLOW_DIAG_DEFAULT;
unsigned int ALLOW_SQUEEZE_DEFAULT;
unsigned int CUT_CORNERS_DEFAULT;

void initGlobalVars()
{
    TAG_HEIGHT = "height";
    TAG_WIDTH = "width";
    TAG_STARTX = "startx";
    TAG_STARTY = "starty";
    TAG__FINISHX = "finishx";
    TAG_FINISHY = "finishy";
    TAG_LINECOST = "linecost";
    TAG_DIAGONALCONST = "diagonalcost";
    TAG_SEARCHTYPE = "searchtype";
    TAG_METRICTYPE = "metrictype";
    TAG_ALLOWDIAGONAL = "allowdiagonal";
    TAG_ALLOWSQUEEZE = "allowsqueeze";
    TAG_CUTCORNERS = "cutcorners";
    TAG_CELLSIZE = "cellsize";

    CELLSIZE_DEFAULT = 1;
    LINE_COST_DEFAULT = 1;
    DIAG_COST_DEFAULT = 1.414;
    STARTX_DEFAULT = 0;
    STARTY_DEFAULT = 0;
    FINISHX_DEFAULT = 0;
    FINISHY_DEFAULT = 0;
    SEARCH_TYPE_DEFAULT = std::string("astar");
    METRIC_TYPE_DEFAULT = "euclid";
    ALLOW_DIAG_DEFAULT = 0;
    ALLOW_SQUEEZE_DEFAULT = 0;
    CUT_CORNERS_DEFAULT = 0;
}

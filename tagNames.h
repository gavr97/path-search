//
// Created by alexgavr on 30.01.17.
//

#ifndef REPO_TAGNAMES_H
#define REPO_TAGNAMES_H

#include <string>


extern int XAXA;
#ifdef MAIN_PART
int XAXA = 7;
#endif


extern const char* (group[1]); #ifdef
const char *TAG_WIDTH = "width";
const char *TAG_STARTX = "startx";
const char *TAG_STARTY = "starty";
const char *TAG__FINISHX = "finishx";
const char *TAG_FINISHY = "finishy";
const char *TAG_LINECOST = "linecost";
const char *TAG_DIAGONALCONST = "diagonalcost";
const char *TAG_SEARCHTYPE = "searchtype";
const char *TAG_METRICTYPE = "metrictype";
const char *TAG_ALLOWDIAGONAL = "allowdiagonal";
const char *TAG_ALLOWSQUEEZE = "allowsqueeze";
const char *TAG_CUTCORNERS = "cutcorners";
const char *TAG_CELLSIZE = "cellsize";


#endif //REPO_TAGNAMES_H
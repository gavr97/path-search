//
// Created by alexgavr on 30.01.17.
//

#ifndef REPO_TAGNAMES_H
#define REPO_TAGNAMES_H

#include <string>

void initGlobalVars();

extern const char *TAG_HEIGHT;
extern const char *TAG_WIDTH;
extern const char *TAG_STARTX;
extern const char *TAG_STARTY;
extern const char *TAG__FINISHX;
extern const char *TAG_FINISHY;
extern const char *TAG_LINECOST;
extern const char *TAG_DIAGONALCONST;
extern const char *TAG_SEARCHTYPE;
extern const char *TAG_METRICTYPE;
extern const char *TAG_ALLOWDIAGONAL;
extern const char *TAG_ALLOWSQUEEZE;
extern const char *TAG_CUTCORNERS;
extern const char *TAG_CELLSIZE;

extern double CELLSIZE_DEFAULT;
extern double LINE_COST_DEFAULT;
extern double DIAG_COST_DEFAULT;
extern unsigned int STARTX_DEFAULT;
extern unsigned int STARTY_DEFAULT;
extern unsigned int FINISHX_DEFAULT;
extern unsigned int FINISHY_DEFAULT;
extern std::string SEARCH_TYPE_DEFAULT;
extern std::string METRIC_TYPE_DEFAULT;
extern unsigned int ALLOW_DIAG_DEFAULT;
extern unsigned int ALLOW_SQUEEZE_DEFAULT;
extern unsigned int CUT_CORNERS_DEFAULT;

#endif //REPO_TAGNAMES_H
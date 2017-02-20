//
// Created by alexgavr on 30.01.17.
//

#ifndef REPO_TAGNAMES_H
#define REPO_TAGNAMES_H

#include <string>


#define TAG_HEIGHT "height"
#define TAG_WIDTH "width"
#define TAG_STARTX "startx"
#define TAG_STARTY "starty"
#define TAG__FINISHX "finishx"
#define TAG_FINISHY "finishy"
#define TAG_LINECOST "linecost"
#define TAG_DIAGONALCONST "diagonalcost"
#define TAG_SEARCHTYPE "searchtype"
#define TAG_METRICTYPE "metrictype"
#define TAG_ALLOWDIAGONAL "allowdiagonal"
#define TAG_ALLOWSQUEEZE "allowsqueeze"
#define TAG_CUTCORNERS "cutcorners"
#define TAG_CELLSIZE "cellsize"
#define TAG_MAP "map"
#define TAG_GRID "grid"
#define TAG_ALGORITHM "algorithm"

#define CELLSIZE_DEFAULT 1
#define LINE_COST_DEFAULT 1
#define DIAG_COST_DEFAULT 1.414
#define STARTX_DEFAULT 0
#define STARTY_DEFAULT 0
#define FINISHX_DEFAULT 0
#define FINISHY_DEFAULT 0
#define SEARCH_TYPE_DEFAULT std::string("astar")
#define METRIC_TYPE_DEFAULT "euclid"
#define ALLOW_DIAG_DEFAULT 0
#define ALLOW_SQUEEZE_DEFAULT 0
#define CUT_CORNERS_DEFAULT 0

#define OBSTACLE '1'
#define NO_OBSTACLE '0'


#endif //REPO_TAGNAMES_H
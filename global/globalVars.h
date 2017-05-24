#ifndef REPO_TAGNAMES_H
#define REPO_TAGNAMES_H

#include <string>

#define TAG_HEIGHT "height"
#define TAG_WIDTH "width"
#define TAG_STARTX "startx"
#define TAG_STARTY "starty"
#define TAG_FINISHX "finishx"
#define TAG_FINISHY "finishy"
#define TAG_H_WEIGHT "hweight"
#define TAG_LINECOST "linecost"
#define TAG_DIAGONALCONST "diagonalcost"
#define TAG_CELLSIZE "cellsize"
#define TAG_SEARCHTYPE "searchtype"
#define TAG_METRICTYPE "metrictype"
#define TAG_ALLOWDIAGONAL "allowdiagonal"
#define TAG_ALLOWSQUEEZE "allowsqueeze"
#define TAG_CUTCORNERS "cutcorners"
#define TAG_MAP "map"
#define TAG_GRID "grid"
#define TAG_ALGORITHM "algorithm"

#define CELLSIZE_DEFAULT 1
#define H_WEIGHT_DEFAULT static_cast<double>(1)
#define LINE_COST_DEFAULT 1
#define DIAG_COST_DEFAULT 1.41421
#define STARTX_DEFAULT 0
#define STARTY_DEFAULT 0
#define FINISHX_DEFAULT 0
#define FINISHY_DEFAULT 0
#define SEARCH_TYPE_DEFAULT std::string("astar")
#define METRIC_TYPE_DEFAULT std::string("diagonal")
#define ALLOW_DIAG_DEFAULT 0
#define ALLOW_SQUEEZE_DEFAULT 0
#define CUT_CORNERS_DEFAULT 0

#define ASTAR std::string("astar")
#define JPS std::string("jp_search")
#define THETA std::string("theta")

#define OBSTACLE '1'
#define NO_OBSTACLE '0'


#endif //REPO_TAGNAMES_H

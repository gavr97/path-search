//
// Created by alexgavr on 07.01.17.
//

/* path is vector<size_t> or
 *         vector<unsigned>
 *
 * every node has, naturally, indRow, indCol and at the same time key(its own integer identifier)
 *
 */

#ifndef REPO_ASTAR_H
#define REPO_ASTAR_H

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <bits/unordered_map.h>
#include "myTask.h"
#include "myHeap.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::pair;

typedef std::vector<unsigned> Path;
typedef unsigned  Node;
typedef double TypeValue;


class AStar {
private:
    //____members that define features of algorithm(object)_____
    TypeValue (*heuristic)(unsigned ux, unsigned uy, unsigned vx, unsigned vy);
    std::vector<short> dxVec;
    std::vector<short> dyVec;
    std::vector<TypeValue> weightVec;
    bool allowSqueeze();


    //____ commom members______
    Task task;
    std::map<unsigned, TypeValue> gTable;
    std::map<unsigned, unsigned> prevTable;

    inline unsigned key(unsigned ux, unsigned uy);
    inline unsigned coordinateFirst(unsigned key);
    inline unsigned coordinateSecond(unsigned key);

    bool computeGValues();
    std::vector<unsigned> constructPath();

public:
    int solve(const Task &task);
    void printPath();
    Path path;
};

#endif //REPO_ASTAR_H

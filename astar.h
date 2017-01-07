//
// Created by alexgavr on 07.01.17.
//

#ifndef REPO_ASTAR_H
#define REPO_ASTAR_H

#include <vector>
#include <string>
#include <myMap.h>
#include "myMap.h"

double heuristicEuclid(unsigned int leftX, unsigned int leftY, unsigned int rightX, unsigned int rightY);

double heuristicDiagonal(unsigned int leftX, unsigned int leftY, unsigned int rightX, unsigned int rightY);

double heuristicChebyshev(unsigned int leftX, unsigned int leftY, unsigned int rightX, unsigned int rightY);

double heuristicManhattan(unsigned int leftX, unsigned int leftY, unsigned int rightX, unsigned int rightY);  // only when allowdiag = 0;

double heuristic(unsigned int leftX, unsigned int leftY, unsigned int rightX, unsigned int rightY, std::string nameHeuristic);

void astar(const Task &task, std::vector<std::vector<std::pair<short, short>>> &adjTable);

void solve(const Task &task);



#endif //REPO_ASTAR_H

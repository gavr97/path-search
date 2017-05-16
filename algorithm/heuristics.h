#ifndef ASEARCH_HEURISTICS_H
#define ASEARCH_HEURISTICS_H

#include "../global/globalTypes.h"

int my_Max(int a, int b);
TypeValue straight(unsigned ux, unsigned uy, unsigned vx, unsigned vy);
TypeValue euclid(unsigned ux, unsigned uy, unsigned vx, unsigned vy);
TypeValue manhattan(unsigned ux, unsigned uy, unsigned vx, unsigned vy);
TypeValue diagonal(unsigned ux, unsigned uy, unsigned vx, unsigned vy);
TypeValue zero(unsigned ux, unsigned uy, unsigned vx, unsigned vy);

#endif //ASEARCH_HEURISTICS_H

#include "heuristics.h"
#include "../global/globalVars.h"
#include <cmath>

using std::abs;

int my_Max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

TypeValue straight(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    TypeValue ret = my_Max(abs((int)ux - (int)vx), abs((int)uy - (int)vy));
    return ret;
}

TypeValue euclid(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    return sqrt(pow(((int)ux - (int)vx), 2) + pow(((int)uy - (int)vy), 2));
}

TypeValue manhattan(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    TypeValue ret = abs((int)ux - (int)vx) + abs((int)uy - (int)vy);
    return ret;
}

TypeValue zero(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    return 0;
}

TypeValue diagonal(unsigned ux, unsigned uy, unsigned vx, unsigned vy)
{
    int side1 = abs((int)ux - (int)vx);
    int  side2 = abs((int)uy - (int)vy);
    int sideStraight = my_Max(side1, side2);
    int sideDiagonal = side1 + side2 - sideStraight;
    sideStraight -= sideDiagonal;
    return sideStraight + DIAG_COST_DEFAULT * sideDiagonal;
}

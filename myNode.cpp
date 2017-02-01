//
// Created by alexgavr on 01.02.17.
//

#include "globalTypes.h"

bool Node::operator <(const Node &right)
{
    return this->key < right.key;
}
//
// Created by alexgavr on 01.02.17.
//

#include "globalTypes.h"

bool Node::operator <(const Node &right) const
{
    return this->key < right.key;
}

bool Node::operator <(Node &right)
{
    return this->key < right.key;
}
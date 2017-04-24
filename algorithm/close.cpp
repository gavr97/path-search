//
// Created by alexgavr on 14.03.17.
//

#include "close.h"


void Close::init(unsigned cntRealRows, unsigned cntRealCols)
{
    this->cntRealRows = cntRealRows;
    this->cntRealCols = cntRealCols;
}

void Close::push(const Node &node)
{
    hash_table[key(node)] = node;
}

std::unordered_map<unsigned, Node>::const_iterator Close::find(const Node &node)
{
    return hash_table.find(key(node));
}

std::unordered_map<unsigned, Node>::const_iterator Close::end()
{
    return hash_table.end();
}

unsigned Close::size() const
{
    return hash_table.size();
}

Node Close::operator[](const Node &node) const {
    return hash_table.find(key(node))->second;
}

Node Close::operator[](unsigned nodeKey) const {
    return hash_table.find(nodeKey)->second;
}

inline unsigned Close::key(unsigned x, unsigned y) const
{
    return x * (cntRealCols + 2) + y;
}

inline unsigned Close::key(const Node &node) const
{
    return key(node.getX(), node.getY());
}


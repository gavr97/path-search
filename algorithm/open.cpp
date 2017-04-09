//
// Created by alexgavr on 14.03.17.
//

#include "open.h"


void Open::push(const Node &node)
{
    set.insert(node);
    hash_table[key(node)] = node;
}

Node Open::pop()
{
    Node node = *(set.begin());
    set.erase(set.begin());
    hash_table.erase(key(node));
    return node;
}

std::unordered_map<unsigned, Node>::const_iterator Open::find(const Node &node) const
{
    return hash_table.find(key(node));
}

std::unordered_map<unsigned, Node>::const_iterator Open::end() const
{
    return hash_table.end();
}

bool Open::decreaseVal(Node &node, TypeValue gVal, TypeValue fVal, unsigned keyNewParent,
                       TypeValue weightMovement)
{
    auto ptr = set.find(node);
    if (ptr == set.end())
        return true;  // an error occured
    set.erase(ptr);
    hash_table.erase(key(node));
    node.setGVal(gVal);
    node.setFVal(fVal);
    node.setKeyParent(keyNewParent);
    set.insert(node);
    hash_table[key(node)] = node;
    return false;
}

Node Open::operator[](const Node &node) const
{
    return hash_table.find(key(node))->second;
}

bool Open::empty() const
{
    return set.empty();
}

unsigned Open::size() const
{
    return hash_table.size();
}

void Open::setMapSizes(unsigned cntRealRows, unsigned cntRealCols)
{
    this->cntRealRows = cntRealRows;
    this->cntRealCols = cntRealCols;
}

inline unsigned Open::key(unsigned x, unsigned y) const
{
    return x * (cntRealCols + 2) + y;
}

inline unsigned Open::key(const Node &node) const
{
    return key(node.getX(), node.getY());
}

//
// Created by alexgavr on 14.03.17.
//

#include "open.h"

void Open::push(const Node &node)
{
    if (node.getFVal() < nodeMin.getFVal()) {
        nodeMin = node;
    }
    hash_table[key(node)] = node;
}

void Open::pushInit(const Node &node)
{
    nodeMin = node;
    hash_table[key(node)] = node;
}

Node Open::pop()
{
    Node node = nodeMin;
    hash_table.erase(key(nodeMin));
    if (!hash_table.empty()) {
        auto ptrNow = hash_table.begin();
        nodeMin = ptrNow->second;
        while (ptrNow != hash_table.end()) {
            if ((ptrNow->second).getFVal() < nodeMin.getFVal()) {
                nodeMin = ptrNow->second;
            }
            ++ptrNow;
        }
    }
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

bool Open::decreaseVal(Node &node, TypeValue gVal, TypeValue fVal, unsigned keyNewParent)
{
    node.setGVal(gVal);
    node.setFVal(fVal);
    node.setKeyParent(keyNewParent);
    hash_table[key(node)] = node;
    if (node.getFVal() < nodeMin.getFVal()) {
        nodeMin = node;
    }
    return false;
}

Node Open::operator[](const Node &node) const
{
    return hash_table.find(key(node))->second;
}

bool Open::empty() const
{
    return hash_table.empty();
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

Node Open::getNode(unsigned x, unsigned y, bool &wasCreated)
{
    wasCreated = false;
    auto found = hash_table.find(key(x, y));
    if (found != hash_table.end()) {
        wasCreated = true;
        return found->second;
    }
    return Node{x, y};
}

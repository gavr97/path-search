#include "close.h"

void Close::init(unsigned cntRealRows, unsigned cntRealCols)
{
    this->cntRealRows = cntRealRows;
    this->cntRealCols = cntRealCols;
}

const Node * Close::push(const Node &node)
{
    auto pair = hash_table.insert(std::pair<unsigned, const Node>(key(node), node));
    auto iter = pair.first;
    const Node * pNode = &(iter->second);
    return pNode;
}

std::unordered_map<unsigned int, const Node>::const_iterator Close::find(const Node &node) const
{
    return hash_table.find(key(node));
}

std::unordered_map<unsigned, const Node>::const_iterator Close::end() const
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


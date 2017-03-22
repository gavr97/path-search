//
// Created by alexgavr on 14.03.17.
//

#include "close.h"


void Close::push(Node node)
{
    hash_table[node.getKey()] = node;
}

std::unordered_map<unsigned, Node>::const_iterator Close::find(Node node)
{
    return hash_table.find(node.getKey());
}

std::unordered_map<unsigned, Node>::const_iterator Close::end()
{
    return hash_table.end();
}

unsigned Close::size() const
{
    return hash_table.size();
}

Node Close::operator[](Node node) const {
    return hash_table.find(node.getKey())->second;
}

Node Close::operator[](unsigned nodeKey) const {
    return hash_table.find(nodeKey)->second;
}

//
// Created by alexgavr on 14.03.17.
//

#include "close.h"


void Close::push(Node node)
{
    hash_table[node.key] = node;
}

std::unordered_map<unsigned, Node>::const_iterator Close::find(Node node)
{
    return hash_table.find(node.key);
}
std::unordered_map<unsigned, Node>::const_iterator Close::end()
{
    return hash_table.end();
};

unsigned Close::size() const
{
    return hash_table.size();
}

Node Close::operator[](Node node) const {
    return hash_table.find(node.key)->second;
}

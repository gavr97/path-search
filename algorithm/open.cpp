//
// Created by alexgavr on 14.03.17.
//

#include "open.h"


void Open::push(Node node)
{
    set.insert(node);
    hash_table[node.getKey()] = node;
}

Node Open::pop()
{
    Node node = *(set.begin());
    set.erase(set.begin());
    hash_table.erase(node.getKey());
    return node;
}

std::unordered_map<unsigned, Node>::const_iterator Open::find(Node node) const
{
    return hash_table.find(node.getKey());
}

std::unordered_map<unsigned, Node>::const_iterator Open::end() const
{
    return hash_table.end();
}

bool Open::decreaseVal(Node node, TypeValue gVal, TypeValue fVal)
{
    auto ptr = set.find(node);
    if (ptr == set.end())
        return true;  // an error occured
    set.erase(ptr);
    hash_table.erase(node.getKey());
    node.setGVal(gVal);
    node.setFVal(fVal);
    set.insert(node);
    hash_table[node.getKey()] = node;
    return false;
}

Node Open::operator[] (Node node) const
{
    return hash_table.find(node.getKey())->second;
}

bool Open::empty() const
{
    return set.empty();
}

unsigned Open::size() const
{
    return hash_table.size();
}
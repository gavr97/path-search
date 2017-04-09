//
// Created by alexgavr on 01.02.17.
//

#include "../global/globalTypes.h"

//bool Node::operator <(const Node &right) const
//{
//    return this->key < right.key;
//}

//bool Node::operator <(Node &right)
//{
//    return this->key < right.key;
//}

bool Node::operator <(const Node &right) const
{
    return ((this->fVal < right.fVal) || (this->fVal == right.fVal && this->key < right.key));
}

bool Node::operator == (const Node &right) const
{
    return this->key == right.key;
}

bool Node::operator !=(const Node &right) const
{
    return this->key != right.key;
}

Node::Node(unsigned int x, unsigned int y, unsigned int key) : x(x), y(y), key(key)
{
}

Node::Node(unsigned int x, unsigned int y, unsigned int key, TypeValue gVal, TypeValue fVal) :
        x(x), y(y), key(key), gVal(gVal), fVal(fVal)
{}

unsigned int Node::getX() const
{
    return x;
}

unsigned int Node::getY() const
{
    return y;
}

unsigned int Node::getKey() const
{
    return key;
}

TypeValue Node::getGVal() const
{
    return gVal;
}

TypeValue Node::getFVal() const
{
    return fVal;
}

void Node::setGVal(TypeValue gVal)
{
    Node::gVal = gVal;
}

void Node::setFVal(TypeValue fVal)
{
    Node::fVal = fVal;
}

Node::Node()
{}

unsigned int Node::getKeyParent() const {
    return keyParent;
}

void Node::setKeyParent(unsigned int keyParent) {
    Node::keyParent = keyParent;
}


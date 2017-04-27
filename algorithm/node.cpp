//
// Created by alexgavr on 01.02.17.
//

#include "../global/globalTypes.h"

bool Node::operator <(const Node &right) const
{
    bool is1 = this->fVal == right.fVal;
    bool is2 = this->x == right.x;
    return ((this->fVal < right.fVal) || ((is1) && (this->x < right.x)) || (is1 && is2 && (this->y < right.y)));
}

bool Node::operator == (const Node &right) const
{
    return ((this->x == right.x) && (this->y == right.y));
}

bool Node::operator !=(const Node &right) const
{
    return !(*this == right);
}

Node::Node(unsigned int x, unsigned int y) : x(x), y(y)
{
}

Node::Node(unsigned int x, unsigned int y, TypeValue gVal, TypeValue fVal) :
        x(x), y(y), gVal(gVal), fVal(fVal)
{}

unsigned int Node::getX() const
{
    return x;
}

unsigned int Node::getY() const
{
    return y;
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

const Node * Node::getParent() const
{
    return parent;
}

void Node::setParent(const Node *parent)
{
    Node::parent = parent;
}

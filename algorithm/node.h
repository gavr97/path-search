//
// Created by alexgavr on 15.03.17.
//

#ifndef REPO_NODE_H
#define REPO_NODE_H

#include "../global/globalTypes.h"

class Node{
private:
    unsigned x;
    unsigned y;
    TypeValue gVal;
    TypeValue fVal;
    unsigned keyParent;

public:
    Node();
    Node(unsigned int x, unsigned int y);
    Node(unsigned int x, unsigned int y, TypeValue gVal, TypeValue fVal);

    unsigned int getX() const;
    unsigned int getY() const;

    TypeValue getGVal() const;
    TypeValue getFVal() const;
    unsigned int getKeyParent() const;

    void setGVal(TypeValue gVal);
    void setFVal(TypeValue fVal);
    void setKeyParent(unsigned int keyParent);

    bool operator == (const Node &right) const;
    bool operator <(const Node &right) const;
    bool operator != (const Node &right) const;
};

#endif //REPO_NODE_H

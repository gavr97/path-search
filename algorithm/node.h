#ifndef REPO_NODE_H
#define REPO_NODE_H

#include "../global/globalTypes.h"

class Node{
private:
    unsigned x;
    unsigned y;
    TypeValue gVal;
    TypeValue fVal;
    const Node* parent;

public:
    Node();
    Node(unsigned int x, unsigned int y);
    Node(unsigned int x, unsigned int y, TypeValue gVal, TypeValue fVal);

    unsigned int getX() const;
    unsigned int getY() const;

    TypeValue getGVal() const;
    TypeValue getFVal() const;
    const Node *getParent() const;

    void setGVal(TypeValue gVal);
    void setFVal(TypeValue fVal);
    void setParent(const Node *parent);

    bool operator == (const Node &right) const;
    bool operator <(const Node &right) const;
    bool operator != (const Node &right) const;
};

#endif //REPO_NODE_H

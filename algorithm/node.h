//
// Created by alexgavr on 15.03.17.
//

#ifndef REPO_NODE_H
#define REPO_NODE_H

class Node{
private:
    unsigned x;
    unsigned y;
    unsigned key;
    TypeValue gVal;
    TypeValue fVal;
    unsigned keyParent;
    TypeValue weightMovement;

public:
    Node();
    Node(unsigned int x, unsigned int y);
    Node(unsigned int x, unsigned int y, unsigned int key);
    Node(unsigned int x, unsigned int y, unsigned int key, TypeValue gVal, TypeValue fVal);

    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int getKey() const;

    TypeValue getGVal() const;
    TypeValue getFVal() const;
    unsigned int getKeyParent() const;
    TypeValue getWeightMovement() const;

    void setGVal(TypeValue gVal);
    void setFVal(TypeValue fVal);
    void setKeyParent(unsigned int keyParent);
    void setWeightMovement(TypeValue weightMovement);

    bool operator == (const Node &right) const;
    bool operator <(const Node &right) const;
    bool operator != (const Node &right) const;
};

#endif //REPO_NODE_H

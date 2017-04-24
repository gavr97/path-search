//
// Created by alexgavr on 14.03.17.
//

#include "open.h"

void Open::init(unsigned cntRealRows, unsigned cntRealCols)
{
    this->cntRealRows = cntRealRows;
    this->cntRealCols = cntRealCols;
    lists.resize(cntRealRows + 2);  // because indexing from one
    _empty = true;
}

void Open::push(const Node &node)
{
    if (_empty || node.getFVal() < nodeMin.getFVal()) {
        nodeMin = node;
    }
    _empty = false;

    std::list<Node> &chain = lists[node.getX()];
    auto newPlace = chain.end(); // before which new node Node should be placed
    auto iter = chain.begin();
    while (iter != chain.end()) {
        if (newPlace == chain.end() && iter->getFVal() > node.getFVal()) {
            newPlace = iter;
            break;
        }
        ++iter;
    }
    chain.insert(newPlace, node);
}

bool isBetter(std::list<Node>::const_iterator iter, const Node &node)
{
    return ((iter->getFVal() > node.getFVal()) ||
            (iter->getFVal() == node.getFVal() && iter->getGVal() < node.getGVal()));
}

bool Open::update(const Node &node, bool &wasCreated)
{
    if (_empty || node.getFVal() < nodeMin.getFVal()) {
        nodeMin = node;
    } else if (node.getFVal() == nodeMin.getFVal()) {  // breking ties
        if (node.getGVal() > nodeMin.getGVal()) {
            nodeMin = node;
        }
    }

    _empty = false;
    wasCreated = false;
    bool shouldPut = true;

    //_____pass chain and find out a place to insert_______
    std::list<Node> &chain = lists[node.getX()];
    auto newPlace = chain.end(); // before which new node Node should be placed
    auto iter = chain.begin();
    while (iter != chain.end()) {
        if (newPlace == chain.end() && isBetter(iter, node))
        {
            newPlace = iter;
            shouldPut = true;
        }

        if (iter->getY() == node.getY() && isBetter(iter, node))
        {
            if (iter == newPlace) {  // specific case
                auto tmp_iter = iter;
                ++tmp_iter;
                newPlace = tmp_iter;
            }
            chain.remove(*iter);
            shouldPut = true;
            wasCreated = true;
            break;
        }

        if (iter->getY() == node.getY() && iter->getFVal() <= node.getFVal())
        {
            shouldPut = false;
            wasCreated = true;
            break;
        }
        ++iter;
    }

    //____insert or not____
    if (shouldPut)
    {
        chain.insert(newPlace, node);
        return true;
    } else {
        return false;
    }
}

Node Open::pop()
{
    Node node = nodeMin;
    auto &chain = lists[nodeMin.getX()];
    auto iter = chain.begin();
    while (iter->getY() != nodeMin.getY()) {
        ++iter;
    }
    chain.remove(*iter);

    bool isInited = false;
    TypeValue minF;
    TypeValue maxG;
    for (auto &chain : lists) {
        if (chain.begin() != chain.end()) {
            if (chain.begin()->getFVal() < minF ||
                (chain.begin()->getFVal() == minF && chain.begin()->getGVal() > maxG) ||
                !isInited)
            {
                isInited = true;
                nodeMin = *(chain.begin());
                minF = nodeMin.getFVal();
                maxG = nodeMin.getGVal();
            }
        }
    }
    if (!isInited)
        _empty = true;
    return node;
}

bool Open::empty() const
{
    return _empty;
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
    std::list<Node> &chain = lists[x];
    auto iter = chain.begin();
    while (iter != chain.end()) {
        if (iter->getY() == y) {
            wasCreated = true;
            return *iter;
        }
        ++iter;
    }
    return Node{x, y, (TypeValue)-1, (TypeValue)-1};
}


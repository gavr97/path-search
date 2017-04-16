//
// Created by alexgavr on 14.03.17.
//

#ifndef REPO_CLOSE_H
#define REPO_CLOSE_H
#include <unordered_map>
#include "../global/globalTypes.h"

class Close {
private:
    std::unordered_map<unsigned, Node> hash_table;
    unsigned cntRealCols;
    unsigned cntRealRows;
    inline unsigned key(unsigned x, unsigned y) const;
    inline unsigned key(const Node &node) const;

public:
    void push(const Node &node);
    std::unordered_map<unsigned, Node>::const_iterator find(const Node &node);
    std::unordered_map<unsigned, Node>::const_iterator end();
    unsigned size() const;
    Node operator[](const Node &node) const;
    Node operator[](unsigned nodeKey) const;
    void setMapSizes(unsigned cntRealRows, unsigned cntRealCols);
};

#endif //REPO_CLOSE_H

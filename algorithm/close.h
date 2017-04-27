//
// Created by alexgavr on 14.03.17.
//

#ifndef REPO_CLOSE_H
#define REPO_CLOSE_H
#include <unordered_map>
#include "../global/globalTypes.h"

class Close {
private:
    std::unordered_map<unsigned, const Node> hash_table;
    unsigned cntRealCols;
    unsigned cntRealRows;
    inline unsigned key(unsigned x, unsigned y) const;
    inline unsigned key(const Node &node) const;

public:
    const Node * push(const Node &node);
    std::unordered_map<unsigned, const Node>::const_iterator find(const Node &node) const;
    std::unordered_map<unsigned, const Node>::const_iterator end() const;
    unsigned size() const;
    Node operator[](const Node &node) const;
    Node operator[](unsigned nodeKey) const;
    void init(unsigned cntRealRows, unsigned cntRealCols);
};

#endif //REPO_CLOSE_H

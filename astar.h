//
// Created by alexgavr on 07.01.17.
//

#ifndef REPO_ASTAR_H
#define REPO_ASTAR_H

#include <vector>
#include <string>
#include <iostream>
#include "myMap.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::pair;

struct Pair {
    long long val;
    size_t key;
};

class Heap {
private:
    vector<Pair> heap;
    vector<size_t> place;
    size_t len;

public:
    Heap(size_t size, long long temp = 0) : len(size), place(size) {
        heap.resize(size, { temp, 0 });
        for (size_t i = 0; i != size; ++i) {
            heap[i].key = i;
            place[i] = i;
        }
    }
    template <typename Iter>
    Heap(Iter first, Iter last) : len(0) {
        size_t size = 0;
        Iter it = first;
        while (it != last) {
            ++size;
            ++it;
        }

        place.resize(size);
        heap.resize(size);
        it = first;
        size_t key = 0;
        while (it != last) {
            long long temp = *it;
            this->heap_insert({ temp, key });
            ++key;
            ++it;
        }
    }
    Heap(std::initializer_list<long long> lst) : len(0) {
        auto first = lst.begin();
        auto last = lst.end();
        auto it = first;
        size_t size = lst.size();

        place.resize(size);
        heap.resize(size);
        size_t key = 0;
        while (it != last) {
            this->heap_insert({ *it, key });
            ++key;
            ++it;
        }
    }

    size_t parent(size_t ind) {
        return (ind - 1) / 2;
    }
    size_t left_son(size_t ind) {
        return 2 * ind + 1;
    }
    size_t right_son(size_t ind) {
        return 2 * ind + 2;
    }

    void heap_insert(Pair pair) {
        heap[len] = pair;
        place[pair.key] = len;
        ++len;
        size_t ind = len - 1;
        up(ind);
    }
    void down(size_t ind) {  // ind - cell's place in heap
        size_t min = ind;
        size_t right = right_son(ind);
        size_t left = left_son(ind);
        if (right < len && heap[right].val < heap[min].val)
            min = right;
        if (left < len && heap[left].val < heap[min].val)
            min = left;
        if (min != ind) {
            place[heap[min].key] = ind;
            place[heap[ind].key] = min;
            std::swap(heap[min], heap[ind]);
            down(min);
        }
    }
    void up(size_t ind) {
        if (ind == 0)
            return;
        size_t dad = parent(ind);
        if (heap[ind].val < heap[dad].val) {
            place[heap[dad].key] = ind;
            place[heap[ind].key] = dad;
            std::swap(heap[ind], heap[dad]);
            up(dad);
        }
    }

    size_t size() const {
        return len;
    }
    bool empty() const  {
        return len == 0;
    }
    size_t top() const {
        return heap[0].key;
    }
    long long operator[] (size_t ind) const {
        size_t indz = place[ind];
        return heap[indz].val;
    }

    void pop() {
        heap[0] = heap[len - 1];
        place[heap[0].key] = 0;
        --len;
        heap.pop_back();
        down(0);
    }
    void decrease_key(size_t key, long long val) {
        size_t ind = place[key];
        heap[ind].val = val;
        up(ind);
    }
};

class AStarBase {
private:
    //____members that define features of algorithm(object)_____
    inline double (*heuristic)(unsigned ux, unsigned uy, unsigned vx, unsigned vy);
    std::vector<short> dx;
    std::vector<short> dy;
    bool allowSqueeze();


    //____ commom members______
    Task task;
    std::vector<std::vector<long long>> gTable;
    std::vector<std::vector<unsigned>> prevTable;
    std::vector<unsigned> path;
    Heap heap;

    inline unsigned key(unsigned ux, unsigned uy);
    void computeGValues();
    void constructPath();
    std::vector<unsigned> solve(const Task &task);
};

#endif //REPO_ASTAR_H

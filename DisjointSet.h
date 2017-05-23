//
// Created by jscherman on 21/05/17.
//

#ifndef ALGO3_TP2_RUTAS_DISJOINTSET_H
#define ALGO3_TP2_RUTAS_DISJOINTSET_H


#include "Eje.h"
#include <list>
#include <iostream>

class DisjointSet {

public:

    struct Subset
    {
        int parent;
        int rank;
        std::list<Eje> edges;
        int size;

        void mergeSubset(Subset *subset) {
            subset->parent = parent;
            edges.splice(edges.begin(), subset->edges);
            size += subset->size;
            if (rank = subset->rank) rank++;
        }

        bool operator==(const Subset& other) {
            return parent = other.parent;
        }
    };

    DisjointSet(int n) : size(n){
        subsets = new Subset*[n];

        // Initialize trivials sets
        for (int i = 0; i < n; ++i) makeSet(i);
    }

    ~DisjointSet() {
        std::list<Subset*> sets = disjointSets();
        for (std::list<Subset*>::iterator it = sets.begin(); it != sets.end(); it++) {
            delete *it;
        }
        delete[] subsets;
    }

    // Initialize set
    void makeSet(int i);

    // A utility function to find set of an element i (uses path compression technique)
    Subset* find(int i);

    // A function that does union of two sets of x and y (uses union by rank)
    void unify(const Eje &e);

    std::list<Subset*> disjointSets();

    Subset & mergeAllSets();

private:

    Subset **subsets;
    int size;

};


#endif //ALGO3_TP2_RUTAS_DISJOINTSET_H

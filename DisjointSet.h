//
// Created by jscherman on 21/05/17.
//

#ifndef ALGO3_TP2_RUTAS_DISJOINTSET_H
#define ALGO3_TP2_RUTAS_DISJOINTSET_H


class DisjointSet {

public:

    DisjointSet(int n) {
        subsets = new Subset[n];

        // Initialize trivials sets
        for (int i = 0; i < n; ++i) makeSet(i);
    }

    ~DisjointSet() {
        delete subsets;
    }

    // Initialize set
    void makeSet(int i);

    // A utility function to find set of an element i (uses path compression technique)
    int find(int i);

    // A function that does union of two sets of x and y (uses union by rank)
    void unify(int x, int y);

private:

    struct Subset
    {
        int parent;
        int rank;
    };

    Subset *subsets;
};


#endif //ALGO3_TP2_RUTAS_DISJOINTSET_H

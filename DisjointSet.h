//
// Created by jscherman on 21/05/17.
//

#ifndef ALGO3_TP2_RUTAS_DISJOINTSET_H
#define ALGO3_TP2_RUTAS_DISJOINTSET_H


#include "Eje.h"
#include <list>
#include <iostream>
#include <string>

class DisjointSet {

public:

    struct Subset
    {
        int parent;
        int rank;
        std::list<Eje> edges;
        int size;

        bool operator==(const Subset& other) {
            return parent = other.parent;
        }

        friend std::ostream & operator<<(std::ostream & os, const Subset& s) {
            os << "Rank " << s.rank << " | Size: " << s.size << " | Parent: " << s.parent << " | Edges: ";
            for (std::list<Eje>::const_iterator it = s.edges.begin(); it != s.edges.end() ; ++it) {
                os << *it << " ";
            }
            return os;
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
    Subset* find(int i) const;

    // A function that does union of two sets of x and y (uses union by rank)
    void unify(const Eje &e);

    std::list<Subset*> disjointSets() const;

    Subset & mergeAllSets();

    friend std::ostream& operator<<(std::ostream& os, const DisjointSet& d) {
        std::list<Subset*> sets = d.disjointSets();
        os << "Disjoint set | " << std::to_string(sets.size())  << " sets: " << std::endl;
        for (std::list<Subset*>::const_iterator it = sets.begin(); it != sets.end() ; ++it) {
            os << "--> " << **it << std::endl;
        }
        return os;
    }

private:

    Subset **subsets;
    int size;

};


#endif //ALGO3_TP2_RUTAS_DISJOINTSET_H

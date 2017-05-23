//
// Created by jscherman on 21/05/17.
//

#include <iostream>
#include "DisjointSet.h"

void DisjointSet::makeSet(int i) {
    subsets[i] = new Subset;
    subsets[i]->parent = i;
    subsets[i]->rank = 0;
    subsets[i]->size = 1;

}

DisjointSet::Subset * DisjointSet::find(int i) const {
    // find root and make root as parent of i (path compression)
    if (subsets[i]->parent != i)
        subsets[i] = find(subsets[i]->parent);

    return subsets[i];
}

void DisjointSet::unify(const Eje &e)
{
    Subset *xroot = find(e.origen);
    Subset *yroot = find(e.destino);

    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    if (xroot->rank < yroot->rank) {
        if (xroot != yroot) yroot->size += xroot->size;
        xroot->parent = yroot->parent;
        yroot->edges.splice(yroot->edges.begin(), xroot->edges);
        yroot->edges.push_back(e);
    } else if (xroot->rank > yroot->rank) {
        if (xroot != yroot) xroot->size += yroot->size;
        yroot->parent = xroot->parent;
        xroot->edges.splice(xroot->edges.begin(), yroot->edges);
        xroot->edges.push_back(e);
    } else {
        // If ranks are same, then make one as root and incrementits rank by one
        if (xroot != yroot) xroot->size += yroot->size;
        yroot->parent = xroot->parent;
        xroot->edges.splice(xroot->edges.begin(), yroot->edges);
        xroot->edges.push_back(e);
        xroot->rank++;
    }
}

std::list<DisjointSet::Subset*> DisjointSet::disjointSets() const {
    bool added[size+1] = {false};
    std::list<Subset*> result;
    for (int i = 0; i < size; ++i) {
        Subset *setOfI = find(i);
        if (!added[setOfI->parent]) {
            result.push_back(setOfI);
            added[setOfI->parent] = true;
        }
    }
    return result;
}

DisjointSet::Subset & DisjointSet::mergeAllSets() {
//    std::list<Subset*> sets = disjointSets();
//    if (!sets.empty()) {
//        Subset* first = sets.front();
//        for (std::list<Subset*>::iterator it = sets.begin(); it != sets.end(); it++) {
//            first->mergeSubset(*it);
//        }
//    }
}

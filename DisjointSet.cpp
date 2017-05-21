//
// Created by jscherman on 21/05/17.
//

#include "DisjointSet.h"

void DisjointSet::makeSet(int i) {
    subsets[i].parent = i;
    subsets[i].rank = 0;
}

int DisjointSet::find(int i) {
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets[i].parent);

    return subsets[i].parent;
}

void DisjointSet::unify(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);

    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        // If ranks are same, then make one as root and incrementits rank by one
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool DisjointSet::generatesCycle(int x, int y) {
    int xParent = find(x);
    int yParent = find(y);

    return xParent == yParent;
}

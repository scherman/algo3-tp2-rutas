//
// Created by jscherman on 24/05/17.
//

#ifndef ALGO3_TP2_RUTAS_DISJOINTSET_H
#define ALGO3_TP2_RUTAS_DISJOINTSET_H


#include "Eje.h"
#include <list>
#include <iostream>

class DisjointSet {

public:

    struct Subset {
        int parent;
        std::list<Eje> edges;
        int rank;
        int size;

        ~Subset(){
//            std::cout << "DESTRUCCION Subset" << this << std::endl;
        }


        friend std::ostream& operator<<(std::ostream& os, const Subset& s){
            os << "[Subset] parent: " << s.parent << ", rank: " << s.rank << ", size: " << s.size << ", edges: ";
            for (std::list<Eje>::const_iterator it = s.edges.begin(); it != s.edges.end(); it++) {
                os << *it << " ";
            }
            return os;
        }
    };

    DisjointSet(int n) : totalSize(n) {
        subsets = new Subset*[n]();
        for (int i = 0; i < n; ++i) {
            makeSet(i);
        }
    };

    DisjointSet(Subset & subset) : totalSize(subset.size), totalEdges(subset.edges){
        subsets = new Subset*[totalSize]();
        for (int i = 0; i < totalSize; ++i) {
            makeSet(i);
        }

        subsets[subset.parent] = &subset;
        for (int i = 0; i < totalSize; ++i) {
            subsets[i]->parent = subset.parent;
        }
    };

    ~DisjointSet(){
//        std::cout << "DESTRUCCION DisjointSet " << this << std::endl;
    }

    std::list<Eje> & edges() {return totalEdges;};

    void makeSet(int v) {
        subsets[v] = new Subset();
        subsets[v]->parent = v;
        subsets[v]->rank = 0;
        subsets[v]->size = 1;
    }

    Subset & find(int v) const {
        if (subsets[v]->parent == v) return *subsets[v];
        else find(subsets[v]->parent);
    }

    void unify(const Eje & eje) {
        Subset &srcSet = find(eje.origen);
        Subset &destSet = find(eje.destino);

//        std::cout << "Estado inicial:" << std::endl;
//        std::cout << srcSet << std::endl;
//        std::cout << destSet << std::endl;

//        srcSet.parent = destSet.parent;

        if (srcSet.rank > destSet.rank) {
            if (srcSet.parent != destSet.parent) srcSet.size += destSet.size;
            srcSet.edges.splice(srcSet.edges.begin(), destSet.edges);
            srcSet.edges.push_back(eje);
            destSet.parent = srcSet.parent;
        } else if (srcSet.rank < destSet.rank) {
            if (srcSet.parent != destSet.parent) destSet.size += srcSet.size;
            destSet.edges.splice(destSet.edges.begin(), srcSet.edges);
            destSet.edges.push_back(eje);
            srcSet.parent = destSet.parent;
        } else {
            if (srcSet.parent != destSet.parent) destSet.size += srcSet.size;
            destSet.edges.splice(destSet.edges.begin(), srcSet.edges);
            destSet.edges.push_back(eje);
            srcSet.parent = destSet.parent;
            destSet.rank++;
        }
        totalEdges.push_back(eje);

//        std::cout << "Estado final:" << std::endl;
//        std::cout << &srcSet << ": " << srcSet << std::endl;
//        std::cout << &destSet << ": " << destSet << std::endl;
//        std::cout << &find(eje.origen) << ": " << find(eje.origen)<< std::endl;
//        std::cout << &find(eje.destino) << ": " << find(eje.destino)<< std::endl;
    };

    std::list<Subset*> sets() const {
        bool seen [totalSize] = {false};

        std::list<Subset*> ss;
        for (int i = 0; i < totalSize; ++i) {
            Subset &subset = find(i);
            if (!seen[subset.parent]) {
                seen[subset.parent] = true;
                ss.push_back(&subset);
                std::cout << &subset << ",";
            }
        }

        std::cout << std::endl;
        for (std::list<DisjointSet::Subset*>::iterator it = ss.begin(); it != ss.end(); ++it) {
            std::cout << *it << ",";
        }

        std::cout << std::endl;
        return ss;
    }

    friend std::ostream& operator<<(std::ostream& os, const DisjointSet& d){
        os << "[DisjointSet] totalSize: "<< d.totalSize << ", subsets: " << std::endl;
        std::list<Subset*> subsets = d.sets();
        for (std::list<Subset*>::const_iterator it = subsets.begin(); it != subsets.end(); it++) {
            os << "--> " << **it << std::endl;
        }
        return os;
    }

private:

    int totalSize;
    std::list<Eje> totalEdges;
    Subset ** subsets;

};


#endif //ALGO3_TP2_RUTAS_DISJOINTSET_H

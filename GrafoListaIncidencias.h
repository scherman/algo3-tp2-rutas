//
// Created by jscherman on 24/05/17.
//

#ifndef ALGO3_TP2_RUTAS_GRAFOLISTAINCIDENCIAS_H
#define ALGO3_TP2_RUTAS_GRAFOLISTAINCIDENCIAS_H


#include "DisjointSet.h"
#include "Eje.h"

class GrafoListaIncidencias {

public:

    GrafoListaIncidencias(int n) : disjointSet(DisjointSet(n)){};
//    GrafoListaIncidencias(int n, DisjointSet::Subset & subset) : disjointSet(DisjointSet(n, subset)){};

//    GrafoListaIncidencias(DisjointSet & disjointSet) : disjointSet(disjointSet) {};

    std::list<Eje> & ejes(){return disjointSet.edges();};

    void agregarEje(Eje e) {
            disjointSet.unify(e);
    };

    std::list<DisjointSet::Subset*> componentesConexas() const{
        return disjointSet.sets();
    }

    friend std::ostream& operator<<(std::ostream& os, const GrafoListaIncidencias& s){
        return os << "[Grafo] " << s.disjointSet;
    }

private:

    DisjointSet disjointSet;

};


#endif //ALGO3_TP2_RUTAS_GRAFOLISTAINCIDENCIAS_H

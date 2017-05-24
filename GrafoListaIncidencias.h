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
    GrafoListaIncidencias(DisjointSet::Subset & subset) : disjointSet(DisjointSet(subset)){};

//    GrafoListaIncidencias(DisjointSet & disjointSet) : disjointSet(disjointSet) {};

    std::list<Eje> & ejes(){return disjointSet.edges();};

    void agregarEje(Eje e) {
            disjointSet.unify(e);
    };

    std::list<DisjointSet::Subset*> componentesConexas() const{
        std::list<DisjointSet::Subset*> asd = disjointSet.sets();
        for (std::list<DisjointSet::Subset*>::iterator it = asd.begin(); it != asd.end(); ++it) {
            std::cout << *it << ",";
        }
        std::cout << std::endl;
        return asd;
    }

    friend std::ostream& operator<<(std::ostream& os, const GrafoListaIncidencias& s){
        return os << "[Grafo] " << s.disjointSet;
    }

private:

    DisjointSet disjointSet;

};


#endif //ALGO3_TP2_RUTAS_GRAFOLISTAINCIDENCIAS_H

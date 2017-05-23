//
// Created by jscherman on 21/05/17.
//

#ifndef ALGO3_TP2_RUTAS_LISTAINCIDENCIAS_H
#define ALGO3_TP2_RUTAS_LISTAINCIDENCIAS_H

#include <list>
#include "GrafoListaIncidencias.h"
#include "DisjointSet.h"
#include <ostream>
#include "Eje.h"

class GrafoListaIncidencias {

public:

    GrafoListaIncidencias(int n) : _cantNodos(n){
        _ejes = new std::list<Eje>();
    }

    GrafoListaIncidencias(int n, std::list<Eje> &ejes) : _cantNodos(n){
        _ejes = &ejes;
    }

    ~GrafoListaIncidencias() {
        delete _ejes;
    }

    const std::list<Eje>* ejes() const {return _ejes;}
    void agregarEje(int origen, int destino, int peso) {_ejes->push_back({origen, destino, peso});};
    GrafoListaIncidencias AGMin();


    std::pair<GrafoListaIncidencias, int> AGMax();

    friend std::ostream& operator<<(std::ostream& os, const GrafoListaIncidencias& g) {
        for (std::list<Eje>::const_iterator it = g.ejes()->begin(); it != g.ejes()->end() ; ++it) {
            os << *it << " ";
        }
        return os;
    }

private:

    std::list<Eje> *_ejes;
    int _cantNodos;

    int pesoTotal;

};


#endif //ALGO3_TP2_RUTAS_LISTAINCIDENCIAS_H

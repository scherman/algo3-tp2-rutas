//
// Created by jscherman on 21/05/17.
//

#ifndef ALGO3_TP2_RUTAS_LISTAINCIDENCIAS_H
#define ALGO3_TP2_RUTAS_LISTAINCIDENCIAS_H

#include <list>
#include <stdlib.h>


class GrafoListaIncidencias {


public:

    struct Eje {
        int origen, destino, peso;

        bool operator<(const Eje& r) {return peso < r.peso;}
    };

    GrafoListaIncidencias(int n) : _cantNodos(n){
        _ejes = new std::list<Eje>();
    }

    ~GrafoListaIncidencias() {
        delete _ejes;
    }


    const std::list<Eje>* ejes() const {return _ejes;}
    void agregarEje(int origen, int destino, int peso) {_ejes->push_back({origen, destino, peso});};

    // Calcula su AGM.
    GrafoListaIncidencias kruskal();

    friend std::ostream& operator<<(std::ostream& os, const GrafoListaIncidencias& g) {
        for (std::list<GrafoListaIncidencias::Eje>::const_iterator it = g.ejes()->begin(); it != g.ejes()->end() ; ++it) {
            GrafoListaIncidencias::Eje e = *it;
            os << "(" << e.origen << ", " << e.destino << ", " << e.peso << ") ";
        }
        return os;
    }

private:

    std::list<Eje> *_ejes;
    int _cantNodos;

};


#endif //ALGO3_TP2_RUTAS_LISTAINCIDENCIAS_H

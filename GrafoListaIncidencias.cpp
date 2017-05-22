//
// Created by jscherman on 21/05/17.
//

#include <iostream>
#include "GrafoListaIncidencias.h"
#include "DisjointSet.h"

bool sortByName(const GrafoListaIncidencias::Eje &x, const GrafoListaIncidencias::Eje &y) { return x.peso < y.peso; }

GrafoListaIncidencias GrafoListaIncidencias::kruskal() {
    // Creo uds trivial (1 set x nodo)
    DisjointSet uds(_cantNodos);

    // Ordenar aristas por peso de forma ascendente
    _ejes->sort();

    GrafoListaIncidencias agm(_cantNodos);
    std::list<GrafoListaIncidencias::Eje>::iterator itEjes= _ejes->begin();
    for (int i = 0; i < _cantNodos; ++i) {
        GrafoListaIncidencias::Eje e = *itEjes;

        // Obtengo representantes de origen y destino
        int repOrigen = uds.find(e.origen);
        int repDestino = uds.find(e.destino);

        // Si no genera ciclos, la agrego
        if (repOrigen != repDestino) {
            agm.agregarEje(e.origen, e.destino, e.peso);
            uds.unify(repOrigen, repDestino);
        }
        itEjes++;
    }

    return agm;
}
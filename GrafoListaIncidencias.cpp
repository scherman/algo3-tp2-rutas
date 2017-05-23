//
// Created by jscherman on 21/05/17.
//

#include "GrafoListaIncidencias.h"

GrafoListaIncidencias GrafoListaIncidencias::AGMin() {
    // Creo uds trivial (1 set x nodo)
    DisjointSet uds(_cantNodos);

    // Ordenar aristas por peso de forma ascendente
    _ejes->sort();

    GrafoListaIncidencias agm(_cantNodos);
    std::list<Eje>::iterator itEjes= _ejes->begin();
    for (int i = 0; i < _cantNodos; ++i) {
        Eje e = *itEjes;

        // Obtengo representantes de origen y destino
        DisjointSet::Subset *setOrigen = uds.find(e.origen);
        DisjointSet::Subset *setDestino = uds.find(e.destino);

        // Si no genera ciclos, la agrego
        if (setOrigen != setDestino) {
            agm.agregarEje(e.origen, e.destino, e.peso);
            uds.unify(e);
        }
        itEjes++;
    }

    return agm;
}
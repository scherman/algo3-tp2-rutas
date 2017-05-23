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

    std::cout << uds << std::endl;

    return agm;
}

std::pair<GrafoListaIncidencias, int> GrafoListaIncidencias::AGMax(){
    // Creo uds trivial (1 set x nodo)
    DisjointSet uds(_cantNodos);

    // Invierto pesos
    for (std::list<Eje>::iterator it = _ejes->begin(); it != _ejes->end(); it++) {
        it->peso = it->peso * (-1);
    }

    // Ordenar aristas por peso de forma ascendente
    _ejes->sort();

    GrafoListaIncidencias agm(_cantNodos);
    int precioDestruccion = 0;

    std::list<Eje>::iterator itEjes= _ejes->begin();
    for (int i = 0; i < _cantNodos; ++i) {
        Eje e = *itEjes;
        e.peso = e.peso * (-1);

        // Obtengo representantes de origen y destino
        DisjointSet::Subset *setOrigen = uds.find(e.origen);
        DisjointSet::Subset *setDestino = uds.find(e.destino);

        // Si no genera ciclos, la agrego
        if (setOrigen != setDestino) {
            agm.agregarEje(e.origen, e.destino, e.peso);
            uds.unify(e);
        } else {
            precioDestruccion += e.peso;
        }
        itEjes++;
    }

    std::cout << uds << std::endl;
};
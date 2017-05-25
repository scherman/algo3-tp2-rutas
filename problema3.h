//
// Created by jscherman on 23/05/17.
//

#ifndef ALGO3_TP2_RUTAS_PROBLEMA3_H
#define ALGO3_TP2_RUTAS_PROBLEMA3_H

#include <utility>
#include <list>
#include <iostream>
#include "Eje.h"
#include "GrafoListaIncidencias.h"


int AGMax(int numberOfNodes, int n, std::list<Eje> & edges) {

    DisjointSet uds(numberOfNodes);

    // Invierto aristas
    for (std::list<Eje>::iterator it = edges.begin(); it != edges.end() ; it++) it->peso = it->peso * (-1);

    // Ordeno de forma ascendente
    edges.sort();

    int costoDestruccion = 0;
    std::list<Eje>::iterator itEjes = edges.begin();
    for (int i = 0; i < n && itEjes != edges.end(); ++i) {
        Eje &eje = *itEjes;
        eje.peso = eje.peso * (-1);

        DisjointSet::Subset setOrigen = uds.find(eje.origen);
        DisjointSet::Subset setDestino = uds.find(eje.destino);

        if (setDestino ==setOrigen) {
            // Ruta innecesaria. Destruirla y sumar costo de destruccion
            costoDestruccion += eje.peso;
            itEjes = edges.erase(itEjes);
        } else {
            // Dejar ruta
            uds.unify(eje);
            itEjes++;
        }
    }

    return costoDestruccion;
}

/*
 * Ejercicio 3
 * >> Grafo simple
 * >>    V := Ciudades
 * >>    E := Rutas
 * >>    p(c1,c2) = Precio de destrucción (si existe) o construcción (si no) de la ruta que une a las ciudades c1 y c2.
 * >> Grafo no necesariamente conexo
 * Input:   totalSize
 *          c1 c2 existe? precioConstruccionODestruccion  (totalSize(totalSize-1)/2 veces)
 *          ...
 *          -1
 * Output:  precioTotal cantRutasFinales c11 c12 c21 c22 ... cr1 cr2
 */
int reconstruirRutas(int n, std::list<std::pair<Eje, bool>> rutas){
    std::list<Eje> rutasNoExistentes;

    GrafoListaIncidencias g(n);
    for (std::list<std::pair<Eje, bool>>::iterator it = rutas.begin(); it != rutas.end(); ++it) {
        std::pair<Eje, bool> ruta = *it;
        if (ruta.second) { // Existe ruta?
            g.agregarEje(ruta.first);
        } else {
            rutasNoExistentes.push_back(ruta.first);
        }
    }

    std::cout << "Grafo inicial: " << g << std::endl;
    int precioTotalDestruccion = 0;
    std::list<DisjointSet::Subset*> componentesConexas = g.componentesConexas();
    for (std::list<DisjointSet::Subset*>::iterator it = componentesConexas.begin(); it != componentesConexas.end(); it++) {
        DisjointSet::Subset &componente = **it;
        int precioDestruccion = AGMax(n, componente.size, componente.edges);
        precioTotalDestruccion += precioDestruccion;
    }
    std::cout << "Grafo final: " << g << std::endl;


}

#endif //ALGO3_TP2_RUTAS_PROBLEMA3_H

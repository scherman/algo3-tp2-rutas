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


int AGMax(int totalSize, int componentSize, std::list<Eje> & edges) {

    DisjointSet uds(totalSize);

    // Invierto aristas
    for (std::list<Eje>::iterator it = edges.begin(); it != edges.end() ; it++) it->peso = it->peso * (-1);

    // Ordeno de forma ascendente
    edges.sort();

    int costoDestruccion = 0;
    std::list<Eje>::iterator itEjes = edges.begin();
    for (int i = 0; i < componentSize && itEjes != edges.end(); ++i) {
        Eje &eje = *itEjes;
        eje.peso = eje.peso * (-1);

        DisjointSet::Subset setOrigen = uds.find(eje.origen);
        DisjointSet::Subset setDestino = uds.find(eje.destino);

        if (setDestino == setOrigen) {
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

int AGMin(int n, std::list<Eje> & rutasExistentes, std::list<Eje> & rutasNoExistentes) {

    DisjointSet uds(n);
    // Agrego rutasExistentes
    for (std::list<Eje>::iterator it = rutasExistentes.begin(); it != rutasExistentes.end() ; it++) uds.unify(*it);

    // Ordeno de forma ascendente
    rutasNoExistentes.sort();

    int costoConstruccion = 0;
    for (std::list<Eje>::iterator itEjes = rutasNoExistentes.begin(); itEjes != rutasNoExistentes.end(); ++itEjes) {
        Eje &eje = *itEjes;

        DisjointSet::Subset setOrigen = uds.find(eje.origen);
        DisjointSet::Subset setDestino = uds.find(eje.destino);

        if (setDestino != setOrigen) {
            // La ruta une componentes desconectadas. Construirla
            uds.unify(eje);
            rutasExistentes.push_back(eje);
            costoConstruccion += eje.peso;
        }
    }

    return costoConstruccion;
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
std::pair<std::list<Eje>, int> reconstruirRutas(int n, std::list<Eje> & rutasExistentes, std::list<Eje> & rutasNoExistentes){

    GrafoListaIncidencias g(n);
    for (std::list<Eje>::iterator it = rutasExistentes.begin(); it != rutasExistentes.end(); it++) {
        g.agregarEje(*it);
    }

    std::list<Eje> rutasResultantes;
    int precioTotal = 0;

//    std::cout << "Grafo inicial: " << g << std::endl;

    std::list<DisjointSet::Subset*> componentesConexas = g.componentesConexas();
    for (std::list<DisjointSet::Subset*>::iterator it = componentesConexas.begin(); it != componentesConexas.end(); it++) {
        DisjointSet::Subset &componente = **it;
        precioTotal += AGMax(n, componente.size, componente.edges);
        rutasResultantes.splice(rutasResultantes.begin(), componente.edges);
    }

    int precioConstruccion = AGMin(n, rutasResultantes, rutasNoExistentes);
    precioTotal += precioConstruccion;

    return std::make_pair(rutasResultantes, precioTotal);

}

#endif //ALGO3_TP2_RUTAS_PROBLEMA3_H

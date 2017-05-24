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
//

    GrafoListaIncidencias g(n);
    for (std::list<std::pair<Eje, bool>>::iterator it = rutas.begin(); it != rutas.end(); ++it) {
        std::pair<Eje, bool> ruta = *it;
        if (ruta.second) { // Existe ruta?
            g.agregarEje(ruta.first);
        } else {
            rutasNoExistentes.push_back(ruta.first);
        }
    }

    std::list<DisjointSet::Subset*> componentesConexas = g.componentesConexas();
    for (std::list<DisjointSet::Subset*>::iterator it = componentesConexas.begin(); it != componentesConexas.end(); it++) {
//        GrafoListaIncidencias componente(**it);
//        DisjointSet::Subset componente = *it;
//        std::cout << componente << std::endl;
//        componente.ejes().pop_front();
//        std::cout << componente << std::endl;
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    componentesConexas.front()->edges.pop_front();

    std::cout << "Fin!" << std::endl;
    std::cout << g << std::endl;


}

#endif //ALGO3_TP2_RUTAS_PROBLEMA3_H

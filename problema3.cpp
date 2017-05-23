//
// Created by jscherman on 22/05/17.
//

#include <utility>
#include <vector>
#include "DisjointSet.h"
#include "GrafoListaIncidencias.h"

/*
 * Ejercicio 3
 * >> Grafo simple
 * >>    V := Ciudades
 * >>    E := Rutas
 * >>    p(c1,c2) = Precio de destrucción (si existe) o construcción (si no) de la ruta que une a las ciudades c1 y c2.
 * >> Grafo no necesariamente conexo
 * Input:   n
 *          c1 c2 existe? precioConstruccionODestruccion  (n(n-1)/2 veces)
 *          ...
 *          -1
 * Output:  precioTotal cantRutasFinales c11 c12 c21 c22 ... cr1 cr2
 */

int reconstruirRutas(int n, std::vector<std::pair<Eje, bool>> rutas){
    std::list<Eje> rutasNoExistentes;
    
    DisjointSet uds(n);
    for (std::vector<std::pair<Eje, bool>>::iterator it = rutas.begin(); it != rutas.end(); ++it) {
        std::pair<Eje, bool> ruta = *it;
        if (ruta.second) { // Existe ruta?
            uds.unify(ruta.first);
        } else {
            rutasNoExistentes.push_back(ruta.first);
        }
    }

    std::list<DisjointSet::Subset*> componentesConexas = uds.disjointSets();
    for (std::list<DisjointSet::Subset*>::iterator it = componentesConexas.begin(); it != componentesConexas.end(); ++it) {
        DisjointSet::Subset* componenteConexa = *it;
        GrafoListaIncidencias grafo (componenteConexa->size, componenteConexa->edges);
//        grafo.AGMax().ejes();
    }

}
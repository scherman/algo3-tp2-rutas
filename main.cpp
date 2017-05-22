#include <iostream>
#include "DisjointSet.h"
#include "GrafoListaIncidencias.h"

/*
 * Ejercicio 1
 * >> Grafo simple: "las ciudades estan conectadas por rutas bidireccionales"
 * >>    V := Ciudades
 * >>    E := Rutas
 * >>    p(c1,c2) = Long. de ruta que une a las ciudades c1 y c2.
 * >> Grafo no necesariamente conexo
 * Input:   origen destino k
 *          c1 c2 esPremium distancia
 *          ...
 *          -1 -1
 * Output:  minima long. pasando por, a lo sumo, k rutas premium.
 */
int calcularCaminoMinimo();

/*
 * Ejercicio 2
 * >> Grafo orientado: "Estas rutas son de una sola mano"
 * >>    V := Ciudades
 * >>    E := Rutas
 * >>    p(c1,c2) = Precio del peaje de la ruta que va de la ciudad c1 a la ciudad c2.
 * >> Grafo fuertemente conexo: "Desde cualquier ciudad se puede viajar a otra ciudad" (no es necesariamente completo)
 * Input:   cantCiudades cantRutas
 *          c1 c2 precio(entero > 0)
 *          ...
 *          -1 -1
 * Output:  maximo subsidio posible que no genere abusos
 */
int maximoSubsidio();

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
int reconstruirRutas();



int main() {
    GrafoListaIncidencias grafo(4);
    grafo.agregarEje(0, 1, 10);
    grafo.agregarEje(0, 2, 6);
    grafo.agregarEje(0, 3, 5);
    grafo.agregarEje(1, 3, 15);
    grafo.agregarEje(2, 3, 4);

    std::cout << "Grafo: " << grafo << std::endl;
    std::cout << "AGM de grafo: " << grafo.kruskal() << std::endl;
    return 0;
}
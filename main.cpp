//#include <iostream>
//#include "DisjointSet.h"
//#include "GrafoListaIncidencias.h"

#include "problema3.h"
#include "Eje.h"
#include <list>
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


int main() {
    escribirTiemposEj3(500, 5);
    return 0;
}
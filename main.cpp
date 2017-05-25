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

    std::list<Eje> rutasExistentes, rutasNoExistentes;

    rutasExistentes.push_back({0, 3, 50});
    rutasExistentes.push_back({1, 3, 70});
    rutasExistentes.push_back({2, 3, 80});
    rutasExistentes.push_back({1, 2, 50});
    rutasExistentes.push_back({4, 5, 90});

    rutasNoExistentes.push_back({0, 2, 10});
    rutasNoExistentes.push_back({0, 1, 10});
    rutasNoExistentes.push_back({4, 0, 10});
    rutasNoExistentes.push_back({4, 1, 20});
    rutasNoExistentes.push_back({4, 2, 30});
    rutasNoExistentes.push_back({4, 3, 40});
    rutasNoExistentes.push_back({4, 6, 5});
    rutasNoExistentes.push_back({5, 0, 50});
    rutasNoExistentes.push_back({5, 1, 50});
    rutasNoExistentes.push_back({5, 2, 50});
    rutasNoExistentes.push_back({5, 3, 50});
    rutasNoExistentes.push_back({5, 6, 50});
    rutasNoExistentes.push_back({6, 0, 99});
    rutasNoExistentes.push_back({6, 1, 99});
    rutasNoExistentes.push_back({6, 2, 99});
    rutasNoExistentes.push_back({6, 3, 1});

    int n = 7;

    reconstruirRutas(n, rutasExistentes, rutasNoExistentes);

    return 0;
}
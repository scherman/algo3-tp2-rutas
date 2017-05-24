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

    std::list<std::pair<Eje, bool>> rutas;
    rutas.push_back(std::make_pair<Eje, bool>({0, 3, 50}, true));
    rutas.push_back(std::make_pair<Eje, bool>({1, 3, 70}, true));
    rutas.push_back(std::make_pair<Eje, bool>({2, 3, 80}, true));
    rutas.push_back(std::make_pair<Eje, bool>({1, 2, 50}, true));
    rutas.push_back(std::make_pair<Eje, bool>({0, 2, 10}, false));
    rutas.push_back(std::make_pair<Eje, bool>({0, 1, 10}, false));

    rutas.push_back(std::make_pair<Eje, bool>({4, 5, 90}, true));
    rutas.push_back(std::make_pair<Eje, bool>({4, 0, 10}, false));
    rutas.push_back(std::make_pair<Eje, bool>({4, 1, 20}, false));
    rutas.push_back(std::make_pair<Eje, bool>({4, 2, 30}, false));
    rutas.push_back(std::make_pair<Eje, bool>({4, 3, 40}, false));
    rutas.push_back(std::make_pair<Eje, bool>({4, 6, 5}, false));
    rutas.push_back(std::make_pair<Eje, bool>({5, 0, 50}, false));
    rutas.push_back(std::make_pair<Eje, bool>({5, 1, 50}, false));
    rutas.push_back(std::make_pair<Eje, bool>({5, 2, 50}, false));
    rutas.push_back(std::make_pair<Eje, bool>({5, 3, 50}, false));
    rutas.push_back(std::make_pair<Eje, bool>({5, 6, 50}, false));

    rutas.push_back(std::make_pair<Eje, bool>({6, 0, 99}, false));
    rutas.push_back(std::make_pair<Eje, bool>({6, 1, 99}, false));
    rutas.push_back(std::make_pair<Eje, bool>({6, 2, 99}, false));
    rutas.push_back(std::make_pair<Eje, bool>({6, 3, 1}, false));

    int n = 7;

    reconstruirRutas(n, rutas);

//    GrafoListaIncidencias grafo(4);
//    grafo.agregarEje(0, 1, 10);
//    grafo.agregarEje(0, 2, 6);
//    grafo.agregarEje(0, 3, 5);
//    grafo.agregarEje(1, 3, 15);
//    grafo.agregarEje(2, 3, 4);
//
//    std::cout << "Grafo: " << grafo << std::endl;
//    std::cout << "AGM de grafo: " << grafo.AGMin() << std::endl;
    return 0;
}
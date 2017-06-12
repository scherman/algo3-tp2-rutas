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
#include "stringTokenizer.hpp"
#include <random>
#include <set>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>


void imprimirEjes(std::list<Eje> & ejes) {
    for (std::list<Eje>::iterator it = ejes.begin(); it != ejes.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

std::pair<std::list<Eje>, long> AGMax(int totalSize, int componentSize, std::list<Eje> & edges) {

    DisjointSet uds(totalSize);

    // Invierto aristas
    for (std::list<Eje>::iterator it = edges.begin(); it != edges.end() ; it++) it->peso = it->peso * (-1);

    // Ordeno de forma ascendente
    edges.sort();

    std::list<Eje> agm;
    long costoDestruccion = 0;
    std::list<Eje>::iterator itEjes = edges.begin();
    while (agm.size() < componentSize - 1 && itEjes != edges.end()) {
        Eje &eje = *itEjes;
        eje.peso = eje.peso * (-1);

        DisjointSet::Subset setOrigen = uds.find(eje.origen);
        DisjointSet::Subset setDestino = uds.find(eje.destino);

        if (setDestino == setOrigen) {
            // Ruta innecesaria. Destruirla y sumar costo de destruccion
            costoDestruccion += eje.peso;
        } else {
            // Dejar ruta
            uds.unify(eje);
            agm.push_back(eje);
        }
        itEjes++;
    }
    return std::make_pair(agm, costoDestruccion);
}

std::pair<std::list<Eje>, int> AGMin(int n, std::list<Eje> & rutasExistentes, std::list<Eje> & rutasNoExistentes) {

    DisjointSet uds(n);

    // Agrego rutasExistentes
    for (std::list<Eje>::iterator it = rutasExistentes.begin(); it != rutasExistentes.end() ; it++) {
        uds.unify(*it);
    }

    // Ordeno de forma ascendente
    rutasNoExistentes.sort();

    int costoConstruccion = 0;
    std::list<Eje> rutasNuevas;
    std::list<Eje>::iterator itEjes = rutasNoExistentes.begin();
    while (rutasNuevas.size() + rutasExistentes.size() < n - 1 && itEjes != rutasNoExistentes.end()) {
        Eje &eje = *itEjes;

        DisjointSet::Subset setOrigen = uds.find(eje.origen);
        DisjointSet::Subset setDestino = uds.find(eje.destino);

        if (setDestino != setOrigen) {
            // La ruta une componentes desconectadas. Construirla
            uds.unify(eje);
            rutasNuevas.push_back(eje);
            costoConstruccion += eje.peso;
        }
        ++itEjes;
    }

    return std::make_pair(rutasNuevas, costoConstruccion);
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
std::pair<std::list<Eje>, long> reconstruirRutas(int n, std::list<Eje> & rutasExistentes, std::list<Eje> & rutasNoExistentes){

    std::list<Eje> rutasResultantes;
    long precioTotal = 0;

    // Paso 1: Armo componentes conexas
    GrafoListaIncidencias g(n);
    for (std::list<Eje>::iterator it = rutasExistentes.begin(); it != rutasExistentes.end(); it++) {
        g.agregarEje(*it);
    }

    // Paso 2: Destruyo rutas innecesarias mas baratas
    std::list<DisjointSet::Subset*> componentesConexas = g.componentesConexas();
//    std::cout << "Cant componentes conexas: " << componentesConexas.size() << std::endl;
    for (std::list<DisjointSet::Subset*>::iterator it = componentesConexas.begin(); it != componentesConexas.end(); it++) {
        DisjointSet::Subset &componente = **it;
        std::pair<std::list<Eje>, long> destruccion = AGMax(n, componente.size, componente.edges);
        rutasResultantes.splice(rutasResultantes.begin(), destruccion.first);
        precioTotal += destruccion.second;
    }
//    std::cout << "Rutas dps de destruccion (" << rutasResultantes.size() << "): ";
//    imprimirEjes(rutasResultantes);

    // Paso 3: Construyo las rutas nuevas más baratas (y necesarias)
    std::pair<std::list<Eje>, long> construccion = AGMin(n, rutasResultantes, rutasNoExistentes);
    rutasResultantes.splice(rutasResultantes.begin(), construccion.first);
    precioTotal += construccion.second;
//    std::cout << "Rutas dps de construccion(" << rutasResultantes.size() << "): ";
//    imprimirEjes(rutasResultantes);

    return std::make_pair(rutasResultantes, precioTotal);

}

// Devuelve matriz de adyacencia y de incidencias
std::pair<std::list<Eje>, int**> generarGrafo(int n, int m, bool conexo) {
//    std::cout << "n = " << n << ", m = " << m << " < " << (n*(n-1))/2 << std::endl;
    if (m > (n*(n-1))/2) throw std::invalid_argument( "No puede tener tantos ejes!");
    if (conexo && m < n - 1) throw std::invalid_argument( "No puede ser conexo porque m < n - 1");

    std::list<Eje> rutasExistentes;

    int **ejesAgregados= new int*[n];
    for(int i = 0; i < n; ++i) {
        ejesAgregados[i] = new int[n];
        for(int r = 0; r < n; ++r) {
            if (i == r) {
                ejesAgregados[i][r] = 1;
            } else {
                ejesAgregados[i][r] = 0;
            }
        }
    }

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist_vertices(0, n-1);
    std::uniform_int_distribution<int> uniform_dist_pesos(0, 5000);
    if (conexo) {

        int origen = uniform_dist_vertices(e1);
        // Agrego m rutas existentes aleatorias
        while (rutasExistentes.size() < m) {
            int destino = uniform_dist_vertices(e1);
            if (ejesAgregados[origen][destino] == 0) {
                // Todavia no agregue esta arista. La agrego
                int peso = uniform_dist_pesos(e1);
                ejesAgregados[origen][destino] = 1;
                ejesAgregados[destino][origen] = 1;
                rutasExistentes.push_back({origen, destino, peso});
            }
            origen = destino;
        }
    } else {
        // Agrego m rutas existentes aleatorias
        while (rutasExistentes.size() < m) {
            int origen = uniform_dist_vertices(e1);
            int destino = uniform_dist_vertices(e1);
            if (ejesAgregados[origen][destino] == 0) {
                // Todavia no agregue esta arista. La agrego
                int peso = uniform_dist_pesos(e1);
                ejesAgregados[origen][destino] = 1;
                ejesAgregados[destino][origen] = 1;
                rutasExistentes.push_back({origen, destino, peso});
            }
        }
    }
    return std::make_pair(rutasExistentes, ejesAgregados);
}

std::list<Eje> rutasComplemento(int n, const std::list<Eje> &rutasExistentes, int** &ejesAgregados) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist_pesos(0, 5000);

    std::list<Eje> rutasNoExistentes;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!ejesAgregados[i][j] && !ejesAgregados[j][i]) {
                int peso = uniform_dist_pesos(e1);
                ejesAgregados[i][j] = 1;
                ejesAgregados[j][i] = 1;
                rutasNoExistentes.push_back({i, j, peso});
            }
        }
    }
    return rutasNoExistentes;
}

void escribirTiemposEj3(int maxN, int cantInstanciasPorN) {
    std::string nombreArchivo = "tiempos-ej3";

    std::stringstream ss;
    ss <<  "/home/jscherman/CLionProjects/algo3-tp2-rutas/datos/" << nombreArchivo << ".csv";
    std::ofstream a_file (ss.str());

    a_file << "cant_ejes, ns_rutas_completas, ns_rutas_vacias, ns_rutas_esparso_conexo, ns_rutas_esparso_disconexo, ns_rutas_denso_conexo, ns_rutas_denso, disconexo" << std::endl;

    for (int i = 3; i < maxN; ++i) {
        int tiempoTotalRutasCompletas = 0;
        int tiempoTotalRutasVacias = 0;
        int tiempoTotalRutasEsparsoConexo = 0;
        int tiempoTotalRutasEsparsoDisconexo = 0;
        int tiempoTotalRutasDensoConexo = 0;
        int tiempoTotalRutasDensoDisconexo = 0;
        for (int j = 0; j < cantInstanciasPorN; ++j) {
            {
                // Test rutas completas
                std::pair<std::list<Eje> , int**> grafo = generarGrafo(i, (i*(i-1))/2, false);
                std::list<Eje> rutasExistentes = grafo.first;
                std::list<Eje> rutasNoExistentes = rutasComplemento(i, rutasExistentes, grafo.second);

                auto tpi = std::chrono::high_resolution_clock::now();
                std::pair<std::list<Eje>, long> pair = reconstruirRutas(i, rutasExistentes, rutasNoExistentes);
                auto tpf = std::chrono::high_resolution_clock::now();
                auto tiempoRutasCompletas = std::chrono::duration_cast<std::chrono::nanoseconds>(tpf-tpi).count();
                tiempoTotalRutasCompletas += tiempoRutasCompletas;
            }
            {
                // Test rutas vacias
                std::pair<std::list<Eje> , int**> grafo = generarGrafo(i, 0, false);
                std::list<Eje> rutasExistentes = grafo.first;
                std::list<Eje> rutasNoExistentes = rutasComplemento(i, rutasExistentes, grafo.second);

                auto tpi = std::chrono::high_resolution_clock::now();
                std::pair<std::list<Eje>, long> pair = reconstruirRutas(i, rutasExistentes, rutasNoExistentes);
                auto tpf = std::chrono::high_resolution_clock::now();
                auto tiempoRutasVacias = std::chrono::duration_cast<std::chrono::nanoseconds>(tpf-tpi).count();
                tiempoTotalRutasVacias += tiempoRutasVacias;
            }
            {
                // Test rutas esparso conexo
                std::pair<std::list<Eje> , int**> grafo = generarGrafo(i, i, true);
                std::list<Eje> rutasExistentes = grafo.first;
                std::list<Eje> rutasNoExistentes = rutasComplemento(i, rutasExistentes, grafo.second);

                auto tp1i = std::chrono::high_resolution_clock::now();
                std::pair<std::list<Eje>, long> pair = reconstruirRutas(i, rutasExistentes, rutasNoExistentes);
                auto tp1f = std::chrono::high_resolution_clock::now();
                auto tiempoRutasEsparsoConexo = std::chrono::duration_cast<std::chrono::nanoseconds>(tp1f-tp1i).count();
                tiempoTotalRutasEsparsoConexo += tiempoRutasEsparsoConexo;
            }
            {
                // Test rutas esparso disconexo
                std::pair<std::list<Eje> , int**> grafo = generarGrafo(i, i, false);
                std::list<Eje> rutasExistentes = grafo.first;
                std::list<Eje> rutasNoExistentes = rutasComplemento(i, rutasExistentes, grafo.second);

                auto tp1i = std::chrono::high_resolution_clock::now();
                std::pair<std::list<Eje>, long> pair = reconstruirRutas(i, rutasExistentes, rutasNoExistentes);
                auto tp1f = std::chrono::high_resolution_clock::now();
                auto tiempoRutasEsparsoDisconexo = std::chrono::duration_cast<std::chrono::nanoseconds>(tp1f-tp1i).count();
                tiempoTotalRutasEsparsoDisconexo += tiempoRutasEsparsoDisconexo;
            }
            {
                // Test rutas denso conexo
                std::pair<std::list<Eje> , int**> grafo = generarGrafo(i, pow(i-1, 2)/2, true);
                std::list<Eje> rutasExistentes = grafo.first;
                std::list<Eje> rutasNoExistentes = rutasComplemento(i, rutasExistentes, grafo.second);

                auto tp1i = std::chrono::high_resolution_clock::now();
                std::pair<std::list<Eje>, long> pair = reconstruirRutas(i, rutasExistentes, rutasNoExistentes);
                auto tp1f = std::chrono::high_resolution_clock::now();
                auto tiempoRutasDensoConexo = std::chrono::duration_cast<std::chrono::nanoseconds>(tp1f-tp1i).count();
                tiempoTotalRutasDensoConexo += tiempoRutasDensoConexo;
            }
            {
                // Test rutas denso disconexo
                std::pair<std::list<Eje> , int**> grafo = generarGrafo(i ,pow(i-1, 2)/2, false);
                std::list<Eje> rutasExistentes = grafo.first;
                std::list<Eje> rutasNoExistentes = rutasComplemento(i, rutasExistentes, grafo.second);

                auto tp1i = std::chrono::high_resolution_clock::now();
                std::pair<std::list<Eje>, long> pair = reconstruirRutas(i, rutasExistentes, rutasNoExistentes);
                auto tp1f = std::chrono::high_resolution_clock::now();
                auto tiempoRutasDensoDisconexo = std::chrono::duration_cast<std::chrono::nanoseconds>(tp1f-tp1i).count();
                tiempoTotalRutasDensoDisconexo += tiempoRutasDensoDisconexo;
            }
        }

        tiempoTotalRutasCompletas = tiempoTotalRutasCompletas / cantInstanciasPorN;
        tiempoTotalRutasVacias = tiempoTotalRutasVacias / cantInstanciasPorN;
        tiempoTotalRutasEsparsoConexo = tiempoTotalRutasEsparsoConexo / cantInstanciasPorN;
        tiempoTotalRutasEsparsoDisconexo = tiempoTotalRutasEsparsoDisconexo / cantInstanciasPorN;
        tiempoTotalRutasDensoConexo = tiempoTotalRutasDensoConexo / cantInstanciasPorN;
        tiempoTotalRutasDensoDisconexo = tiempoTotalRutasDensoDisconexo / cantInstanciasPorN;
        std::cout << i << ", " << tiempoTotalRutasCompletas << ", " << tiempoTotalRutasVacias<< ", " << tiempoTotalRutasEsparsoConexo<< ", " << tiempoTotalRutasEsparsoDisconexo << ", " << tiempoTotalRutasDensoConexo << ", " << tiempoTotalRutasDensoDisconexo << std::endl ;
        a_file << i << ", " << tiempoTotalRutasCompletas << ", " << tiempoTotalRutasVacias<< ", " << tiempoTotalRutasEsparsoConexo<< ", " << tiempoTotalRutasEsparsoDisconexo << tiempoTotalRutasDensoConexo << ", " << tiempoTotalRutasDensoDisconexo << std::endl ;
    }

    a_file.close();
    std::cout << "Listo!" << std::endl;
}


int main(int argc, char *argv[])
{
    if (argc <= 1) throw std::invalid_argument( "No se ingreso nada!" );

    unsigned n, m;
    stringTokenizer strTok;
    string linea;
    fstream input(argv[1], fstream::in);
    while(getline(input, linea)){
        if(linea == "-1") continue;
        strTok.tokenize(linea, ' ');
        n = stoi(strTok[0]);
        m = (n*(n-1))/2;
        std::list<Eje> rutasExistentes;
        std::list<Eje> rutasNoExistentes;
        for(int i = 0; i < m; i++){
            int origen, destino, precio, existe;
            getline(input, linea);
            strTok.tokenize(linea, ' ');
            origen = stoi(strTok[0]);
            destino = stoi(strTok[1]);
            existe = stoi(strTok[2]);
            precio = stoi(strTok[3]);
            if (existe) rutasExistentes.push_back({origen, destino, precio});
            else rutasNoExistentes.push_back({origen, destino, precio});
        }

        // Ejecucion
        std::pair<std::list<Eje>, int> resultado = reconstruirRutas(n, rutasExistentes, rutasNoExistentes);
        std::list<Eje> rutas = resultado.first;
        int costo = resultado.second;
        std::cout << costo << " " << rutas.size();
        for (std::list<Eje>::iterator it = rutas.begin(); it != rutas.end(); it++) {
            std::cout << " " << it->origen << " " << it->destino;
        }
        std::cout << std::endl;
    }
    input.close();
}

#endif //ALGO3_TP2_RUTAS_PROBLEMA3_H

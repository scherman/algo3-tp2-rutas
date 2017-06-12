#include <utility>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>

#include "listaAdyacencia.hpp"
#include "stringTokenizer.hpp"
#include "Eje.h"
#include "DisjointSet.h"

using namespace std;

bool tiene_ciclos_negativos(std::list<Eje> grafo, int n, int origen) {

    // Inicializar distancias en infinito
    int dist[n];
    int infinito = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++) {
        dist[i] = infinito;
    }
    dist[origen] = 0;

    // Relajar todos los ejes n-1 veces
    for (int i = 1; i < n; i++) {
        for (std::list<Eje>::iterator it = grafo.begin(); it != grafo.end(); it++) {
            Eje &eje = *it;
            int u = eje.origen;
            int v = eje.destino;
            int weight = eje.peso;
            if (dist[u] != infinito && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Chequeo ciclos negativos
    for (std::list<Eje>::iterator it = grafo.begin(); it != grafo.end(); it++) {
        Eje &eje = *it;
        int u = eje.origen;
        int v = eje.destino;
        int weight = eje.peso;
        if (dist[u] != infinito && dist[u] + weight < dist[v]){
            return true; // Tiene ciclo negativo
        }
    }
    return false;
}


void aumentarSubsidio(std::list<Eje> &grafo, int valor) {
    for (std::list<Eje>::iterator it = grafo.begin(); it != grafo.end(); it++) {
        it->peso -= valor;
    }
}
void disminuirSubsidio(std::list<Eje> &grafo, int valor) {
    for (std::list<Eje>::iterator it = grafo.begin(); it != grafo.end(); it++) {
        it->peso += valor;
    }
}


void imprimirEjes(std::list<Eje> & ejes) {
    for (std::list<Eje>::iterator it = ejes.begin(); it != ejes.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int problema_dos(std::list<Eje> grafo, int n, int m, int c) {

    // Conecto componentes conexas con un nodo 'centinela'
    int centinela = n;
    for (int k = 0; k < n; ++k) {
        grafo.push_back({centinela, k, c});
        m++;
    }
    n++;

    // Busco subsidio
    int j = c + 1;
    int i = 0;
    int subsidio, ultimoSubsidio;
    if (tiene_ciclos_negativos(grafo, n, centinela)) return 0;
    while (i <= j) {
        subsidio = (j+i)/2;

        // Evito ciclo infinito en caso borde (C = 50, subsidio = 50)
        if (subsidio == ultimoSubsidio) break;

        // Intento subsidiar
        aumentarSubsidio(grafo, subsidio);
        if (tiene_ciclos_negativos(grafo,n,centinela)) {
            j = subsidio;
        } else {
            i = subsidio;
        }
        // Vuelvo al subsidio de antes
        disminuirSubsidio(grafo, subsidio);

        ultimoSubsidio = subsidio;
    }
    return subsidio;
}

//#include "problema3.cpp"

int main(int argc, char** argv){

    unsigned n, m;
    stringTokenizer strTok;
    string linea;
    fstream input(argv[1], fstream::in);
    while(getline(input, linea)){
        if(linea == "-1 -1") continue;
        strTok.tokenize(linea, ' ');
        n = stoi(strTok[0]);
        m = stoi(strTok[1]);
        std::list<Eje> grafo;
        int c = 0;
        for(int i = 0; i < m; i++){
			int c1, c2, p;
			getline(input, linea);
			strTok.tokenize(linea, ' ');
			c1 = stoi(strTok[0]);
			c2 = stoi(strTok[1]);
			p = stoi(strTok[2]);
			grafo.push_back({c1, c2, p});
			if (p > c) { //buscar el mayor peaje
                		c = p;
			}
		}
		cout << problema_dos(grafo, n, m, c) << endl;
	}
	input.close();
}

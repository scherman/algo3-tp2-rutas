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

bool tiene_ciclos_negativos(std::list<Eje> grafo, int n, int m) {
    int dist[n];
    int infinito = std::numeric_limits<int>::max();

    // Inicializar distancias en infinito
    for (int i = 0; i < n; i++) {
        dist[i] = infinito;
    }
    dist[0] = 0;

    // Relajar todos los ejes n-1 veces
    for (int i = 1; i <= n-1; i++) {
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




int problema_dos(std::list<Eje> grafo, int n, int m, int c) {

    // Genero grafo
    int centinela = n;
    DisjointSet g(n);
    for (std::list<Eje>::const_iterator it = grafo.begin(); it != grafo.end() ; it++) {
        g.unify(*it);
    }

    // Uno centinela al representante de cada componente conexa
    std::list<DisjointSet::Subset*> sets = g.sets();
    for (std::list<DisjointSet::Subset*>::const_iterator it = sets.begin(); it != sets.end() ; it++) {
        DisjointSet::Subset* actual = *it;
        grafo.push_back({actual->parent, n, c});
        grafo.push_back({n, actual->parent, c});
        m = m + 2;
    }

    int j = c;
    int i = 1;
    int centro;

    if (tiene_ciclos_negativos(grafo, n+1, m)) return 0;
    while (i < j) {
        centro = (j+i)/2;
        aumentarSubsidio(grafo, centro);
        if (tiene_ciclos_negativos(grafo,n+1,m)) {
            j = centro;
            disminuirSubsidio(grafo, centro);
        } else {
            i = centro;
        }
    }
    return centro;
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

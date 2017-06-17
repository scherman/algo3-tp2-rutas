#include <utility>
#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>
#include <random>
#include <sstream>
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
    int j = c+1;
    int i = 0;
    int subsidio, ultimoSubsidio;
    while (i < j) {
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


std::pair<std::list<Eje>, int> generarGrafo(int n, int m, bool conexo, long C) {
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

    int maxPeso = 0;
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist_vertices(0, n-1);
    std::uniform_int_distribution<int> uniform_dist_pesos(1, C);

    // Agrego 1 ruta por cada ciudad para que no me queden vertices aislados
    for (int i = 0; i < n; ++i) {
        int peso = uniform_dist_pesos(e1);
        if (peso > maxPeso) maxPeso = peso;
        int destino = uniform_dist_vertices(e1);
        while (destino == i) {
            destino = uniform_dist_vertices(e1);
        }
        ejesAgregados[i][destino] = 1;
        rutasExistentes.push_back({i, destino, peso});
    }

    // Agrego m rutas existentes aleatorias
    while (rutasExistentes.size() < m) {
        int origen = uniform_dist_vertices(e1);
        int destino = uniform_dist_vertices(e1);
        if (ejesAgregados[origen][destino] == 0) {
            // Todavia no agregue esta arista. La agrego
            int peso = uniform_dist_pesos(e1);
            if (peso > maxPeso) maxPeso = peso;
            ejesAgregados[origen][destino] = 1;
            rutasExistentes.push_back({origen, destino, peso});
        }
    }

    for (int j = 0; j < n; ++j) {
        delete ejesAgregados[j];
    }
    delete[] ejesAgregados;

    return std::make_pair(rutasExistentes, maxPeso);
}

void variarN(int cantInstanciasPorN, int minN, int maxN, int constantePesoMax){
    std::string nombreArchivo = "tiempos-ej2-variando-n";

    std::stringstream ss;
    ss <<  "/home/jscherman/CLionProjects/algo3-tp2-rutas/datos/" << nombreArchivo << ".csv";
    std::ofstream a_file (ss.str());

    a_file << "n, tiempoTotal" << std::endl;

    int m = minN*(minN-1)/2;
    std::cout << "Variando n: {m=" << m << ", C=" << constantePesoMax << "} => " << minN << " <= n <= " << maxN << std::endl;
    for (int i = minN; i <= maxN; ++i) {

        long long tiempoTotal = 0;
        for (int j = 0; j < cantInstanciasPorN; ++j) {
            std::pair<std::list<Eje> , int> grafo = generarGrafo(i, m, false, constantePesoMax);
            auto tpi = std::chrono::high_resolution_clock::now();
            int res = problema_dos(grafo.first, i, grafo.first.size(), grafo.second);
            auto tpf = std::chrono::high_resolution_clock::now();
            auto tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(tpf-tpi).count();
            tiempoTotal+= tiempo;
        }

        tiempoTotal = tiempoTotal/ cantInstanciasPorN;
        std::cout << i << ", " << tiempoTotal << std::endl ;
        a_file << i <<  ", " << tiempoTotal << std::endl;
    }

    a_file.close();
    std::cout << "Listo!" << std::endl;
}

void variarM(int cantInstanciasPorM, int constanteN,  int constantePesoMaximo){
    std::string nombreArchivo = "tiempos-ej2-variando-m";

    std::stringstream ss;
    ss <<  "/home/jscherman/CLionProjects/algo3-tp2-rutas/datos/" << nombreArchivo << ".csv";
    std::ofstream a_file (ss.str());

    a_file << "m, tiempoTotal" << std::endl;
    int maxM = (constanteN*(constanteN-1))/2;
    int minM = constanteN;
    std::cout << "Variando m: {n=" << constanteN << ", C=" << constantePesoMaximo << "} => " << minM << " <= m <= " << maxM << std::endl;
    for (int i = minM; i <= maxM; ++i) {
        long long tiempoTotal = 0;
        for (int j = 0; j < cantInstanciasPorM; ++j) {
            std::pair<std::list<Eje> , int> grafo = generarGrafo(constanteN, i, false, constantePesoMaximo);

            auto tpi = std::chrono::high_resolution_clock::now();
            int res = problema_dos(grafo.first, constanteN, grafo.first.size(), grafo.second);
            auto tpf = std::chrono::high_resolution_clock::now();
            auto tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(tpf-tpi).count();
            tiempoTotal+= tiempo;
        }

        tiempoTotal = tiempoTotal/ cantInstanciasPorM;
        std::cout << i << ", " << tiempoTotal << std::endl ;
        a_file << i << ", " << tiempoTotal << std::endl;
    }

    a_file.close();
    std::cout << "Listo!" << std::endl;
}

void variarC(int cantInstanciasPorC, int minC, int maxC, int constanteN, int constanteM){
    std::string nombreArchivo = "tiempos-ej2-variando-c";

    std::stringstream ss;
    ss <<  "/home/jscherman/CLionProjects/algo3-tp2-rutas/datos/" << nombreArchivo << ".csv";
    std::ofstream a_file (ss.str());

    a_file << "c, tiempoTotal" << std::endl;
    std::cout << "Variando c: {n=" << constanteN << ", m=" << constanteM << "} => " << minC << " <= c <= " << maxC << std::endl;
    for (int i = minC; i <= maxC; ++i) {
        long long tiempoTotal = 0;
        for (int j = 0; j < cantInstanciasPorC; ++j) {
            std::pair<std::list<Eje> , int> grafo = generarGrafo(constanteN, constanteM, false, i);

            auto tpi = std::chrono::high_resolution_clock::now();
            int res = problema_dos(grafo.first, constanteN, constanteM, grafo.second);
            auto tpf = std::chrono::high_resolution_clock::now();
            auto tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(tpf-tpi).count();
            tiempoTotal+= tiempo;
        }

        tiempoTotal = tiempoTotal/ cantInstanciasPorC;
        std::cout << i << ", " << tiempoTotal << std::endl ;
        a_file << i << ", " << tiempoTotal << std::endl;
    }

    a_file.close();
    std::cout << "Listo!" << std::endl;
}

void escribirTiemposEj2(){
    int cantInstanciasPorValor = 5;
    int cotaPesoMaximo = 5000;
    {
        int minN = 10, maxN = 1000;
        variarN(cantInstanciasPorValor, minN, maxN, cotaPesoMaximo);
    }
    {
        int n = 50;
        variarM(cantInstanciasPorValor, n, cotaPesoMaximo);
    }
    {
        int minC = 1, maxC = 1000, n = 200, m = 300;
        variarC(cantInstanciasPorValor, minC, maxC, 200, 300);
    }
}


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
			if (p > c) c = p;
		}
		cout << problema_dos(grafo, n, m, c) << endl;
	}
	input.close();
}

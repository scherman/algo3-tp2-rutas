#include <iostream>
#include <fstream>
#include <math.h>

#include "listaAdyacencia.hpp"
#include "stringTokenizer.hpp"

using namespace std;

//Nodo: Tupla(ciudad, k)
//Vecino: Tupla(Nodo, d)  donde d es la distancia
typedef pair<unsigned, unsigned> nodo;
typedef pair <nodo, int> vecino;
#define make_nodo make_pair
#define make_vecino make_pair

/*
template <typename... Args>
auto make_nodo(Args&&... args) -> decltype(make_pair(std::forward<Args>(args)...)) {
  return make_pair(std::forward<Args>(args)...);
}

template <typename... Args>
auto make_vecino(Args&&... args) -> decltype(make_pair(std::forward<Args>(args)...)) {
  return make_pair(std::forward<Args>(args)...);
}
*/

int dist_camino_minimo_dijkstra(nodo n1, nodo n2){
	
}

void resolver(int* grafoOriginal, unsigned n, unsigned origen, unsigned destino, unsigned k){

	int (*G)[n] = (int (*)[n]) grafoOriginal;

	listaAdyacencia<vecino> grafo(n*(k+1), false);
	
	for(unsigned i = 0; i < n*(k+1); i++){
		
		unsigned c1 = (unsigned)(i / (k + 1));
		unsigned p1 = i % (k+1);
		for(unsigned j = 0; j < n*(k+1); j++){
						
			unsigned c2 = (unsigned)(j / (k + 1));
			unsigned p2 = j % (k+1);


			if(c1 == c2 && p1 < p2){
				grafo.agregarVecino(i, make_vecino(make_nodo(c2, p2), 0));
			}
			else{
				int distancia = G[c1][c2];
				if (distancia == 0) continue; //si las ciudades no estan conectadas, nada que hacer
				bool esRutaPremium = (distancia < 0);

				if((p2 == (p1 + 1) && esRutaPremium) || (p1 == p2 && !esRutaPremium)){ //<- ya sabemos que las ciudades están conectadas!
					grafo.agregarVecino(i, make_vecino(make_nodo(c2, p2), abs(distancia)));
				}

			}
		}
	}

	/*
		El nodo (origen, 0)  se corresponde con la ciudad de origen, sin haber usando ninguna ruta premium
		El nodo (destino, k) se corresponde con la ciudad de destino, habiendo usado a lo sumo k rutas premium.
	*/
	return dist_camino_minimo_dijkstra(make_nodo(0, 0), make_nodo(n-1, k));
}

int main(int argc, char** argv){

/*
	grafo[10] = 2;
	int (*grafoT)[10] = (int (*)[10]) grafo;


	cout << "gt: " << grafoT[1][0] << endl;
	delete grafo;
	return 0;
*/

	unsigned n, m, origen, destino, k;
	stringTokenizer strTok;
	string linea;

	fstream input(argv[1], fstream::in);
	
	//primera linea del archivo (n y m)
	getline(input, linea);
	strTok.tokenize(linea, ' ');
	n = stoi(strTok[0]);
	m = stoi(strTok[1]);

	int* grafo = new int[n*n];
	for(int i = 0; i < n*n; i++)//O(n^2)
		grafo[i] = 0;

	//segunda linea del archivo (origen, destino, k)
	getline(input, linea);
	strTok.tokenize(linea, ' ');
	origen = stoi(strTok[0]);
	destino = stoi(strTok[1]);
	k = stoi(strTok[2]);

	for(int i = 0; i < m; i++){

		int c1, c2, d;
		bool p;

		getline(input, linea);
		strTok.tokenize(linea, ' ');
		c1 = stoi(strTok[0]);
		c2 = stoi(strTok[1]);
		p = stoi(strTok[2]);
		d = stoi(strTok[3]);

		//Representación: distancia negativa es ruta premium, distancia positiva es ruta normal. 
		//Es un grafo normal, por lo tanto la matriz es simétrica.
		grafo[(c1-1)*n + (c2-1)] = d*pow(-1, p); 
		grafo[(c2-1)*n + (c1-1)] = d*pow(-1, p); 
	}

	getline(input, linea);

	resolver(grafo, n, origen - 1, destino - 1, k); //En el grafo las ciudades se indexaron en el rango [0, n)
	input.close();

	delete[] grafo;
	return 0;

}

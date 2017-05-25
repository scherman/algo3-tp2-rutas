#include <iostream>
#include <fstream>
#include <math.h>

#include "listaAdyacencia.hpp"
#include "stringTokenizer.hpp"

using namespace std;

//Nodo: Tupla(ciudad, k)
typedef pair<unsigned, unsigned> nodo;
#define make_nodo make_pair

//Vecino: Tupla(Nodo, d)  donde d es la distancia entre vecinos
typedef pair <nodo, int> vecino;
#define make_vecino make_pair


inline unsigned idNodo(nodo n, unsigned k){
	unsigned p = (k != 0) ? (k+1) : 1;
	return (n.first*p + n.second);
}


//Cola de prioridad para el algo de dijkstra.
//Matiene hasta cantElementos elementos y a partir de ahí decrece. Todos los elementos son inicializados con prioridad infinita. 
class colaPrioArray{

private:

	vector<int> _elementos;
	vector<bool> _extraido;
	unsigned _cantExtraidos;
	const int _INF_;

public:

	colaPrioArray(unsigned cantElementos):
		_elementos(cantElementos),
		_extraido(cantElementos),
		_cantExtraidos(0),
		_INF_(-1){

		for(unsigned i = 0; i < _elementos.size(); i++){
			_elementos[i] = _INF_;
			_extraido[i] = false;			
		}

	}

	void actualizarPrio(unsigned elemento, int prioridad){
		_elementos[elemento] = prioridad;
	}

	//pre: existe un mínimo
	unsigned extraerMin(){
		int min = _INF_;
		unsigned indice;
		for(unsigned i = 0; i < _elementos.size(); i++){
			int v = _elementos[i];
			if(v != _INF_ && !_extraido[i]){
				if(min == _INF_ || v < min){
					min = v;
					indice = i;	
				} 
			}
		}
		_extraido[indice] = true;
		_cantExtraidos++;
		return indice;
	}

	bool empty(){
		return _elementos.size() == _cantExtraidos;
	}

};

int dist_camino_minimo_dijkstra(nodo n1, nodo n2, listaAdyacencia<vecino> grafo, unsigned k){

	const int _INF_ = -1; //Infinito!
	vector<int> distancia(grafo.cantNodos(), _INF_); 	//O(n)
	colaPrioArray cola(grafo.cantNodos());				//O(n)

	unsigned origen = idNodo(n1, k);
	unsigned destino = idNodo(n2, k);
	distancia[origen] = 0;
	cola.actualizarPrio(origen, 0);
	
	while(!cola.empty()){
		unsigned p = cola.extraerMin();
		for(vecino v : grafo.vecinos(p)){
			unsigned q = idNodo(v.first, k);
			unsigned costo = v.second;
			if(distancia[q] == _INF_ || distancia[q] > distancia[p] + costo){
				distancia[q] = distancia[p] + costo;
			}
			cola.actualizarPrio(q, distancia[q]);
		}
	}

	return distancia[destino];

}

int resolver(int* grafoOriginal, unsigned n, unsigned origen, unsigned destino, unsigned k){

	int (*G)[n] = (int (*)[n]) grafoOriginal;

	listaAdyacencia<vecino> grafo(n*(k+1), false);
	
	for(unsigned i = 0; i < n*(k+1); i++){ //O(n*(k+1)) iteraciones
		
		unsigned c1 = (unsigned)(i / (k + 1));
		unsigned p1 = i % (k+1);
		for(unsigned j = 0; j < n*(k+1); j++){ //O(n*(k+1)) iteraciones
						
			unsigned c2 = (unsigned)(j / (k + 1));
			unsigned p2 = j % (k+1);


			if(c1 == c2 && p1 < p2){
				//Dados i, j (i < j), y una ciudad c,  si se puede llegar a c usando a lo sumo i rutas premium,
				//entonces también se puede llegar a c usando a lo sumo j rutas premium
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
	
	//El nodo (origen, 0)  se corresponde con la ciudad de origen, sin haber usando ninguna ruta premium
	//El nodo (destino, k) se corresponde con la ciudad de destino, habiendo usado a lo sumo k rutas premium.
	return dist_camino_minimo_dijkstra(make_nodo(0, 0), make_nodo(n-1, k), grafo, k);
}

int main(int argc, char** argv){

	unsigned n, m, origen, destino, k;
	stringTokenizer strTok;
	string linea;

	fstream input(argv[1], fstream::in); //Asumimos que siempre podemos leer el archivo
	
	//primera linea del archivo (n y m)
	while(getline(input, linea)){
		if(linea == "-1 -1") continue;
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

		cout << resolver(grafo, n, origen - 1, destino - 1, k) << endl; //En el grafo las ciudades se indexaron en el rango [0, n)
		delete[] grafo;
	}	
	input.close();
	return 0;

}

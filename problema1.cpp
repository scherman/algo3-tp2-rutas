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

inline nodo nodoFromId(unsigned id, unsigned k){
	unsigned k0 = (k != 0) ? (k+1) : 1;
	unsigned p  = (k != 0) ? (id % k0) : 0;
	return make_nodo((int)(id / k0), p);
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
		bool a = false;
		for(unsigned i = 0; i < _elementos.size(); i++){
			int v = _elementos[i];
			if(v != _INF_ && !_extraido[i]){
				if(min == _INF_ || v < min){
					min = v;
					indice = i;	
					a = true;
				} 
			}
		}
		_extraido[indice] = true;
		_cantExtraidos++;

		return indice;
	}

	bool empty(){
		return (_elementos.size() == _cantExtraidos);
	}

};

int dist_camino_minimo_dijkstra(const nodo& n1, const nodo& n2, const listaAdyacencia<vecino>& grafo, unsigned k){

	const int _INF_ = -1; //Infinito!
	vector<int> distancia(grafo.cantNodos(), _INF_); 	//O(n*(k+1))
	colaPrioArray cola(grafo.cantNodos());				//O(n*(k+1))

	unsigned origen = idNodo(n1, k);
	unsigned destino = idNodo(n2, k);
	distancia[origen] = 0;
	cola.actualizarPrio(origen, 0);
	bool destinoVisitado = false;

	while(!cola.empty()){
		
		unsigned p = cola.extraerMin();
		nodo n = nodoFromId(p, k);
		if(n.first == n2.first){
			cout << "corte\n";
			return distancia[p];
		}
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

int resolver(const listaAdyacencia<pair<unsigned, int>>& grafoEntrada, unsigned n, unsigned origen, unsigned destino, unsigned k){

	listaAdyacencia<vecino> grafo(n*(k+1), false);

	for(unsigned i = 0; i < grafoEntrada.cantNodos(); i++){
		for(auto v : grafoEntrada.vecinos(i)){
			bool esRutaPremium = (v.second < 0);
			for(unsigned p = 0; p <= k; p++){
				auto id = idNodo(make_nodo(i, p), k);
				if(esRutaPremium && p!=k){
					nodo nodoVecino = make_nodo(v.first, p+1);
					grafo.agregarVecino(id, make_vecino(nodoVecino, abs(v.second)));
				}
				else if(!esRutaPremium){
					nodo nodoVecino = make_nodo(v.first, p);
					grafo.agregarVecino(id, make_vecino(nodoVecino, abs(v.second)));
				}
			}
		}
	}

	//El nodo (origen, 0)  se corresponde con la ciudad de origen, sin haber usando ninguna ruta premium
	//El nodo (destino, k) se corresponde con la ciudad de destino, habiendo usado a lo sumo k rutas premium.
	return dist_camino_minimo_dijkstra(make_nodo(origen, 0), make_nodo(destino, k), grafo, k);
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

		listaAdyacencia<pair<unsigned, int>> grafo(n, false);

		//segunda linea del archivo (origen, destino, k)
		getline(input, linea);
		strTok.tokenize(linea, ' ');
		origen = stoi(strTok[0]) - 1;
		destino = stoi(strTok[1]) - 1;
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
			grafo.agregarVecino(c1-1, make_pair(c2-1, d*pow(-1, p))); 
			grafo.agregarVecino(c2-1, make_pair(c1-1, d*pow(-1, p))); 
		}

		cout << resolver(grafo, n, origen, destino, k) << endl; //En el grafo las ciudades se indexaron en el rango [0, n)
	}	
	input.close();
	return 0;

}

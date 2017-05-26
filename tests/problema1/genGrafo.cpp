#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <stdlib.h>

using namespace std;

//Uso: genGrafo [n] [m] [p] [n0] [n1] [k] 
//Output: Una instancia del problema 1 con un grafo conexo aleatorio de n vertices, m aristas y p rutas premium, 
//			con n0 origen, n1 destino y k el max de rutas premium que se pueden usar.
//			Si m no es suficientemente grande (< n-1) se expandirá para que el grafo sea conexo. Si es más grande de lo posible (> n*(n-1)/2) será comprimido.
//			Las distancias se elegirán aleatoriamente entre 0 y 100.
//			Si p supera a las aristas disponibles todas las aristas serán usadas.
//
//Ejemplo: genGrafo 3 1 1 1 3 0  genera un grafo conexco de 3 vertices, 2 rutas (m fue expandido), 1 ruta premium, 
//			y se quiere ir la ciudad 1 a la 3 usando 0 rutas premium
int main(int argc, char** argv){

	unsigned n 	= stoi(argv[1]), 
			 m 	= stoi(argv[2]),
			 p 	= stoi(argv[3]),
			 n0 = stoi(argv[4]),
			 n1 = stoi(argv[5]),
			 k 	= stoi(argv[6]);
	
	int* grafo = new int[n*n];
	int (*G)[n] = (int (*)[n]) grafo;

	set<int> nodos, usados;
	for(unsigned i = 0; i < n; i++) {
		nodos.insert(i);
		for(unsigned j = 0; j < n; j++) G[i][j] = 0;
	}

	auto it = nodos.begin();
	advance(it, rand() % nodos.size()); //Obtener un nodo aleatoriamente
	int nodoActual = *it;

	nodos.erase(nodoActual);
	usados.insert(nodoActual);
	unsigned aristasTotales = 0;

	while(!nodos.empty()){
		auto it = nodos.begin();
		advance(it, rand() % nodos.size()); //Obtener un nodo aleatoriamente
		int vecino = *it;
		G[nodoActual][vecino] = (rand() % 100);
		G[vecino][nodoActual] = G[nodoActual][vecino];
		aristasTotales++;

		nodos.erase(vecino);
		usados.insert(vecino);
		nodoActual = vecino;
	}

	//Agregar las aristas que falten
	m = min(m, (unsigned)(n*(n-1)/2));
	while(aristasTotales < m){
		if(nodos.empty()) nodos = usados;

		auto it = nodos.begin();
		advance(it, rand() % nodos.size());
		unsigned nodo1 = *it;
		nodos.erase(nodo1);

		vector<int> vecinos;
		for(unsigned i = 0; i < n; i++) if(i != nodo1) vecinos.push_back(i);
		bool encontrado = false;

		while(!encontrado && !vecinos.empty()){
			unsigned idxVecino = rand() % vecinos.size();
			unsigned nodo2 = vecinos[idxVecino];
			if(G[nodo1][nodo2] == 0){
				G[nodo1][nodo2] = (rand() % 100);
				G[nodo2][nodo1] = G[nodo1][nodo2];
				aristasTotales++;
				encontrado = true;
			}
			vecinos[idxVecino] = vecinos[vecinos.size() - 1];
			vecinos.pop_back();
		}
	}

	bool simetrico = true;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			simetrico == simetrico && (G[i][j] == G[j][i]);

	//Agregar rutas premium
	int premiumTotales = 0;
	p = min(p, aristasTotales);
	nodos = usados;

	while(premiumTotales < p){

		if(nodos.empty()) nodos = usados;
		
		auto it = nodos.begin();
		advance(it, rand() % nodos.size());
		unsigned nodo1 = *it;
		nodos.erase(nodo1);

		vector<int> vecinos(n-1);
		for(unsigned i = 0; i < n; i++) if(i != nodo1) vecinos.push_back(i);
		bool encontrado = false;

		while(!encontrado && !vecinos.empty()){
			unsigned idxVecino = rand() % vecinos.size();
			unsigned nodo2 = vecinos[idxVecino];
			if(G[nodo1][nodo2] > 0){
				G[nodo1][nodo2] = G[nodo1][nodo2]*(-1);
				G[nodo2][nodo1] = G[nodo2][nodo1]*(-1);
				premiumTotales++;
				encontrado = true;
			}
			vecinos[idxVecino] = vecinos[vecinos.size() - 1];
			vecinos.pop_back();
		}

	}

	//Imprimir formato de salida
	printf("%d %d\n", n, aristasTotales);
	printf("%d %d %d\n", n0, n1, k);
	for(unsigned i = 0; i < n; i++){
		for(unsigned j = 0; j < n; j++){
			if(G[i][j] == 0) continue;
			int premium = (G[i][j] < 0);
			printf("%d %d %d %d\n", i+1, j+1, premium, abs(G[i][j]));
			//Eliminar elemento simétrico
			G[j][i] = 0;
		}
	}
	printf("-1 -1\n");
	delete[] grafo;
	return 0;

}
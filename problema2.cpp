#include <vector>
#include <utility>
#include <iostream>
#include <limits>
#include <math.h>

#include "listaAdyacencia.hpp"
#include "stringTokenizer.hpp"

using namespace std;

bool tiene_ciclos_negativos(vector< vector<int> > v, int n, int c){
    int infinito = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++){ //resta c a cada peaje
        for (int j = 0; j < n; j++) {
            if (i != j && v[i][j] != infinito) {
                v[i][j] = v[i][j] - c;
            }
        }
    }
    //Algoritmo de Dantzing completo
    bool b = true;
    for(int k = 0; k < n-1; k++){
        for (int i = 0; i < k; i++){
            int minimo = v[i][0] + v[0][k];
            for (int j = 0; j < k; j++) {
                if (v[k][i] + v[i][k] < minimo){
                    minimo = v[i][j] + v[j][k+1];
                }
            }
            v[i][k+1] = minimo;
            minimo = v[k][0] + v[0][i];
            for (int j = 0; j < k; j++) {
                if (v[k][i] + v[i][k] < minimo){
                    minimo = v[k][j] + v[j][i];
                }
            }
            v[k+1][i] = minimo;
        }
        int minimo = v[k][0] + v[0][k];
        for (int i = 0; i < k; i++) {
            if (v[k][i] + v[i][k] < minimo){
                minimo = v[k][i] + v[i][k];
            }
        }
        if (minimo < 0){
            b = false;
        }

        for (int i = 0; i < k; i++){
            for (int j = 0; j < k; j++) {
                v[i][j] = min(v[i][j],v[i][k+1]+v[k+1][j]);
            }
        }
    }
    return b;
}

bool tiene_ciclos_negativos_Version2(vector< vector<int> > v, int n, int c){
    int infinito = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++){ //resta c a cada peaje
        for (int j = 0; j < n; j++) {
            if (i != j && v[i][j] != infinito) {
                v[i][j] = v[i][j] - c;
            }
        }
    }
    //Algoritmo de Dantzing (solo detectar ciclo negativo?)
    bool b = true;
    for(int k = 0; k < n; k++){
        int minimo = 0;
        for (int i = 0; i < k; i++) {
            if (v[k+1][i] + v[i][k+1] < minimo){
                minimo = v[k+1][i] + v[i][k+1];
            }
        }
        if (minimo < 0){
            b = false;
        }
    }
    return b;
}

int problema_dos(vector< vector<int> > v, int n, int c) {
    int j = c;
    int i = 0;
    bool b;
    int centro;
    while (i <= j) { //busqueda binaria
        centro = (j+i)/2;
        b = tiene_ciclos_negativos(v,n,centro);
        if (b == false) {
            j = centro - 1;
        } else {
            i = centro + 1;
        }
    }
    return centro;
}

int main(int argc, char** argv){
	unsigned n, m;
	stringTokenizer strTok;
	string linea;
    int infinito = std::numeric_limits<int>::max();
	fstream input(argv[1], fstream::in);
	while(getline(input, linea)){
		if(linea == "-1 -1") continue;
		strTok.tokenize(linea, ' ');
		n = stoi(strTok[0]);
		m = stoi(strTok[1]);
		vector< vector<int> > v (n, vector<int>(n));
		for(int i = 0; i < n; i++){ //O(n^2)
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    v[i][j] = 0;
                } else {
                    v[i][j] = infinito;
                }
            }
		}
		int c = 0;
		for(int i = 0; i < m; i++){
			int c1, c2, p;
			getline(input, linea);
			strTok.tokenize(linea, ' ');
			c1 = stoi(strTok[0]);
			c2 = stoi(strTok[1]);
			p = stoi(strTok[2]);
			v[c1][c2] = p;
			if (p > c) {
                c = p;
			}
		}
		cout << problema_dos(v, n, c) << endl;
	}
	input.close();
}

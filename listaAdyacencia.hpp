#include <vector>
#include <list>


using namespace std;

/*
*	Representación de un grafo como lista de adyacencia.
*	TP2 - Algoritmos y Estructuras de Datos 3 - FCEN - UBA
*/

template<typename T>
class listaAdyacencia{

private:

	vector<list<T>> _nodos;
	bool _indexadoEnUno;

public:

	/*
	*cantNodos (unsigned): cantidad de nodos del grafo
	*indexadoEnUno (bool): indica si los nodos de numeran en el rango [0, cantNodos) o en [1, cantNodos]
	*/
	listaAdyacencia(unsigned cantNodos, bool indexadoEnUno):
		 _nodos(cantNodos, list<T>()),
		 _indexadoEnUno(indexadoEnUno){
	}

	/*
	*	Agrega a dato como un vecino de nodo (esto es, dato es adyacente a nodo)
	*/
	void agregarVecino(unsigned nodo, T dato){
		unsigned numNodo = nodo - _indexadoEnUno*1;
		_nodos[numNodo].push_back(dato);
	}

	const list<T>& vecinos(unsigned nodo) const{
		unsigned numNodo = nodo - _indexadoEnUno*1;
		return _nodos[numNodo];
	}

	size_t cantNodos() const{
		return _nodos.size();
	}
};
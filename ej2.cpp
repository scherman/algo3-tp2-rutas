// A C / C++ program for Bellman-Ford's single source 
// shortest path algorithm.
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <iostream>

using namespace std;

// estructura para representar ejes con pesos
struct Edge
{
    int src, dest, weight;
};
 
// structura para representar un grafo dirigido y con pesos.
struct Graph
{
    // V-> Numero de vertices, E-> Numero de ejes
    int V, E;
 
    // represento al grafo como un aarreglo de ejes.
    struct Edge* edge;
};
 
// Creo el Grafo con V vertices y E ejes.
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = 
         (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = 
       (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
 
// Funcion para imprimir la solucion
void printArr(int dist[], int n)
{
    printf("Costo del Vertice i al Vertice src\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// BellmanFord nos da el camino minimo desde src, source, a todos los nodos del Grafo graph.
// Ademas detecta si el grafo tiene ciclos negativos, devolviendo true si lo hay.
bool hayCicloNegativo(struct Graph* graph, int src, int subsidio)
{
    bool hasNegativeCycles = false;
    int V = graph->V;
    int E = graph->E;
    int dist[V];
 
    // Inicializo los costos de cada eje como INFINITO
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
 
    //relajo todas las aristas |V|-1 veces. Ya que un camino minimo simple
    // de un vertice a cualquier otro puede tener a lo sumo |V| -1 ejes.
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = (graph->edge[j].weight) - subsidio;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    // Chequeo si hay ciclos con costos negativos.

    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = (graph->edge[i].weight) - subsidio;
        int a = weight + dist[u] - dist[v];
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
            cout << "Tiene ciclos engativos" <<endl;
            hasNegativeCycles = true;
        }
    }
 
    printArr(dist, V);
 
    return hasNegativeCycles;
}

int peajeMaximo(struct Graph* graph){
    int ejeMaximo = 0;
    for(int i = 0; i < graph->E; i++){
        if(graph->edge[i].weight > ejeMaximo){
            ejeMaximo = graph->edge[i].weight;
        }
    }
    return ejeMaximo;
}

int subsidiandoRutas(struct Graph* graph, int src) {
    int c = peajeMaximo(graph);
    int a = 0;
    while (c != a) {
        if (hayCicloNegativo(graph, src, (a + c) / 2)) {
            if (c == (a + c) / 2) return c;
            c = (a + c) / 2;
        }
        else {
            if (a == (a + c) / 2) return a;
            a = (a + c) / 2;
        }
        if (a == c) return a;
    }
}
 
int main() {
    /* Let us create the graph given in above example */
    int V = 5;  // Number of vertices in graph
    int E = 9;  // Number of edges in graph
    struct Graph *graph = createGraph(V, E);
    int C = 0;
    // add edge 0-1 (or A-B in above figure)
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 2;

    // add edge 2-0 (or A-E in above figure)
    graph->edge[8].src = 2;
    graph->edge[8].dest = 0;
    graph->edge[8].weight = 3;

    // add edge 1-2 (or B-C in above figure)
    graph->edge[2].src = 1;
    graph->edge[2].dest = 2;
    graph->edge[2].weight = 4;

    // add edge 0-2 (or A-C in above figure)
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 4;
    // add edge 1-3 (or B-D in above figure)
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 14;

    // add edge 1-4 (or A-E in above figure)
    graph->edge[4].src = 1;
    graph->edge[4].dest = 4;
    graph->edge[4].weight = 14;

    // add edge 3-2 (or D-C in above figure)
    graph->edge[5].src = 3;
    graph->edge[5].dest = 2;
    graph->edge[5].weight = 14;

    // add edge 3-1 (or D-B in above figure)
    graph->edge[6].src = 3;
    graph->edge[6].dest = 1;
    graph->edge[6].weight = 14;

    // add edge 4-3 (or E-D in above figure)
    graph->edge[7].src = 4;
    graph->edge[7].dest = 3;
    graph->edge[7].weight = 14;

    //cout << "hay ciclo negativo?: " << hayCicloNegativo(graph, 0, 17) << endl;
    cout << "El maximo subsidio posble es: " << subsidiandoRutas(graph, 0) << endl;
    return 0;
}

//Consideraciones de la solucion al problema2
//Los costos asignados a las rutas son positivos en un principio, al restarle C pueden pasar a ser negativos.
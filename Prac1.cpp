#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6 // Número de nodos en el grafo
#define INF INT_MAX // Valor infinito para representar la distancia

// Función para encontrar el nodo con la distancia mínima que no ha sido procesado aún
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Función para imprimir las distancias más cortas desde el nodo de origen
void printSolution(int dist[]) {
    printf("Nodo \t Distancia desde el origen\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

// Función para implementar el algoritmo de Dijkstra
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Arreglo para almacenar las distancias más cortas desde el origen
    int visited[V]; // Arreglo para rastrear los nodos visitados

    // Inicializar todas las distancias como infinito y todos los nodos como no visitados
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    // La distancia desde el nodo de origen hacia sí mismo siempre es 0
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprimir las distancias más cortas desde el nodo de origen
    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int source = 0; // Nodo de origen

    dijkstra(graph, source);

    return 0;
}

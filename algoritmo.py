import random

# Definir el número de nodos en el grafo
num_nodos = 5

# Crear una matriz de adyacencia para representar el grafo
grafo = [[0 if i == j else float('inf') for j in range(num_nodos)] for i in range(num_nodos)]

# Generar retrasos aleatorios entre 1 y 1000 para las conexiones
for i in range(num_nodos):
    for j in range(i + 1, num_nodos):
        retraso = random.randint(1, 1000)
        grafo[i][j] = retraso
        grafo[j][i] = retraso

# Algoritmo de rutas más cortas (por ejemplo, Dijkstra)
def dijkstra(grafo, inicio):
    # Implementa aquí el algoritmo de Dijkstra
    pass

# Calcula las rutas más cortas desde el nodo 0 a todos los demás nodos
rutas_cortas = dijkstra(grafo, 0)

# Imprime los resultados
for nodo, retraso in enumerate(rutas_cortas):
    print(f"Retraso desde el nodo 0 hasta el nodo {nodo}: {retraso}")

//
// Created by Guillermo Galvez on 11/02/2025.
//

#include "GraphSTL.h"
int main() {
    // Creamos un grafo no dirigido y ponderado.
    GraphSTL<string, int> g(false, true);

    g.addEdge("A", "B", 5);
    g.addEdge("A", "C", 3);
    g.addEdge("B", "D", 2);
    g.addEdge("C", "D", 4);
    g.addEdge("D", "E", 1);

    cout << "Representación del grafo (lista de adyacencia):\n";
    g.printGraph();

    cout << "\nDFS desde el vértice A:\n";
    g.DFS("A");

    cout << "\nBFS desde el vértice A:\n";
    g.BFS("A");

    return 0;
}
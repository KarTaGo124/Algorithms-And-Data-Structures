#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    // Grafo no dirigido sin pesos
    Graph<string> g;
    g.addEdge("A", "B");
    g.addEdge("A", "C");
    g.addEdge("B", "D");
    g.addEdge("C", "D");

    cout << "Grafo no dirigido sin pesos:\n";
    g.printGraph();

    // Grafo dirigido con pesos tipo double
    Graph<int, double> g2(true, true);
    g2.addEdge(1, 2, 2.5);
    g2.addEdge(1, 3, 3.1);
    g2.addEdge(2, 4, 1.8);
    g2.addEdge(3, 4, 4.2);

    cout << "\nGrafo dirigido ponderado:\n";
    g2.printGraph();

    return 0;
}

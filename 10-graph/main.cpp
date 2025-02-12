#include "Graph.h"

int main() {
    Graph<string> g(true);

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addVertex("E");

    g.addEdge("A", "B");
    g.addEdge("A", "C");
    g.addEdge("B", "D");
    g.addEdge("C", "D");
    g.addEdge("D", "E");

    cout << "Grafo:" << endl;
    g.printGraph();
    cout << endl;

    cout << "Ejecutando DFS..." << endl;
    g.DFS();

    cout << "\nResultados del DFS:" << endl;
    g.printDFSInfo();

    return 0;
}

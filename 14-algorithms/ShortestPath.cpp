#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

#include "../9-heap/Heap.h"

const double INF = numeric_limits<double>::infinity();

// Structure to represent an edge
struct Edge {
    int destination;
    double weight;
};

// Graph class using adjacency list
class Graph {
private:
    int vertices;
    bool isDirected;
    vector<vector<Edge>> adjList;

public:
    explicit Graph(int v, bool directed = false) : vertices(v), isDirected(directed), adjList(v) {}

    void addEdge(int u, int v, double probability) {
        adjList[u].push_back({v, probability});
        if (!isDirected) {
            adjList[v].push_back({u, probability});
        }
    }

    [[nodiscard]] const vector<vector<Edge>>& getAdjList() const {
        return adjList;
    }

    [[nodiscard]] int getVertices() const {
        return vertices;
    }
};

// Common initialization for the algorithms
void InitializeSingleSource(vector<double>& d, vector<int>& pi, int s) {
    fill(d.begin(), d.end(), INF);
    fill(pi.begin(), pi.end(), -1);
    d[s] = 0;
}

// Relaxation operation
void Relax(int u, int v, double weight, vector<double>& d, vector<int>& pi) {
    if (d[v] > d[u] + weight) {
        d[v] = d[u] + weight;
        pi[v] = u;
    }
}

/*
 * Comparador para el heap.
 * En vez de comparar directamente el valor de u y v,
 * usamos d[u] y d[v], que son las distancias.
 *
 * Queremos un min-heap por distancia, así que devolvemos true
 * si d[u] < d[v].
 */
struct DistCompare {
    const vector<double>& dist;  // referencia a distancias
    DistCompare(const vector<double>& d) : dist(d) {}

    // Para un min-heap, retorna true si 'u' tiene distancia menor que 'v'
    bool operator()(int u, int v) const {
        return dist[u] < dist[v];
    }
};

// Dijkstra que usa solo enteros en el heap (los nodos),
// pero los compara según d[u].
void Dijkstra(const Graph& graph, int s) {
    int n = graph.getVertices();
    vector<double> d(n, INF);
    vector<int> pi(n, -1);
    vector<bool> visited(n, false);

    // Distancia al nodo inicial es 0
    d[s] = 0.0;

    // Creamos el comparador, pasándole la referencia al vector de distancias
    DistCompare comp(d);
    // Instanciamos el heap con ese comparador
    Heap<int, DistCompare> minHeap(comp);

    // Insertamos el nodo inicial
    minHeap.push(s);

    while (!minHeap.empty()) {
        // Extraemos el nodo u con la menor distancia (según DistCompare)
        int u = minHeap.pop();

        // Si ya fue visitado, lo ignoramos (posible duplicado en el heap)
        if (visited[u]) continue;
        visited[u] = true;

        // Relajamos las aristas que salen de u
        for (auto& edge : graph.getAdjList()[u]) {
            int v = edge.destination;
            double w = edge.weight;
            if (!visited[v] && d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pi[v] = u;
                // Insertamos de nuevo el nodo v en el heap
                // (si estaba antes, será un duplicado obsoleto)
                minHeap.push(v);
            }
        }
    }

    // Mostramos resultados
    for (int i = 0; i < n; ++i) {
        cout << "Distance to " << i << ": ";
        if (d[i] == INF) cout << -1 << "\n";
        else cout << d[i] << "\n";
    }
}

// Bellman-Ford algorithm (allows negative-weight edges)
bool BellmanFord(const Graph& graph, int s) {
    int n = graph.getVertices();
    vector<double> d(n);
    vector<int> pi(n);
    InitializeSingleSource(d, pi, s);

    for (int i = 1; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            for (const auto& edge : graph.getAdjList()[u]) {
                Relax(u, edge.destination, edge.weight, d, pi);
            }
        }
    }

    for (int u = 0; u < n; ++u) {
        for (const auto& edge : graph.getAdjList()[u]) {
            if (d[edge.destination] > d[u] + edge.weight) {
                cout << "Negative cycle detected" << endl;
                return false;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << "Distance to " << i << ": " << (d[i] == INF ? -1 : d[i]) << "\n";
    }
    return true;
}

void BFS(const Graph& graph, int s) {
    int n = graph.getVertices();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (const auto& edge : graph.getAdjList()[u]) {
            int v = edge.destination;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

int main() {
    int n = 5; // Number of nodes

    Graph graph(n);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 2, 1);
    graph.addEdge(3, 1, 3);
    graph.addEdge(3, 2, 9);
    graph.addEdge(3, 4, 2);
    graph.addEdge(2, 4, 4);

    cout << "Dijkstra from node 0:" << endl;
    Dijkstra(graph, 0);

    cout << "\nBellman-Ford from node 0:" << endl;
    BellmanFord(graph, 0);

    return 0;
}

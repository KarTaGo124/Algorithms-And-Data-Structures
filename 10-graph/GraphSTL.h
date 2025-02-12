//
// Created by Guillermo Galvez on 11/02/2025.
//

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_GRAPHSTL_H
#define ALGORITHMS_AND_DATA_STRUCTURES_GRAPHSTL_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

template <typename T, typename W = int>
class GraphSTL {
private:
    // La lista de adyacencia: cada vértice se asocia a un vector de pares (vecino, peso)
    unordered_map<T, vector<pair<T, W>>> adjList;
    bool directed; // true: grafo dirigido, false: grafo no dirigido
    bool weighted; // true: aristas ponderadas, false: no ponderadas (se ignora el peso)

public:
    // Constructor: por defecto, grafo no dirigido y no ponderado.
    GraphSTL(bool directed = false, bool weighted = false)
            : directed(directed), weighted(weighted) {}

    // Agrega un vértice al grafo.
    void addVertex(const T &vertex) {
        // Si el vértice no existe, se crea una entrada en la lista de adyacencia.
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = vector<pair<T, W>>();
        }
    }

    // Agrega una arista entre 'source' y 'destination'.
    // Si el grafo no es ponderado, se ignora el valor de 'weight' (se usa 1).
    void addEdge(const T &source, const T &destination, W weight = W(1)) {
        // Aseguramos que ambos vértices existan en el grafo.
        addVertex(source);
        addVertex(destination);

        if (!weighted) {
            weight = W(1);
        }

        // Se inserta la arista en la lista de adyacencia del vértice origen.
        adjList[source].push_back({destination, weight});

        // Si el grafo es no dirigido, se agrega también la arista en sentido inverso.
        if (!directed) {
            adjList[destination].push_back({source, weight});
        }
    }

    // Elimina una arista desde 'source' hacia 'destination'.
    void removeEdge(const T &source, const T &destination) {
        auto it = adjList.find(source);
        if (it != adjList.end()) {
            auto &neighbors = it->second;
            neighbors.erase(remove_if(neighbors.begin(), neighbors.end(),
                                      [&destination](const pair<T, W> &edge) {
                                          return edge.first == destination;
                                      }),
                            neighbors.end());
        }
        // Si el grafo es no dirigido, se elimina también la arista inversa.
        if (!directed) {
            auto it2 = adjList.find(destination);
            if (it2 != adjList.end()) {
                auto &neighbors2 = it2->second;
                neighbors2.erase(remove_if(neighbors2.begin(), neighbors2.end(),
                                           [&source](const pair<T, W> &edge) {
                                               return edge.first == source;
                                           }),
                                 neighbors2.end());
            }
        }
    }

    // Elimina un vértice y todas las aristas incidentes en él.
    void removeVertex(const T &vertex) {
        // Se elimina la entrada correspondiente al vértice.
        adjList.erase(vertex);

        // Se recorren todas las listas de adyacencia para eliminar aristas que tengan a 'vertex' como destino.
        for (auto &entry : adjList) {
            auto &neighbors = entry.second;
            neighbors.erase(remove_if(neighbors.begin(), neighbors.end(),
                                      [&vertex](const pair<T, W> &edge) {
                                          return edge.first == vertex;
                                      }),
                            neighbors.end());
        }
    }

    // Retorna un vector con todos los vértices del grafo.
    vector<T> getVertices() const {
        vector<T> vertices;
        for (const auto &entry : adjList) {
            vertices.push_back(entry.first);
        }
        return vertices;
    }

    // Retorna la lista de vecinos (junto con el peso) del vértice 'vertex'.
    const vector<pair<T, W>>& getNeighbors(const T &vertex) const {
        auto it = adjList.find(vertex);
        if (it == adjList.end()) {
            throw std::out_of_range("El vértice no se encontró en el grafo.");
        }
        return it->second;
    }

    // Imprime el grafo en forma de lista de adyacencia.
    void printGraph() const {
        for (const auto &entry : adjList) {
            cout << entry.first << " -> ";
            for (const auto &edge : entry.second) {
                cout << "(" << edge.first;
                if (weighted)
                    cout << ", " << edge.second;
                cout << ") ";
            }
            cout << "\n";
        }
    }

    // Recorrido en profundidad (DFS) de forma recursiva.
    void DFSUtil(const T &vertex, unordered_map<T, bool> &visited) const {
        visited[vertex] = true;
        cout << vertex << " ";
        auto it = adjList.find(vertex);
        if (it != adjList.end()) {
            for (const auto &edge : it->second) {
                if (!visited[edge.first]) {
                    DFSUtil(edge.first, visited);
                }
            }
        }
    }

    // Realiza un recorrido DFS a partir del vértice 'start'.
    void DFS(const T &start) const {
        unordered_map<T, bool> visited;
        for (const auto &entry : adjList) {
            visited[entry.first] = false;
        }
        DFSUtil(start, visited);
        cout << "\n";
    }

    // Realiza un recorrido en anchura (BFS) a partir del vértice 'start'.
    void BFS(const T &start) const {
        unordered_map<T, bool> visited;
        for (const auto &entry : adjList) {
            visited[entry.first] = false;
        }
        queue<T> q;
        visited[start] = true;
        q.push(start);
        while (!q.empty()) {
            T vertex = q.front();
            q.pop();
            cout << vertex << " ";
            auto it = adjList.find(vertex);
            if (it != adjList.end()) {
                for (const auto &edge : it->second) {
                    if (!visited[edge.first]) {
                        visited[edge.first] = true;
                        q.push(edge.first);
                    }
                }
            }
        }
        cout << "\n";
    }
};

#endif //ALGORITHMS_AND_DATA_STRUCTURES_GRAPHSTL_H

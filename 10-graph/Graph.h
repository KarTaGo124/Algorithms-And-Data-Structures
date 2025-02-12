#ifndef ALGORITHMS_AND_DATA_STRUCTURES_GRAPH_H
#define ALGORITHMS_AND_DATA_STRUCTURES_GRAPH_H

#include <iostream>
#include "../2-linked-list/ForwardList.h"
#include "../6-hash/Hash.h"

using namespace std;

// Estructura para representar una arista
template <typename T, typename W>
struct Edge {
    T destination;
    W weight;

    Edge(T dest, W w) : destination(dest), weight(w) {}
};

// Nodo del grafo
template <typename T, typename W>
struct GraphNode {
    T data;
    ForwardList<Edge<T, W>*> neighbors;  // Ahora usamos ForwardList en lugar de List

    GraphNode(T value) : data(value) {}
};

// Grafo genérico
template <typename T, typename W = int>
class Graph {
private:
    Hash<T, GraphNode<T, W>*> adjList;
    bool isDirected;
    bool isWeighted;

public:
    Graph(bool directed = false, bool weighted = false) : isDirected(directed), isWeighted(weighted) {}

    // Agregar un vértice
    void addVertex(T value) {
        if (!adjList.exists(value)) {
            adjList.put(value, new GraphNode<T, W>(value));
        }
    }

    // Agregar una arista con peso opcional
    void addEdge(T v1, T v2, W weight = 1) {
        addVertex(v1);
        addVertex(v2);

        GraphNode<T, W>* node1 = adjList[v1];
        node1->neighbors.push_back(new Edge<T, W>(v2, isWeighted ? weight : 1));

        if (!isDirected) {
            GraphNode<T, W>* node2 = adjList[v2];
            node2->neighbors.push_back(new Edge<T, W>(v1, isWeighted ? weight : 1));
        }
    }

    // Mostrar el grafo
    void printGraph() {
        vector<T> keys = adjList.getAllKeys();
        for (T key : keys) {
            cout << key << " -> ";
            GraphNode<T, W>* node = adjList[key];
            Node<Edge<T, W>*>* current = node->neighbors.getIterator();
            while (current != nullptr) {
                cout << "(" << current->data->destination;
                if (isWeighted) {
                    cout << ", " << current->data->weight;
                }
                cout << ") ";
                current = current->next;
            }
            cout << endl;
        }
    }

    // Destructor para liberar memoria
    ~Graph() {
        vector<T> keys = adjList.getAllKeys();
        for (T key : keys) {
            GraphNode<T, W>* node = adjList[key];
            Node<Edge<T, W>*>* current = node->neighbors.getIterator();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete node;
        }
    }
};

#endif // ALGORITHMS_AND_DATA_STRUCTURES_GRAPH_H

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_GRAPH_H
#define ALGORITHMS_AND_DATA_STRUCTURES_GRAPH_H

#include "../6-hash/Hash.h"

template <typename T, typename W>
struct Edge {
    T destination;
    W weight;

    Edge(T dest, W w) : destination(dest), weight(w) {}
};

template <typename T, typename W>
struct GraphNode {
    T data;
    ForwardList<Edge<T, W>*> neighbors;

    GraphNode(T value) : data(value) {}
};

template <typename T, typename W = int>
class Graph {
private:
    Hash<T, GraphNode<T, W>*> adjList;
    Hash<T, int> colors; // 0: Blanco, 1: Gris, 2: Negro
    Hash<T, int> discoveryTime;
    Hash<T, int> finishTime;
    Hash<T, T> parent;
    int time;
    bool isDirected;
    bool isWeighted;

    void DFSVisit(T u) {
        colors.put(u, 1); // Gris: visitado pero no finalizado
        time++;
        discoveryTime.put(u, time);

        GraphNode<T, W>* node = adjList.get(u);
        Node<Edge<T, W>*>* current = node->neighbors.getIterator();
        while (current != nullptr) {
            T v = current->data->destination;
            if (!colors.exists(v) || colors.get(v) == 0) {
                parent.put(v, u);
                DFSVisit(v);
            }
            current = current->next;
        }

        colors.put(u, 2); // Negro: finalizado
        time++;
        finishTime.put(u, time);
    }

public:
    Graph(bool directed = false, bool weighted = false) : isDirected(directed), isWeighted(weighted), time(0) {}

    void addVertex(T value) {
        if (!adjList.exists(value)) {
            adjList.put(value, new GraphNode<T, W>(value));
        }
    }

    void addEdge(T v1, T v2, W weight = 1) {
        addVertex(v1);
        addVertex(v2);

        GraphNode<T, W>* node1 = adjList.get(v1);
        node1->neighbors.push_back(new Edge<T, W>(v2, isWeighted ? weight : 1));

        if (!isDirected) {
            GraphNode<T, W>* node2 = adjList.get(v2);
            node2->neighbors.push_back(new Edge<T, W>(v1, isWeighted ? weight : 1));
        }
    }

    void initializeColors() {
        ForwardList<T> keys = adjList.getAllKeys();
        Node<T>* keyNode = keys.getIterator();
        while (keyNode != nullptr) {
            colors.put(keyNode->data, 0); // Blanco: No visitado
            parent.put(keyNode->data, T()); // Nil
            keyNode = keyNode->next;
        }
        time = 0;
    }

    void DFSFrom(T start) {
        if (!adjList.exists(start)) return;
        DFSVisit(start);
    }

    int getColor(T node) {
        return colors.exists(node) ? colors.get(node) : 0;
    }

    void DFS() {
        ForwardList<T> keys = adjList.getAllKeys();
        Node<T>* keyNode = keys.getIterator();
        while (keyNode != nullptr) {
            colors.put(keyNode->data, 0); // Inicialmente, todos los nodos son blancos
            parent.put(keyNode->data, T()); // nullptr
            keyNode = keyNode->next;
        }
        time = 0;
        keyNode = keys.getIterator();
        while (keyNode != nullptr) {
            if (colors.get(keyNode->data) == 0) {
                DFSVisit(keyNode->data);
            }
            keyNode = keyNode->next;
        }
    }

    void printDFSInfo() {
        cout << "Nodo | Descubrimiento | Finalización | Padre" << endl;
        cout << "--------------------------------------" << endl;
        ForwardList<T> keys = adjList.getAllKeys();
        Node<T>* keyNode = keys.getIterator();
        while (keyNode != nullptr) {
            T node = keyNode->data;
            cout << node << "\t " << discoveryTime.get(node) << "\t\t "
                 << finishTime.get(node) << "\t\t ";
            if (parent.get(node) == T())
                cout << "-";
            else
                cout << parent.get(node);
            cout << endl;
            keyNode = keyNode->next;
        }
    }

    void printGraph() {
        ForwardList<T> keys = adjList.getAllKeys();
        Node<T>* keyNode = keys.getIterator();
        while (keyNode != nullptr) {
            cout << keyNode->data << " -> ";
            GraphNode<T, W>* node = adjList.get(keyNode->data);
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
            keyNode = keyNode->next;
        }
    }

    ~Graph() {
        ForwardList<T> keys = adjList.getAllKeys();
        Node<T>* keyNode = keys.getIterator();
        while (keyNode != nullptr) {
            GraphNode<T, W>* node = adjList.get(keyNode->data);
            Node<Edge<T, W>*>* current = node->neighbors.getIterator();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete node;
            keyNode = keyNode->next;
        }
    }

    void DFSFromAlternative(T source, Hash<T, bool>& visited) {
        if (visited.exists(source) && visited.get(source)) return;
        visited.put(source, true);
        GraphNode<T, W>* node = adjList.get(source);
        Node<Edge<T, W>*>* current = node->neighbors.getIterator();
        while (current != nullptr) {
            DFSFromAlternative(current->data->destination, visited);
            current = current->next;
        }
    }

    void DFSAlternative(Hash<T, bool>& visited) {
        ForwardList<T> keys = adjList.getAllKeys();
        Node<T>* keyNode = keys.getIterator();
        while (keyNode != nullptr) {
            if (!visited.exists(keyNode->data) || !visited.get(keyNode->data)) {
                DFSVisitAlternative(keyNode->data, visited);
            }
            keyNode = keyNode->next;
        }
    }

    void DFSVisitAlternative(T node, Hash<T, bool>& visited) {
        visited.put(node, true); // Mark as visited
        GraphNode<T, W>* graphNode = adjList.get(node);
        Node<Edge<T, W>*>* current = graphNode->neighbors.getIterator();
        while (current != nullptr) {
            if (!visited.exists(current->data->destination) || !visited.get(current->data->destination)) {
                DFSVisitAlternative(current->data->destination, visited);
            }
            current = current->next;
        }
    }
};

#endif // ALGORITHMS_AND_DATA_STRUCTURES_GRAPH_H

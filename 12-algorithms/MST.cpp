//
// Created by Guillermo Galvez on 18/02/2025.
//

#include <iostream>
using namespace std;
#include "../11-disjoint-set/DisjointSet.h"
#include "Heap.h"

vector<vector<pair<int, int>>> kruskal(vector<vector<pair<int, int>>>& graph, int V) {
    DisjointSet ds(V);
    vector<vector<pair<int, int>>> mst(V);
    vector<tuple<int, int, int>> edges;

    for (int u = 0; u < V; ++u) {
        for (auto [v, w] : graph[u]) {
            if (u < v) { // Evitar duplicados en un grafo no dirigido
                edges.push_back({w, u, v});
            }
        }
    }

    sort(edges.begin(), edges.end());

    for (auto [w, u, v] : edges) {
        if (ds.findSet(u) != ds.findSet(v)) {
            mst[u].push_back({v, w});
            ds.unionSets(u, v);
        }
    }

    return mst;
}

vector<vector<int>> prim(vector<vector<pair<int, int>>>& graph, int V, int r) {
    vector<vector<int>> mst;
    vector<bool> inMST(V, false);
    Heap<pair<int, int>> minHeap(V); // MinHeap based on edge weight
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);

    key[r] = 0;
    for (int u = 0; u < V; ++u) {
        minHeap.pushOrUpdate({key[u], u});
    }

    while (!minHeap.empty()) {
        auto [weight, u] = minHeap.pop();
        if (inMST[u]) continue;

        inMST[u] = true;
        if (parent[u] != -1) {
            mst.push_back({parent[u], u});
        }

        for (auto [v, w] : graph[u]) {
            if (!inMST[v] && w < key[v]) {
                parent[v] = u;
                key[v] = w;
                minHeap.pushOrUpdate({key[v], v}); // Decrease-Key operation
            }
        }
    }

    return mst;
}

int main () {
    vector<vector<int>> edges = {
            {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5},
            {2, 4, 7}, {3, 4, 9}
    };

    int V = 5;
    int r = 0; // Root vertex
    vector<vector<pair<int, int>>> graph(V);

    // Example edges: {u, {v, weight}}


    for (auto edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph[u].push_back({v, w});
    }

    vector<vector<pair<int, int>>> kruskal_mst = kruskal(graph, 5);

    cout << "Aristas del árbol de expansión mínima:" << endl;
    for (int u = 0; u < V; ++u) {
        for (auto [v, w] : kruskal_mst[u]) {
            cout << u << " - " << v << " (" << w << ")\n";
        }
    }


    vector<vector<int>> mst = prim(graph, V, r);
    cout << "Aristas del árbol de expansión mínima (Prim):" << endl;
    for (auto arista : mst) {
        cout << arista[0] << " - " << arista[1] << endl;
    }

    return 0;
}

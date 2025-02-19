//
// Created by Guillermo Galvez on 18/02/2025.
//

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_KRUSKAL_H
#define ALGORITHMS_AND_DATA_STRUCTURES_KRUSKAL_H

#include "../11-disjoint-set/DisjointSet.h"

vector<vector<int>> kruskal(vector<vector<int>>& aristas, int V) {
    DisjointSet ds(V+1);
    vector<vector<int>> A;

    sort(aristas.begin(), aristas.end());
    for (auto arista : aristas) {
        int u = arista[0];
        int v = arista[1];
        if (ds.findSet(u) != ds.findSet(v)) {
            A.push_back({u, v});
            ds.unionSets(u, v);
        }
    }
    return A;
}


#endif //ALGORITHMS_AND_DATA_STRUCTURES_KRUSKAL_H

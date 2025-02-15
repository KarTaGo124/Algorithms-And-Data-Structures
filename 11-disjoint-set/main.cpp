//
// Created by Guillermo Galvez on 14/02/2025.
//

#include "DisjointSet.h"
#include <iostream>
int main() {
    DisjointSet ds(5);

    ds.unionSets(0, 2);
    ds.unionSets(4, 2);
    ds.unionSets(3, 1);

    for (int i = 0; i < 5; i++) {
        cout << "Parent of " << i << ": " << ds.findSet(i) << endl;
    }

    return 0;
}
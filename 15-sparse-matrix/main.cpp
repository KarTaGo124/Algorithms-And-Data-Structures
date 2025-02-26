#include <vector>
#include "SparseMatrix.h"

using namespace std;

int main() {
    SparseMatrix<int> matrix(9, 9);
    vector<vector<int>> cells = {{2,1,3},{2,2,5},{2,7,9},{3,7,5},{4,5,5},{4,9,22},{6,5,5},{7,2,5},{7,8,5},{9,9,5}};

    matrix.set(4,9,22);
    for (auto cell : cells) {
        // restamos 1 a los índices porque el usuario ingresa los índices desde 1 pero mi implementación es desde 0
        matrix.set(cell[0]-1, cell[1]-1, cell[2]);
    }

    matrix.display();

    return 0;
}

#include <vector>
#include "CircularSparseMatrix.h"

using namespace std;

int main() {
    int rows = 9, cols = 9;

    CircularSparseMatrix<int> matrix1(rows, cols);
    CircularSparseMatrix<int> matrix2(rows, cols);

    vector<vector<int>> cells1 = {
            {2, 3, 3}, {5, 1, 3}, {5, 4, 1}, {7, 4, 5}, {8, 1, 1}, {8, 6, 4}, {9, 3, 2}
    };

    vector<vector<int>> cells2 = {
            {2, 3, 4}, {5, 1, 2}, {5, 4 ,1}, {7, 4, 4}, {8, 1, 3}, {8, 6, 2}, {9, 3, 1}
    };

    for (const auto &cell : cells1) {
        matrix1.set(cell[0] - 1, cell[1] - 1, cell[2]);
    }

    for (const auto &cell : cells2) {
        matrix2.set(cell[0] - 1, cell[1] - 1, cell[2]);
    }

    cout << "Matrix 1:" << endl;
    matrix1.display();

    cout << "Matrix 2:" << endl;
    matrix2.display();

    CircularSparseMatrix<int> result = matrix1 + matrix2;

    cout << "Matrix 1 + Matrix 2:" << endl;
    result.display();

    return 0;
}
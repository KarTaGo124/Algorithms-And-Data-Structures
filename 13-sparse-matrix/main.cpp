
#include "SparseMatrix.h"

int main() {
    SparseMatrix<double> mat1(5, 5);
    SparseMatrix<double> mat2(5, 5);

    mat1.set(0, 1, 10);
    mat1.set(1, 2, 20);
    mat1.set(3, 4, 30);
    mat1.set(4, 0, 40);

    cout << "Matriz 1:" << endl;
    mat1.display();

    mat2.set(0, 0, 5);
    mat2.set(1, 2, 15);
    mat2.set(2, 3, 25);
    mat2.set(3, 4, 35);

    cout << "\nMatriz 2:" << endl;
    mat2.display();

    SparseMatrix<double> sum = mat1 + mat2;
    cout << "\nSuma de Matriz 1 y Matriz 2:" << endl;
    sum.display();

    SparseMatrix<double> scalar_mult = mat1 * 3.5;
    cout << "\nMatriz 1 multiplicada por 3:" << endl;
    scalar_mult.display();

    SparseMatrix<double> prod = mat1 * mat2;
    cout << "\nProducto de Matriz 1 y Matriz 2:" << endl;
    prod.display();

    return 0;
}

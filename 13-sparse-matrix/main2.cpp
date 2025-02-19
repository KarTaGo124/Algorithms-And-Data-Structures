#include <iostream>
#include "CircularSparseMatrix.h"

using namespace std;

int main() {
    // 1. Crear una matriz dispersa 3x3 y agregar elementos
    CircularSparseMatrix<int> mat1(3, 3);
    mat1.set(0, 0, 5);
    mat1.set(0, 2, 3);
    mat1.set(1, 1, 7);
    mat1.set(2, 0, -2);
    mat1.set(2, 2, 4);

    cout << "Matriz 1:" << endl;
    mat1.display();
    cout << endl;

    // 2. Acceder a elementos usando la sobrecarga del operador ()
    cout << "Elemento en (0,2) usando operator(): " << mat1(0, 2) << endl;
    cout << "Elemento en (1,0) usando operator(): " << mat1(1, 0) << " (debe ser 0)" << endl;
    cout << endl;

    // 3. Buscar elemento usando el método get
    cout << "Elemento en (1,1) usando get(): " << mat1.get(1, 1) << endl;
    cout << endl;

    // 4. Eliminar un elemento (por ejemplo, el de la posición (2,0))
    mat1.remove(2, 0);
    cout << "Matriz 1 después de eliminar el elemento en (2,0):" << endl;
    mat1.display();
    cout << endl;

    // 5. Crear una segunda matriz para realizar operaciones
    CircularSparseMatrix<int> mat2(3, 3);
    mat2.set(0, 0, 2);
    mat2.set(0, 2, 1);
    mat2.set(1, 1, 3);
    mat2.set(2, 0, 4);
    mat2.set(2, 2, -1);

    cout << "Matriz 2:" << endl;
    mat2.display();
    cout << endl;

    // 6. Comparar dos matrices
    if (mat1 == mat2) {
        cout << "La Matriz 1 y la Matriz 2 son iguales." << endl;
    } else {
        cout << "La Matriz 1 y la Matriz 2 son diferentes." << endl;
    }
    cout << endl;

    // 7. Sumar matrices
    CircularSparseMatrix<int> suma = mat1 + mat2;
    cout << "Suma (Matriz 1 + Matriz 2):" << endl;
    suma.display();
    cout << endl;

    // 8. Restar matrices
    CircularSparseMatrix<int> resta = mat1 - mat2;
    cout << "Resta (Matriz 1 - Matriz 2):" << endl;
    resta.display();
    cout << endl;

    // 9. Multiplicar matriz por un escalar
    CircularSparseMatrix<int> escalar = mat1 * 2;
    cout << "Multiplicación de Matriz 1 por 2:" << endl;
    escalar.display();
    cout << endl;

    // 10. Multiplicar dos matrices (las dos son 3x3)
    CircularSparseMatrix<int> mult = mat1 * mat2;
    cout << "Multiplicación (Matriz 1 * Matriz 2):" << endl;
    mult.display();
    cout << endl;

    // 11. Transponer una matriz
    CircularSparseMatrix<int> trans = mat1.transpose();
    cout << "Transpuesta de la Matriz 1:" << endl;
    trans.display();
    cout << endl;

    return 0;
}

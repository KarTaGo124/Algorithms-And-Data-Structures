#ifndef CIRCULAR_SPARSE_MATRIX_H
#define CIRCULAR_SPARSE_MATRIX_H

#include <iostream>

using namespace std;

struct Header {
    int index;
    Header *next;
    void *first;

    explicit Header(int idx) : index(idx), next(nullptr), first(nullptr) {}
};

template<typename T>
struct Element {
    int row, col;
    T value;
    void *next_row;
    void *next_col;

    Element(int r, int c, T val) : row(r), col(c), value(val), next_row(nullptr), next_col(nullptr) {}
};

template<typename T>
class CircularSparseMatrix {
private:
    int rows, cols;
    Header *row_heads;  // Cabeza de las filas
    Header *col_heads;  // Cabeza de las columnas

    void initializeHeaders() {
        // Inicializar las cabeceras de las filas (mantiene circularidad en filas)
        Header *prev_row = nullptr;
        for (int i = 0; i < rows; ++i) {
            auto new_row = new Header(i);
            if (!row_heads) {
                row_heads = new_row;
            } else {
                prev_row->next = new_row;
            }
            prev_row = new_row;
        }
        prev_row->next = row_heads;  // Aquí se conecta la última fila a la primera (circularidad)

        // Inicializar las cabeceras de las columnas (mantiene circularidad en columnas)
        Header *prev_col = nullptr;
        for (int i = 0; i < cols; ++i) {
            auto new_col = new Header(i);
            if (!col_heads) {
                col_heads = new_col;
            } else {
                prev_col->next = new_col;
            }
            prev_col = new_col;
        }
        prev_col->next = col_heads;  // Aquí se conecta la última columna a la primera (circularidad)
    }

public:
    CircularSparseMatrix(int r, int c) : rows(r), cols(c), row_heads(nullptr), col_heads(nullptr) {
        initializeHeaders();
    }

    void set(int row, int col, T value) {
        if (row >= rows || col >= cols || row < 0 || col < 0) {
            throw std::out_of_range("Índices fuera de rango");
        }
        if (value == T()) return;

        Element<T>* newElement = new Element<T>(row, col, value);

        // Insertar en la fila correspondiente
        Header* rowHeader = row_heads;
        while (rowHeader->index != row) rowHeader = rowHeader->next; // Circularidad de las filas

        Element<T>* prevRow = nullptr;
        Element<T>* currentRow = static_cast<Element<T>*>(rowHeader->first);
        while (currentRow && currentRow->col < col) {
            prevRow = currentRow;
            currentRow = static_cast<Element<T>*>(currentRow->next_row);
        }
        newElement->next_row = currentRow;
        if (prevRow) prevRow->next_row = newElement;
        else rowHeader->first = newElement;

        // Insertar en la columna correspondiente
        Header* colHeader = col_heads;
        while (colHeader->index != col) colHeader = colHeader->next; // Circularidad de las columnas

        Element<T>* prevCol = nullptr;
        Element<T>* currentCol = static_cast<Element<T>*>(colHeader->first);
        while (currentCol && currentCol->row < row) {
            prevCol = currentCol;
            currentCol = static_cast<Element<T>*>(currentCol->next_col);
        }
        newElement->next_col = currentCol;
        if (prevCol) prevCol->next_col = newElement;
        else colHeader->first = newElement;
    }

    T get(int row, int col) const {
        auto row_header = row_heads;
        while (row_header->index != row) row_header = row_header->next;  // Circularidad de las filas

        auto elem = static_cast<Element<T>*>(row_header->first);
        while (elem && elem->col < col) elem = static_cast<Element<T>*>(elem->next_row);

        return (elem && elem->col == col) ? elem->value : T();
    }

    void remove(int row, int col) {
        auto row_header = row_heads;
        while (row_header->index != row) row_header = row_header->next;  // Circularidad de las filas

        Element<T> *prev_row = nullptr;
        auto current_row = static_cast<Element<T>*>(row_header->first);
        while (current_row && current_row->col < col) {
            prev_row = current_row;
            current_row = static_cast<Element<T>*>(current_row->next_row);
        }
        if (!current_row || current_row->col != col) return;
        if (prev_row) prev_row->next_row = current_row->next_row;
        else row_header->first = current_row->next_row;

        auto col_header = col_heads;
        while (col_header->index != col) col_header = col_header->next;  // Circularidad de las columnas

        Element<T> *prev_col = nullptr;
        auto current_col = static_cast<Element<T>*>(col_header->first);
        while (current_col && current_col->row < row) {
            prev_col = current_col;
            current_col = static_cast<Element<T>*>(current_col->next_col);
        }
        if (prev_col) prev_col->next_col = current_col->next_col;
        else col_header->first = current_col->next_col;

        delete current_row;
    }

    void display() const {
        for (int i = 0; i < rows; ++i) {
            auto row = row_heads;
            while (row->index != i) row = row->next;  // Circularidad de las filas
            auto elem = static_cast<Element<T>*>(row->first);
            for (int j = 0; j < cols; ++j) {
                if (elem && elem->col == j) {
                    cout << elem->value << " ";
                    elem = static_cast<Element<T>*>(elem->next_row);
                } else {
                    cout << "0 ";
                }
            }
            cout << "\n";
        }
    }

    T operator()(int row, int col) const {
        return get(row, col);
    }

    bool operator==(const CircularSparseMatrix<T> &other) const {
        if (rows != other.rows || cols != other.cols) return false;

        for (auto row = row_heads; row; row = row->next) {
            for (auto elem = static_cast<Element<T>*>(row->first); elem; elem = static_cast<Element<T>*>(elem->next_row)) {
                if (elem->value != other.get(elem->row, elem->col)) return false;
            }
        }

        return true;
    }

    bool operator!=(const CircularSparseMatrix<T> &other) const {
        return !(*this == other);
    }

    CircularSparseMatrix<T> operator+(const CircularSparseMatrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Dimensiones incompatibles");
        CircularSparseMatrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.set(i, j, get(i, j) + other.get(i, j));
            }
        }
        return result;
    }

    CircularSparseMatrix<T> operator-(const CircularSparseMatrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Dimensiones incompatibles");
        CircularSparseMatrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.set(i, j, get(i, j) - other.get(i, j));
            }
        }
        return result;
    }

    CircularSparseMatrix<T> transpose() const {
        CircularSparseMatrix<T> result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.set(j, i, get(i, j));
            }
        }
        return result;
    }

    CircularSparseMatrix<T> operator*(const CircularSparseMatrix<T>& other) const {
        if (cols != other.rows) throw std::invalid_argument("Dimensiones incompatibles para la multiplicación");
        CircularSparseMatrix<T> result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                T sum = T();
                for (int k = 0; k < cols; ++k) {
                    sum += get(i, k) * other.get(k, j);
                }
                if (sum != T()) {
                    result.set(i, j, sum);
                }
            }
        }
        return result;
    }

    CircularSparseMatrix<T> operator*(const T& scalar) const {
        CircularSparseMatrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.set(i, j, get(i, j) * scalar);
            }
        }
        return result;
    }

    ~CircularSparseMatrix() {
        // Destrucción con circularidad: eliminar los elementos y liberar memoria
        for (int i = 0; i < rows; ++i) {
            Header* rowHeader = row_heads;
            row_heads = row_heads->next;
            Element<T>* elem = static_cast<Element<T>*>(rowHeader->first);
            while (elem) {
                Element<T>* next = static_cast<Element<T>*>(elem->next_row);
                delete elem;
                elem = next;
            }
            delete rowHeader;
        }
        for (int i = 0; i < cols; ++i) {
            Header* colHeader = col_heads;
            col_heads = col_heads->next;
            delete colHeader;
        }
    }
};

#endif // CIRCULAR_SPARSE_MATRIX_H

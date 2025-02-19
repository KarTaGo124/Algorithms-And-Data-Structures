#ifndef ALGORITHMS_AND_DATA_STRUCTURES_SPARSEMATRIX_H
#define ALGORITHMS_AND_DATA_STRUCTURES_SPARSEMATRIX_H

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
    Element<T> *next_row;
    Element<T> *next_col;

    Element(int r, int c, T val) : row(r), col(c), value(val), next_row(nullptr), next_col(nullptr) {}
};

template<typename T>
class SparseMatrix {
private:
    int rows, cols;
    Header *row_heads;
    Header *col_heads;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), row_heads(nullptr), col_heads(nullptr) {
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
    }

    ~SparseMatrix() {
        deleteMatrix();
    }

    void deleteMatrix() {
        auto row = row_heads;
        while (row) {
            auto elem = static_cast<Element<T>*>(row->first);
            while (elem) {
                auto temp = elem;
                elem = elem->next_row;
                delete temp;
            }
            auto tempRow = row;
            row = row->next;
            delete tempRow;
        }

        auto col = col_heads;
        while (col) {
            auto tempCol = col;
            col = col->next;
            delete tempCol;
        }
    }

    Header *findOrCreateHeader(Header *&header, int index) {
        Header *prev = nullptr;
        auto current = header;

        while (current && current->index < index) {
            prev = current;
            current = current->next;
        }

        if (current && current->index == index) {
            return current;
        }

        auto new_header = new Header(index);
        if (prev) {
            prev->next = new_header;
        } else {
            header = new_header;
        }
        new_header->next = current;

        return new_header;
    }

    void set(int row, int col, T value) {
        if (value == T()) return;  // Si el valor es cero del tipo T

        auto row_header = findOrCreateHeader(row_heads, row);
        auto col_header = findOrCreateHeader(col_heads, col);

        Element<T> *prev_row = nullptr;
        auto current_row = static_cast<Element<T>*>(row_header->first);

        while (current_row && current_row->col < col) {
            prev_row = current_row;
            current_row = current_row->next_row;
        }

        if (current_row && current_row->col == col) {
            current_row->value = value;
            return;
        }

        auto new_node = new Element<T>(row, col, value);

        if (prev_row) {
            new_node->next_row = prev_row->next_row;
            prev_row->next_row = new_node;
        } else {
            new_node->next_row = static_cast<Element<T>*>(row_header->first);
            row_header->first = new_node;
        }

        Element<T> *prev_col = nullptr;
        auto current_col = static_cast<Element<T>*>(col_header->first);
        while (current_col && current_col->row < row) {
            prev_col = current_col;
            current_col = current_col->next_col;
        }

        if (prev_col) {
            new_node->next_col = prev_col->next_col;
            prev_col->next_col = new_node;
        } else {
            new_node->next_col = static_cast<Element<T>*>(col_header->first);
            col_header->first = new_node;
        }
    }

    T get(int row, int col) const {
        auto row_header = row_heads;
        while (row_header && row_header->index < row) {
            row_header = row_header->next;
        }
        if (!row_header || row_header->index != row) return T();

        auto elem = static_cast<Element<T>*>(row_header->first);
        while (elem && elem->col < col) {
            elem = elem->next_row;
        }

        return (elem && elem->col == col) ? elem->value : T();
    }

    void remove(int row, int col) {
        auto row_header = row_heads;
        while (row_header && row_header->index < row) {
            row_header = row_header->next;
        }
        if (!row_header) return;

        Element<T> *prev_row = nullptr;
        auto current_row = static_cast<Element<T>*>(row_header->first);
        while (current_row && current_row->col < col) {
            prev_row = current_row;
            current_row = current_row->next_row;
        }

        if (!current_row || current_row->col != col) return;

        if (prev_row) {
            prev_row->next_row = current_row->next_row;
        } else {
            row_header->first = current_row->next_row;
        }

        auto col_header = col_heads;
        while (col_header && col_header->index < col) {
            col_header = col_header->next;
        }

        Element<T> *prev_col = nullptr;
        auto current_col = static_cast<Element<T>*>(col_header->first);
        while (current_col && current_col->row < row) {
            prev_col = current_col;
            current_col = current_col->next_col;
        }

        if (prev_col) {
            prev_col->next_col = current_col->next_col;
        } else {
            col_header->first = current_col->next_col;
        }

        delete current_row;
    }

    void display() const {
        for (int i = 0; i < rows; ++i) {
            auto row = row_heads;
            while (row && row->index < i) row = row->next;

            auto elem = static_cast<Element<T>*>(row ? row->first : nullptr);

            for (int j = 0; j < cols; ++j) {
                if (elem && elem->col == j) {
                    cout << elem->value << " ";
                    elem = elem->next_row;
                } else {
                    cout << T() << " ";
                }
            }
            cout << "\n";
        }
    }

    SparseMatrix<T> operator+(const SparseMatrix<T> &other) {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Las dimensiones de las matrices no coinciden");
        }

        SparseMatrix<T> result(rows, cols);

        for (auto row = row_heads; row; row = row->next) {
            for (auto elem = static_cast<Element<T>*>(row->first); elem; elem = elem->next_row) {
                result.set(elem->row, elem->col, elem->value);
            }
        }

        for (auto row = other.row_heads; row; row = row->next) {
            for (auto elem = static_cast<Element<T>*>(row->first); elem; elem = elem->next_row) {
                result.set(elem->row, elem->col, result.get(elem->row, elem->col) + elem->value);
            }
        }

        return result;
    }

    SparseMatrix<T> operator-(const SparseMatrix<T> &other) {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Las dimensiones de las matrices no coinciden");
        }

        SparseMatrix<T> result(rows, cols);

        for (auto row = row_heads; row; row = row->next) {
            for (auto elem = static_cast<Element<T>*>(row->first); elem; elem = elem->next_row) {
                result.set(elem->row, elem->col, elem->value);
            }
        }

        for (auto row = other.row_heads; row; row = row->next) {
            for (auto elem = static_cast<Element<T>*>(row->first); elem; elem = elem->next_row) {
                result.set(elem->row, elem->col, result.get(elem->row, elem->col) - elem->value);
            }
        }

        return result;
    }

    SparseMatrix<T> operator*(const T &scalar) {
        SparseMatrix<T> result(rows, cols);

        for (auto row = row_heads; row; row = row->next) {
            for (auto elem = static_cast<Element<T>*>(row->first); elem; elem = elem->next_row) {
                result.set(elem->row, elem->col, elem->value * scalar);
            }
        }

        return result;
    }

    SparseMatrix<T> operator*(const SparseMatrix<T> &other) {
        if (cols != other.rows) {
            throw invalid_argument("Dimensiones no compatibles para multiplicación.");
        }

        SparseMatrix<T> result(rows, other.cols);

        for (auto row = row_heads; row; row = row->next) {
            for (auto elem = static_cast<Element<T>*>(row->first); elem; elem = elem->next_row) {
                auto other_col = other.col_heads;
                while (other_col) {
                    auto other_elem = static_cast<Element<T>*>(other_col->first);
                    while (other_elem) {
                        if (other_elem->row == elem->col) {
                            T value = elem->value * other_elem->value;
                            if (value != T()) {
                                result.set(elem->row, other_elem->col,
                                           result.get(elem->row, other_elem->col) + value);
                            }
                        }
                        other_elem = other_elem->next_col;
                    }
                    other_col = other_col->next;
                }
            }
        }

        return result;
    }

    [[nodiscard]] int getRows() const { return rows; }
    [[nodiscard]] int getCols() const { return cols; }
};

#endif //ALGORITHMS_AND_DATA_STRUCTURES_SPARSEMATRIX_H
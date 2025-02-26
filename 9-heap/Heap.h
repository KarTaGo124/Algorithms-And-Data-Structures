#ifndef ALGORITHMS_AND_DATA_STRUCTURES_HEAP_H
#define ALGORITHMS_AND_DATA_STRUCTURES_HEAP_H

#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
using namespace std;

template <typename T, typename Compare = less<T>>
class Heap {
private:
    vector<T> heap;   // Almacena los elementos del heap
    Compare cmp;      // Comparador para determinar el orden

    // Intercambia los elementos en las posiciones i y j
    void swapNodes(int i, int j) {
        swap(heap[i], heap[j]);
    }

    // Repara el heap subiendo el elemento en "index" hasta su posición correcta
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            // Si el elemento actual no viola la propiedad del heap, salimos
            if (!cmp(heap[index], heap[parent])) break;
            swapNodes(index, parent);
            index = parent;
        }
    }

    // Repara el heap bajando el elemento en "index" hasta su posición correcta
    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int best = index; // "best" es el candidato a la posición correcta según cmp

            if (left < size && cmp(heap[left], heap[best]))
                best = left;
            if (right < size && cmp(heap[right], heap[best]))
                best = right;

            if (best == index) break;  // La propiedad del heap se cumple
            swapNodes(index, best);
            index = best;
        }
    }

public:
    // Constructor (por defecto se crea un min-heap; para max-heap usar greater<T> como Compare)
    Heap(Compare cmp = Compare()) : cmp(cmp) {}

    // Inserta un elemento en el heap
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Devuelve el elemento en la cima del heap (sin eliminarlo)
    T top() const {
        if (heap.empty())
            throw out_of_range("Heap is empty");
        return heap[0];
    }

    // Extrae y elimina el elemento en la cima del heap
    T pop() {
        if (heap.empty())
            throw out_of_range("Heap is empty");
        T topElement = heap[0];
        swapNodes(0, heap.size() - 1);
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);
        return topElement;
    }

    // Retorna true si el heap está vacío
    bool empty() const {
        return heap.empty();
    }

    // Retorna el número de elementos en el heap
    int size() const {
        return heap.size();
    }
};

#endif // ALGORITHMS_AND_DATA_STRUCTURES_HEAP_H

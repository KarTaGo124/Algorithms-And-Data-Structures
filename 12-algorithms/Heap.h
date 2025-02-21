//
// Created by Guillermo Galvez on 19/02/2025.
//

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_HEAP_H
#define ALGORITHMS_AND_DATA_STRUCTURES_HEAP_H

// Generalized Heap template (MinHeap, MaxHeap, CustomHeap)
template <typename T, typename Compare = less<T>>
class Heap {
private:
    vector<T> heap;       // Stores the heap elements
    Compare cmp;          // Comparator (customizable)
    vector<int> pos;      // Tracks positions of elements

    void swapNodes(int i, int j) {
        swap(heap[i], heap[j]);
        pos[heap[i].second] = i;
        pos[heap[j].second] = j;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (!cmp(heap[index], heap[parent])) break;  // No violation
            swapNodes(index, parent);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && cmp(heap[left], heap[smallest])) {
                smallest = left;
            }
            if (right < size && cmp(heap[right], heap[smallest])) {
                smallest = right;
            }

            if (smallest == index) break;  // Already satisfies heap property
            swapNodes(index, smallest);
            index = smallest;
        }
    }

public:
    Heap(int n = 0, Compare cmp = Compare()) : cmp(cmp), pos(n, -1) {}

    // Insert or update an element
    void pushOrUpdate(const T& value) {
        int node = value.second;

        if (pos[node] == -1) {  // Node not present
            pos[node] = heap.size();
            heap.push_back(value);
            heapifyUp(heap.size() - 1);
        } else if (cmp(value, heap[pos[node]])) {  // Update if needed
            heap[pos[node]] = value;
            heapifyUp(pos[node]);
        }
    }

    // Extract the top element
    T pop() {
        T topElement = heap[0];
        swapNodes(0, heap.size() - 1);
        pos[topElement.second] = -1;  // Mark as removed
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return topElement;
    }

    // Check if the heap is empty
    bool empty() const {
        return heap.empty();
    }
};


#endif //ALGORITHMS_AND_DATA_STRUCTURES_HEAP_H

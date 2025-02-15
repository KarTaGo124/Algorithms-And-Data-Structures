//
// Created by Guillermo Galvez on 14/02/2025.
//

#ifndef ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H
#define ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    T *arr;
    int frontIndex, rearIndex, capacity;

public:
    explicit Queue(int cap) {
        capacity = cap;
        arr = new T[capacity];
        frontIndex = 0;
        rearIndex = -1;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(T value) {
        if (rearIndex + 1 == capacity) {
            cout << "Queue is full, cannot enqueue.\n";
            return;
        }
        rearIndex++;
        arr[rearIndex] = value;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty, cannot dequeue.\n";
            return;
        }
        frontIndex++;
    }

    [[nodiscard]] T front() const {
        if (isEmpty()) {
            throw out_of_range("Queue is empty.");
        }
        return arr[frontIndex];
    }

    [[nodiscard]] bool isEmpty() const {
        return frontIndex > rearIndex;
    }

    [[nodiscard]] bool isFull() const {
        return rearIndex == capacity - 1;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        for (int i = frontIndex; i <= rearIndex; ++i) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

#endif //ALGORITHMS_AND_DATA_STRUCTURES_QUEUE_H

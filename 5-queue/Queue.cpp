//
// Created by Guillermo Galvez on 19/01/2025.
//
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

int main() {
    cout << "Queue Demo:\n";
    Queue<int> queue(5);

    cout << "Enqueue 5\n";
    queue.enqueue(5);
    cout << "Enqueue 3\n";
    queue.enqueue(3);
    cout << "Enqueue 7\n";
    queue.enqueue(7);
    queue.display();
    cout << "Front: " << queue.front() << "\n";
    cout << "Dequeue\n";
    queue.dequeue();
    queue.display();
    cout << "Front: " << queue.front() << "\n";
    cout << "Dequeue\n";
    queue.dequeue();
    queue.display();
    cout << "Enqueue 9\n";
    queue.enqueue(9);
    queue.display();
    if (queue.isEmpty()) {
        cout << "Queue is empty.\n";
    } else {
        cout << "Queue is not empty.\n";
    }
    if (queue.isFull()) {
        cout << "Queue is full.\n";
    } else {
        cout << "Queue is not full.\n";
    }
    return 0;
}
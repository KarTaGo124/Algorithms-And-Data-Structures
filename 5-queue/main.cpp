//
// Created by Guillermo Galvez on 14/02/2025.
//
#include "Queue.h"
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
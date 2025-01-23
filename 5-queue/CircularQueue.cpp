//
// Created by Guillermo Galvez on 19/01/2025.
//
#include <iostream>
using namespace std;

template <typename T>
class MyCircularQueue
{
private:
    int size;
    T *queue;
    int front;
    int rear;

public:
    MyCircularQueue(int k)
    {
        this->size = k + 1;
        queue = new T[size];
        front = 0;
        rear = 0;
    }

    bool enQueue(T value)
    {
        if (isFull())
        {
            cout << "Queue is full, cannot enqueue.\n";
            return false;
        }
        else
        {
            rear = (rear + 1) % size;
            queue[rear] = value;
            return true;
        }
    }

    bool deQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty, cannot dequeue.\n";
            return false;
        }
        else
        {
            front = (front + 1) % size;
            return true;
        }
    }

    T Front()
    {
        if (!isEmpty())
            return queue[(front + 1) % size];
        return T{};
    }

    T Rear()
    {
        if (!isEmpty())
            return queue[rear];
        return T{};
    }

    bool isEmpty()
    {
        if (front == rear)
            return true;
        return false;
    }

    bool isFull()
    {
        if (front == (rear + 1) % size)
            return true;
        return false;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        for (int i = (front + 1) % size; i != (rear + 1) % size; i = (i + 1) % size) {
            cout << queue[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    MyCircularQueue<int> circularQueue(3);

    cout << "Enqueue 5" << endl;
    circularQueue.enQueue(5);
    cout << "Enqueue 3" << endl;
    circularQueue.enQueue(3);
    cout << "Enqueue 7" << endl;
    circularQueue.enQueue(7);
    cout << "Enqueue 9" << endl;
    circularQueue.enQueue(9);
    circularQueue.display();

    cout << "Front: " << circularQueue.Front() << endl;
    cout << "Rear: " << circularQueue.Rear() << endl;

    cout << "Dequeue" << endl;
    circularQueue.deQueue();
    circularQueue.display();

    cout << "Front: " << circularQueue.Front() << endl;
    cout << "Rear: " << circularQueue.Rear() << endl;

    circularQueue.display();

    return 0;
}

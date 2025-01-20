//
// Created by Guillermo Galvez on 19/01/2025.
//
#include <iostream>
using namespace std;

class MyCircularQueue
{
private:
    int size;
    int *queue;
    int front;
    int rear;

public:
    MyCircularQueue(int k)
    {
        this->size = k + 1;
        queue = new int[size];
        front = 0;
        rear = 0;
    }

    bool enQueue(int value)
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

    int Front()
    {
        if (!isEmpty())
            return queue[(front + 1) % size];
        return -1;
    }

    int Rear()
    {
        if (!isEmpty())
            return queue[rear];
        return -1;
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
    MyCircularQueue circularQueue(3);

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

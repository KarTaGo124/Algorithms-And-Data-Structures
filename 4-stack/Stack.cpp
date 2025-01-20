//
// Created by Guillermo Galvez on 19/01/2025.
//
#include <iostream>
using namespace std;

class Stack {
private:
    int *arr;
    int topIndex;
    int capacity;

public:
    explicit Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        topIndex = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        if (topIndex + 1 == capacity) {
            cout << "Stack overflow, cannot push.\n";
            return;
        }
        arr[++topIndex] = value;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot pop.\n";
            return;
        }
        topIndex--;
    }

    [[nodiscard]] int top() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty.");
        }
        return arr[topIndex];
    }

    [[nodiscard]] bool isEmpty() const {
        return topIndex == -1;
    }

    [[nodiscard]] bool isFull() const {
        return topIndex == capacity - 1;
    }

    void display() const {
        for (int i = topIndex; i >= 0; --i) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    cout << "Stack Demo:\n";
    Stack stack(10);
    cout << "Pushing 5\n";
    stack.push(5);
    cout << "Pushing 3\n";
    stack.push(3);
    cout << "Pushing 8\n";
    stack.push(8);
    cout << "Pushing 12\n";
    stack.push(12);
    cout << "Displaying stack: ";
    stack.display();
    cout << "Top element: " << stack.top() << "\n";
    cout << "Popping\n";
    stack.pop();
    cout << "Displaying stack: ";
    stack.display();
    cout << "Top element: " << stack.top() << "\n";
    cout << "Popping\n";
    stack.pop();
    cout << "Displaying stack: ";
    stack.display();
    if (stack.isEmpty()) {
        cout << "Stack is empty.\n";
    } else {
        cout << "Stack is not empty.\n";
    }
    if (stack.isFull()) {
        cout << "Stack is full.\n";
    } else {
        cout << "Stack is not full.\n";
    }

    return 0;
}

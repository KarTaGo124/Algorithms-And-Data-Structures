//
// Created by Guillermo Galvez on 15/01/2025.
//

// Created by Guillermo Galvez on 13/01/2025.

#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node() : next(nullptr), prev(nullptr) {}
    explicit Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    ~Node() = default;
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        clear();
    }

    void print() {
        if (!head) {
            cout << "Elements: []" << endl;
            return;
        }
        Node<T>* temp = head;
        cout << "Elements: [";
        while (temp) {
            cout << temp->data;
            temp = temp->next;
            if (temp) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    T front() {
        return head ? head->data : -1;
    }

    T back() {
        return tail ? tail->data : -1;
    }

    void push_front(T value) {
        auto new_node = new Node<T>(value);
        new_node->next = head;
        if (head) {
            head->prev = new_node;
        } else {
            tail = new_node;
        }
        head = new_node;
    }

    void push_back(T value) {
        auto new_node = new Node<T>(value);
        new_node->prev = tail;
        if (tail) {
            tail->next = new_node;
        } else {
            head = new_node;
        }
        tail = new_node;
    }

    T pop_front() {
        if (!head) return -1;
        auto toDelete = head;
        T value = toDelete->data;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete toDelete;
        return value;
    }

    T pop_back() {
        if (!tail) return -1;
        auto toDelete = tail;
        T value = toDelete->data;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete toDelete;
        return value;
    }

    void insert(T value, int position) {
        if (position < 0 || position > size()) {
            cout << "Cannot insert element at position " << position << endl;
            return;
        }
        if (position == 0) {
            push_front(value);
            return;
        }
        if (position == size()) {
            push_back(value);
            return;
        }
        auto new_node = new Node<T>(value);
        auto temp = head;
        for (int i = 0; i < position; i++) {
            temp = temp->next;
        }
        new_node->next = temp;
        new_node->prev = temp->prev;
        temp->prev->next = new_node;
        temp->prev = new_node;
    }

    void remove(int position) {
        if (position < 0 || position >= size()) {
            cout << "Cannot remove element at position " << position << endl;
            return;
        }
        if (position == 0) {
            pop_front();
            return;
        }
        if (position == size() - 1) {
            pop_back();
            return;
        }
        auto temp = head;
        for (int i = 0; i < position; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    T operator[](int position) {
        if (position < 0 || position >= size()) return -1;
        auto temp = head;
        for (int i = 0; i < position; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        int count = 0;
        auto temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void clear() {
        while (head) {
            auto toDelete = head;
            head = head->next;
            delete toDelete;
        }
        tail = nullptr;
    }

    void reverse() {
        if (!head) return;
        auto current = head;
        Node<T>* prev = nullptr;
        tail = head;
        while (current) {
            auto next = current->next;
            current->next = prev;
            current->prev = next;
            prev = current;
            current = next;
        }
        head = prev;
    }
};

int main() {
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing front(),back() in a doubly linked list with 1 element" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    DoublyLinkedList<int> list;
    list.push_back(3);
    list.print();
    cout << "Front: " << list.front() << endl;
    cout << "Back: " << list.back() << endl;

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing front(),back(),push_back(),push_front(),pop_back(),pop_front() in a doubly linked list" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    DoublyLinkedList<int> list2;
    list2.print();
    cout << "Front when there are no elements: " << list2.front() << endl;
    cout << "Back when there are no elements: " << list2.back() << endl;
    cout << "Pushing back 3,5,2,10 and 6" << endl;
    list2.push_back(3);
    list2.push_back(5);
    list2.push_back(2);
    list2.push_back(10);
    list2.push_back(6);
    list2.print();
    list2.pop_back();
    cout << "Popping back" << endl;
    list2.print();
    cout << "Front: " << list2.front() << endl;
    cout << "Back: " << list2.back() << endl;
    list2.pop_front();
    cout << "Popping front" << endl;
    list2.print();
    cout << "Pushing front 4" << endl;
    list2.push_front(4);
    list2.print();

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing insert(), remove() and reverse() in a doubly linked list" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    list2.print();
    cout << "Inserting 14 at position 3" << endl;
    list2.insert(14, 3);
    list2.print();
    cout << "Inserting 7 at position 1" << endl;
    list2.insert(7, 1);
    list2.print();
    cout << "Inserting 9 at position 5" << endl;
    list2.insert(9, 5);
    list2.print();
    cout << "Removing element at position 4" << endl;
    list2.remove(4);
    list2.print();
    cout << "Removing element at position 2" << endl;
    list2.remove(2);
    list2.print();
    cout << "Removing element at position 1" << endl;
    list2.remove(1);
    list2.print();
    cout << "Reversing the doubly linked list" << endl;
    list2.reverse();
    list2.print();

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing operator[],empty(),size(),clear() in a doubly linked list with some elements" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    list2.print();
    cout << "Element in the position 1: " << list2[1] << endl;
    cout << "Element in the position 2: " << list2[2] << endl;
    if (list2.empty())
        cout << "The doubly linked list is empty" << endl;
    else
        cout << "The doubly linked list is not empty" << endl;
    cout << "The size of the doubly linked list is: " << list2.size() << endl;
    list2.clear();
    cout << "Clearing the doubly linked list..." << endl;
    list2.print();

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing operator[],empty(),size(),clear(), reverse() in a doubly linked list without elements" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    list2.print();
    cout << "Element in the position 1: " << list2[1] << endl;
    cout << "Element in the position 2: " << list2[2] << endl;
    if (list2.empty())
        cout << "The doubly linked list is empty" << endl;
    else
        cout << "The doubly linked list is not empty" << endl;
    cout << "The size of the doubly linked list is: " << list2.size() << endl;
    list2.clear();
    cout << "Inserting element at position 3" << endl;
    list2.insert(3, 3);
    cout << "Removing element at position 1" << endl;
    list2.remove(1);
    cout << "Reversing the doubly linked list" << endl;
    list2.reverse();
    list2.print();
    cout << "Clearing the doubly linked list..." << endl;
    list2.print();

    return 0;
}

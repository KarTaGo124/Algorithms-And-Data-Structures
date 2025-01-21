//
// Created by Guillermo Galvez on 13/01/2025.
//

#include <iostream>

using namespace std;

template <typename T>
struct Node {
    // Data of the node
    T data;
    // Pointer to the next node
    Node* next;
    // Pointer to the previous node
    Node* prev;
    // Constructor
    Node() : next(nullptr), prev(nullptr) {}
    // Constructor with data
    explicit Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    // Destructor
    ~Node() = default;
};

template <typename T>
// Class that represents a circular doubly linked list
class CircularDoublyLinkedList {
private:
    // Pointer to the first element in the list
    Node<T>* sentinel;
    // tamaño de la lista
    int tam;
public:
    // Constructor with a sentinel node
    explicit CircularDoublyLinkedList(){
        sentinel = new Node<T>();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        tam = 0;
    }
    // Destructor
    ~CircularDoublyLinkedList(){
        clear();
        delete sentinel;
    }

    // Prints the elements in the list
    void print(){
        if (sentinel == sentinel->next) {cout << "Elements: []" << endl;}
        else {
            Node<T> *temp = sentinel->next;
            cout << "Elements: [";
            while (temp != sentinel) {
                cout << temp->data;
                temp = temp->next;
                if (temp != sentinel) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        }
    }
    // Returns the first element in the list
    T front(){
        if (sentinel->next == sentinel) return -1;
        else return sentinel->next->data;
    }
    // Returns the last element in the list
    T back(){
        if (sentinel->prev == sentinel) return -1;
        else return sentinel->prev->data;
    }
    // Adds a new element at the beginning of the list
    void push_front(T value){
        auto new_node = new Node<T>(value);
        new_node->next = sentinel->next;
        new_node->prev = sentinel;
        sentinel->next->prev = new_node;
        sentinel->next = new_node;
        tam++;
    }
    // Adds a new element at the end of the list
    void push_back(T value) {
        auto new_node = new Node<T>(value);
        new_node->next = sentinel;
        new_node->prev = sentinel->prev;
        sentinel->prev->next = new_node;
        sentinel->prev = new_node;
        tam++;
    }
    // Removes the first element in the list
    T pop_front(){
        if (sentinel->next == sentinel) return -1;
        else {
            auto toDelete = sentinel->next;
            T value = toDelete->data;
            sentinel->next = toDelete->next;
            toDelete->next->prev = sentinel;
            tam--;
            delete toDelete;
            return value;
        }
    }
    // Removes the last element in the list
    T pop_back(){
        if (sentinel->next == sentinel) return -1;
        else {
            auto toDelete = sentinel->prev;
            T value = toDelete->data;
            sentinel->prev = toDelete->prev;
            toDelete->prev->next = sentinel;
            tam--;
            delete toDelete;
            return value;
        }
    }
    // Inserts a new element in the list at a given position
    void insert(T value, int position) {
        if (position < 0 || position > tam) {
            cout << "Cannot insert element at position " << position << endl;
            return;
        }
         if (position == 0) {
            push_front(value);
            return;
        } else if (position == tam) {
            push_back(value);
            return;
        } else {
            auto new_node = new Node<T>(value);
            auto temp = sentinel->next;
            for (int i = 0; i < position; i++) {
                temp = temp->next;
            }
            new_node->next = temp;
            new_node->prev = temp->prev;
            temp->prev->next = new_node;
            temp->prev = new_node;
            tam++;
         }
    }
    // Removes the element at a given position in the list
    void remove(int position) {
        if (position < 0 || position >= tam) {
            cout << "Cannot remove element at position " << position << endl;
            return;
        }
        if (position == 0) {
            pop_front();
            return;
        } else if (position == tam - 1) {
            pop_back();
            return;
        } else {
            auto temp = sentinel->next;
            for (int i = 0; i < position; i++) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            tam--;
        }
    }
    // Returns the element at the specified position in the list
    T operator[](int position){
        if (position > tam) return -1;
        auto temp = sentinel->next;
        for (int i = 0; i < position; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    // Returns true if the list is empty, false otherwise
    bool empty(){
        if (sentinel->next == sentinel) return true;
        return false;
    }
    // Returns the number of elements in the list
    int size(){
        return tam;
    }
    // Clears the list
    void clear(){
        while (sentinel->next != sentinel) {
            pop_front();
        }
        tam = 0;
    }
    // Reverses the list
    void reverse(){
        if (sentinel->next == sentinel) return;
        auto current = sentinel->next;
        Node<T>* prev = sentinel;
        Node<T>* next = nullptr;
        do {
            next = current->next;
            current->next = prev;
            current->prev = next;
            prev = current;
            current = next;
        } while (current != sentinel);
        sentinel->next = prev;
        sentinel->prev = prev->prev;

    }

};
int main() {
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing front(),back() in a circular doubly linked list with 1 element" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    CircularDoublyLinkedList<int> list;
    list.push_back(3);
    list.print();
    cout << "Front: " << list.front() << endl;
    cout << "Back: " << list.back() << endl;

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing front(),back(),push_back(),push_front(),pop_back(),pop_front() in a circular doubly linked list" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    CircularDoublyLinkedList<int> list2;
    list2.print();
    cout << "Front when there are not elements: " << list2.front() << endl;
    cout << "Back when there are not elements: " << list2.back() << endl;
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
    cout << "Testing insert(), remove() and reverse() in a circular doubly linked list" << endl;
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
    cout << "Reversing the circular doubly linked list" << endl;
    list2.reverse();
    list2.print();

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing operator[],empty(),size(),clear() in a circular doubly linked list with some elements" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    list2.print();
    cout << "Element in the position 1: " << list2[1] << endl;
    cout << "Element in the position 2: " << list2[2] << endl;
    if (list2.empty())
        cout << "The circular doubly linked list is empty" << endl;
    else
        cout << "The circular doubly linked list is not empty" << endl;
    cout << "The size of the circular doubly linked list is: " << list2.size() << endl;
    list2.clear();
    cout << "Clearing the circular doubly linked list..." << endl;
    list2.print();

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing operator[],empty(),size(),clear(), reverse() in a circular doubly linked list without elements" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    list2.print();
    cout << "Element in the position 1: " << list2[1] << endl;
    cout << "Element in the position 2: " << list2[2] << endl;
    if (list2.empty())
        cout << "The circular doubly linked list is empty" << endl;
    else
        cout << "The circular doubly linked list is not empty" << endl;
    cout << "The size of the circular doubly linked list is: " << list2.size() << endl;
    list2.clear();
    cout << "Inserting element at position 3" << endl;
    list2.insert(3, 3);
    cout << "Removing element at position 1" << endl;
    list2.remove(1);
    cout << "Reversing the circular doubly linked list" << endl;
    list2.reverse();
    list2.print();
    cout << "Clearing the circular doubly linked list..." << endl;
    list2.print();

    return 0;
}

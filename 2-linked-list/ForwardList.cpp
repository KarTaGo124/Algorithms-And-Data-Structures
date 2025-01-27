//
// Created by Guillermo Galvez on 07/01/2025.
//
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    // Data of the node
    T data;
    // Pointer to the next node
    Node* next;
    // Constructor
    Node() : next(nullptr) {}
    // Constructor with data
    explicit Node(const T& data) : data(data), next(nullptr) {}
    // Destructor
    ~Node() = default;
};

template <typename T>
// Class that represents a forward list
class ForwardList {
private:
    // Pointer to the first element in the list
    Node<T>* head;
public:
    // Constructor
    ForwardList(): head(nullptr){}
    // Destructor
    ~ForwardList(){
        clear();
    }
    // Prints the elements in the list
    void print(){
        if (head == nullptr) {cout << "Elements: []" << endl;}
        else {
            Node<T> *temp = head;
            cout << "Elements: [";
            while (temp->next != nullptr) {
                cout << temp->data << ", ";
                temp = temp->next;
            }
            cout << temp->data << "]" << endl;
        }
    }
    // Returns the first element in the list
    T front(){
        if (head == nullptr) return -1;
        else return head->data;
    }
    // Returns the last element in the list
    T back(){
        Node<T>* temp = head;
        if (head == nullptr) return -1;
        while (temp->next != nullptr){
            temp = temp->next;
        }
        return temp->data;
    }
    // Adds a new element at the beginning of the list
    void push_front(T value){
        auto new_head = new Node<T>(value);
        new_head->next = head;
        head = new_head;
    }
    // Adds a new element at the end of the list
    void push_back(T value){
        auto new_tail = new Node<T>(value);
        if (head == nullptr) {head = new_tail;}
        else {
            Node<T> *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new_tail;
            new_tail->next = nullptr;
        }
    }
    // Removes the first element in the list
    T pop_front(){
        if (head == nullptr) {return -1;}
        else {
            Node<T> *temp = head;
            head = head->next;
            int value = temp->data;
            delete temp;
            return value;
        }
    }
    // Removes the last element in the list
    T pop_back(){
        if (head == nullptr) {return -1;}
        else if (head->next == nullptr) {
            int value = head->data;
            delete head;
            head = nullptr;
            return value;
        }
        Node<T>* temp = head;
        while (temp->next->next != nullptr){
            temp = temp->next;
        }
        int value = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        return value;
    }
    // Returns the element at the specified position in the list
    T operator[](int position){
        if (head == nullptr) {return -1;}
        else {
            Node<T> *temp = head;
            int i = 0;
            while (i++ < position) {
                temp = temp->next;
            }
            if (temp != nullptr)
                return temp->data;
            else return -1;
        }
    }
    // Returns true if the list is empty, false otherwise
    bool empty(){
        return head == nullptr;
    }
    // Returns the number of elements in the list
    int size(){
        if (head == nullptr) {return 0;}
        else {
            Node<T> *temp = head;
            int i = 1;
            while (temp->next != nullptr) {
                i++;
                temp = temp->next;
            }
            return i;
        }
    }
    // Clears the list
    void clear(){
        Node<T>* temp;
        while (head != nullptr){
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Sorts the list in ascending order using insertion sort
    void sort(){
        if (head == nullptr || head->next == nullptr) {return ;}

        auto prevHead = new Node<T>(0);
        prevHead->next = head;
        auto current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->data <= current->next->data) {
                current = current->next;
                continue;
            }

            auto toInsert = current->next;
            current->next = current->next->next;

            auto prev = prevHead;
            while (prev->next->data < toInsert->data) {
                prev = prev->next;
            }

            toInsert->next = prev->next;
            prev->next = toInsert;

        }
        head = prevHead->next;
        delete prevHead;
    }

    // Reverses the list
    void reverse(){
        if(head == nullptr || head->next == nullptr) return ;

        auto current = head;
        Node<T>* newHead = nullptr;

        while (current != nullptr) {
            auto nextNode = current->next;
            current->next = newHead;
            newHead = current;
            current = nextNode;
        }
        head = newHead;
    }
};
int main(){
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing front(),back() in a forward list with 1 element" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    ForwardList<int> list2;
    list2.push_front(7);
    list2.print();
    cout << "Front: " << list2.front() << endl;
    cout << "Back: " << list2.back() << endl;

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing front(),back(),push_back(),push_front(),pop_back(),pop_front() in a forward list" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    ForwardList<int> list3;
    list3.print();
    cout << "Front when there are not elements: " << list3.front() << endl;
    cout << "Back when there are not elements: " << list3.back() << endl;
    cout << "Pushing back 3,5,2,10 and 6" << endl;
    list3.push_back(3);
    list3.push_back(5);
    list3.push_back(2);
    list3.push_back(10);
    list3.push_back(6);
    list3.print();
    list3.pop_back();
    cout << "Popping back" << endl;
    list3.print();
    cout << "Pushing front 4" << endl;
    list3.push_front(4);
    list3.print();
    cout << "Popping front" << endl;
    list3.pop_front();
    list3.print();
    cout << "Front: " << list3.front() << endl;
    cout << "Back: " << list3.back() << endl;

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing operator[],empty(),size(),clear() in a forward list with some elements" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    list3.print();
    cout << "Element in the position 1: " << list3[1] << endl;
    cout << "Element in the position 4: " << list3[4] << endl;
    if (list3.empty())
        cout << "The forward list is empty" << endl;
    else
        cout << "The forward list is not empty" << endl;
    cout << "The size of the forward list is: " << list3.size() << endl;
    list3.clear();
    cout << "Clearing the forward list..." << endl;
    list3.print();

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing operator[],empty(),size(),clear() in a forward list without elements" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    list2.pop_back();
    list2.print();
    cout << "Element in the position 0: " << list2[1] << endl;
    if (list2.empty())
        cout << "The forward list is empty" << endl;
    else
        cout << "The forward list is not empty" << endl;
    cout << "The size of the forward list is: " << list2.size() << endl;
    list2.clear();
    cout << "Clearing the forward list..." << endl;
    list2.print();



    cout << "---------------------------------------------------------------------" << endl;
    cout << "Testing sort() and reverse() in a forward list with elements" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    ForwardList<int> list4;
    list4.push_back(3);
    list4.push_back(5);
    list4.push_back(2);
    list4.push_back(10);
    list4.push_back(6);
    cout << "Original list" << endl;
    list4.print();
    cout << "Sorting the list" << endl;
    list4.sort();
    list4.print();
    cout << "Reversing the list" << endl;
    list4.reverse();
    list4.print();

    cout << "---------------------------------------------------------------------" << endl;
    cout << "Obs: I am using -1 for exceptions in the returns" << endl;
    cout << "---------------------------------------------------------------------" << endl;
}
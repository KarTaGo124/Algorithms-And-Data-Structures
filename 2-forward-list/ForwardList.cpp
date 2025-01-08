//
// Created by Guillermo Galvez on 07/01/2025.
//
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node() : next(nullptr) {}
    explicit Node(T data) : data(data), next(nullptr) {}
    ~Node() = default;
};

template <typename T>
class ForwardList {
private:
    Node<T>* head;
public:
    ForwardList(): head(nullptr){}
    explicit ForwardList(Node<T>* head):head(head) {};
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
    T front(){
        if (head == nullptr) return -1;
        else return head->data;
    }
    T back(){
        Node<T>* temp = head;
        if (head == nullptr) return -1;
        while (temp->next != nullptr){
            temp = temp->next;
        }
        return temp->data;
    }
    void push_front(T value){
        auto new_head = new Node<T>(value);
        new_head->next = head;
        head = new_head;
    }
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
    bool empty(){
        return head == nullptr;
    }
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
    void clear(){
        Node<T>* temp;
        while (head != nullptr){
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    void sort(){

    }
    void reverse(){

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
    cout << "Obs: I am using -1 for exceptions in the returns" << endl;
    cout << "---------------------------------------------------------------------" << endl;

}
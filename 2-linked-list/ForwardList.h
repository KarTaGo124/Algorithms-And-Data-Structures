#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node *next;
    Node(const T &data) : data(data), next(nullptr) {}
};

template <typename T>
class ForwardList {
private:
    Node<T> *head;
    Node<T> *tail;
    int count;

public:
    ForwardList() : head(nullptr), tail(nullptr), count(0) {}

    ~ForwardList() { clear(); }

    void print() {
        Node<T> *temp = head;
        cout << "Elements: [";
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << ", ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }

    T front() { return head ? head->data : -1; }

    T back() { return tail ? tail->data : -1; }

    void push_front(T value) {
        Node<T> *new_head = new Node<T>(value);
        new_head->next = head;
        head = new_head;
        if (!tail) tail = head;
        count++;
    }

    void push_back(T value) {
        Node<T> *new_tail = new Node<T>(value);
        if (!head) head = tail = new_tail;
        else {
            tail->next = new_tail;
            tail = new_tail;
        }
        count++;
    }

    T pop_front() {
        if (!head) return -1;
        Node<T> *temp = head;
        T value = temp->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        count--;
        return value;
    }

    T pop_back() {
        if (!head) return -1;
        if (head == tail) {
            T value = head->data;
            delete head;
            head = tail = nullptr;
            count--;
            return value;
        }
        Node<T> *temp = head;
        while (temp->next != tail) temp = temp->next;
        T value = tail->data;
        delete tail;
        tail = temp;
        tail->next = nullptr;
        count--;
        return value;
    }

    T operator[](int position) {
        if (position < 0 || position >= count) return -1;
        Node<T> *temp = head;
        while (position--) temp = temp->next;
        return temp->data;
    }

    bool empty() { return count == 0; }

    int size() { return count; }

    void clear() {
        while (head) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    void sort() {
        if (!head || !head->next) return;

        Node<T> *sorted = nullptr;
        Node<T> *current = head;

        while (current) {
            Node<T> *next = current->next;
            if (!sorted || current->data < sorted->data) {
                current->next = sorted;
                sorted = current;
            } else {
                Node<T> *temp = sorted;
                while (temp->next && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
        tail = head;
        while (tail->next) tail = tail->next;
    }

    void reverse() {
        if (!head || !head->next) return;

        Node<T> *prev = nullptr, *current = head, *next = nullptr;
        tail = head;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    Node<T>* getIterator() { return head; }
    bool hasNext(Node<T>* node) { return node && node->next; }
    Node<T>* next(Node<T>* node) { return node->next; }
};

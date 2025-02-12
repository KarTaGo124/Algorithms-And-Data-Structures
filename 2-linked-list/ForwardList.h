//
// Created by Guillermo Galvez on 07/01/2025.
//
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	// Data of the node
	T data;
	// Pointer to the next node
	Node *next;
	// Constructor
	Node() : next(nullptr) {}
	// Constructor with data
	explicit Node(const T &data) : data(data), next(nullptr) {}
	// Destructor
	~Node() = default;
};

template <typename T>
// Class that represents a forward list
class ForwardList
{
private:
	// Pointer to the first element in the list
	Node<T> *head;

public:
	// Constructor
	ForwardList() : head(nullptr) {}
	// Destructor
	~ForwardList()
	{
		clear();
	}
	// Prints the elements in the list
	void print()
	{
		if (head == nullptr)
		{
			cout << "Elements: []" << endl;
		}
		else
		{
			Node<T> *temp = head;
			cout << "Elements: [";
			while (temp->next != nullptr)
			{
				cout << temp->data << ", ";
				temp = temp->next;
			}
			cout << temp->data << "]" << endl;
		}
	}
	// Returns the first element in the list
	T front()
	{
		if (head == nullptr)
			return -1;
		else
			return head->data;
	}
	// Returns the last element in the list
	T back()
	{
		Node<T> *temp = head;
		if (head == nullptr)
			return -1;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		return temp->data;
	}
	// Adds a new element at the beginning of the list
	void push_front(T value)
	{
		auto new_head = new Node<T>(value);
		new_head->next = head;
		head = new_head;
	}
	// Adds a new element at the end of the list
	void push_back(T value)
	{
		auto new_tail = new Node<T>(value);
		if (head == nullptr)
		{
			head = new_tail;
		}
		else
		{
			Node<T> *temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = new_tail;
			new_tail->next = nullptr;
		}
	}
	// Removes the first element in the list
	T pop_front()
	{
		if (head == nullptr)
		{
			return -1;
		}
		else
		{
			Node<T> *temp = head;
			head = head->next;
			int value = temp->data;
			delete temp;
			return value;
		}
	}
	// Removes the last element in the list
	T pop_back()
	{
		if (head == nullptr)
		{
			return -1;
		}
		else if (head->next == nullptr)
		{
			int value = head->data;
			delete head;
			head = nullptr;
			return value;
		}
		Node<T> *temp = head;
		while (temp->next->next != nullptr)
		{
			temp = temp->next;
		}
		int value = temp->next->data;
		delete temp->next;
		temp->next = nullptr;
		return value;
	}
	// Returns the element at the specified position in the list
	T operator[](int position)
	{
		if (head == nullptr)
		{
			return -1;
		}
		else
		{
			Node<T> *temp = head;
			int i = 0;
			while (i++ < position)
			{
				temp = temp->next;
			}
			if (temp != nullptr)
				return temp->data;
			else
				return -1;
		}
	}
	// Returns true if the list is empty, false otherwise
	bool empty()
	{
		return head == nullptr;
	}
	// Returns the number of elements in the list
	int size()
	{
		if (head == nullptr)
		{
			return 0;
		}
		else
		{
			Node<T> *temp = head;
			int i = 1;
			while (temp->next != nullptr)
			{
				i++;
				temp = temp->next;
			}
			return i;
		}
	}
	// Clears the list
	void clear()
	{
		Node<T> *temp;
		while (head != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}

	// Sorts the list in ascending order using insertion sort
	void sort()
	{
		if (head == nullptr || head->next == nullptr)
		{
			return;
		}

		auto prevHead = new Node<T>(0);
		prevHead->next = head;
		auto current = head;

		while (current != nullptr && current->next != nullptr)
		{
			if (current->data <= current->next->data)
			{
				current = current->next;
				continue;
			}

			auto toInsert = current->next;
			current->next = current->next->next;

			auto prev = prevHead;
			while (prev->next->data < toInsert->data)
			{
				prev = prev->next;
			}

			toInsert->next = prev->next;
			prev->next = toInsert;
		}
		head = prevHead->next;
		delete prevHead;
	}

	// Reverses the list
	void reverse()
	{
		if (head == nullptr || head->next == nullptr)
			return;

		auto current = head;
		Node<T> *newHead = nullptr;

		while (current != nullptr)
		{
			auto nextNode = current->next;
			current->next = newHead;
			newHead = current;
			current = nextNode;
		}
		head = newHead;
	}
    // get iterator
    Node<T>* getIterator(){
        return head;
    }
    // has next
    bool hasNext(Node<T>* node){
        return node->next != nullptr;
    }
    // next
    Node<T>* next(Node<T>* node){
        return node->next;
    }
};

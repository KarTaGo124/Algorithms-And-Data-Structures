#include "ForwardList.h"

int main()
{
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
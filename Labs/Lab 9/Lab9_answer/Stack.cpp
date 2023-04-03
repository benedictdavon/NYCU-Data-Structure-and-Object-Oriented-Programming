#include "Stack.h"

void Stack::push(int num) {
	List.Push_back(num);
}

void Stack::pop() {
	List.Delete(List.length);
	List.length--;
}

void Stack::print() {
	cout << "The value in the stack: ";
	List.Print();
	cout << endl;
}
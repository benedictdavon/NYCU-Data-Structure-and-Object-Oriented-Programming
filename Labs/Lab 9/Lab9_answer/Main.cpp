#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"
#include "Stack.h"

int main() {
	ifstream File;
	File.open("input2.txt");

	if (!File.is_open()) {
		cout << "Can't open txt file" << endl;
		return 0;
	}

	int TestCase = 0;
	File >> TestCase;
	//cout << "Test case is: " << TestCase << endl;

	for (int i = 0; i < TestCase; i++) {
		int commandCount, val;
		char type;
		string command;
		File >> type >> commandCount;
		//cout << "Type is: " << type << endl;
		Stack stack;
		Queue queue;

		switch (type)
		{
		case 'S':
			for (int j = 0; j < commandCount; j++) {
				File >> command;
				//cout << "Command is: " << command << endl;
				if (command == "push") {
					File >> val;
					stack.push(val);
				} else if (command == "pop") {
					stack.pop();
				} else if (command == "print") {
					stack.print();
				}
			}
			break;
		case 'Q':
			for (int j = 0; j < commandCount; j++) {
				File >> command;
				//cout << "Command is: " << command << endl;
				if (command == "en") {
					File >> val;
					queue.enqueue(val);
				}
				else if (command == "de") {
					queue.dequeue();
				}
				else if (command == "print") {
					queue.print();
				}
			}
		default:
			break;
		}
		cout << endl;
	}

	system("pause");
	return 0;
}
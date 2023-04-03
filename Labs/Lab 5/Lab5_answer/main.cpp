#include <iostream>
#include <fstream>
#include <windows.h>
#include "Integer.h"

using namespace std;

//read the data from the file
void readFile(const char* fileName);
int toDec(char num);

int main()
{
	readFile("input.txt");
	system("pause");
	return 0;
}

void readFile(const char* fileName) {
	ifstream inputFile;
	inputFile.open(fileName);
	//TODO: Read the input file here.
	int lines = 0;
	char op;
	inputFile >> lines;

	int pos;
	string temp;
	for (size_t i = 0; i < lines; i++)
	{
		//TODO: Implement your add or minus
		Integer answer("");
		pos = 0;
		inputFile >> temp;
		//check if it starts with '-'
		if (temp[0] == '-') {
			//get the position of '+' sign
			pos = temp.find("+");
			if (pos != string::npos) {
				Integer a(temp.substr(1, pos-1));
				Integer b(temp.substr(pos + 1, temp.length() + 1));
				answer = b - a;
				cout << "num1: -" << a << endl;
				cout << "num2: " << b << endl;
				cout << "result: " << answer << endl << endl;
			}
			else {
				pos = temp.find("-", 1);
				Integer a(temp.substr(1, pos-1));
				Integer b(temp.substr(pos + 1, temp.length() + 1));
				cout << "a: " << temp.substr(1, pos-1) << endl;
				cout << "b: " << temp.substr(pos + 1, temp.length() + 1) << endl;
				answer = a + b;
				cout << "num1: -" << a << endl;
				cout << "num2: " << b << endl;
				cout << "result: -" << answer << endl << endl;
			}
		}
		// else if the first integer not a negative number
		else {
			pos = temp.find("+");
			if (pos != string::npos) {
				Integer a(temp.substr(0, pos));
				Integer b(temp.substr(pos + 1, temp.length() + 1));
				answer = a + b;
				cout << "num1: " << a << endl;
				cout << "num2: " << b << endl;
				cout << "result: " << answer << endl << endl;
			}
			else {
				pos = temp.find("-");
				Integer a(temp.substr(0, pos));
				Integer b(temp.substr(pos+1, temp.length() + 1));
				answer = a - b;
				cout << "num1: " << a << endl;
				cout << "num2: " << b << endl;
				cout << "result: " << answer << endl << endl;
			}
		}
		
		
	}

	inputFile.close();
}

#ifndef INTEGER_H
#define INTEGER_H 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Integer
{
private:
	vector<int> num1;  //store the first number
	vector<int> num2;  //store the second number
	vector<int> result;  //store the result
public:
	//constructor
	Integer();	//default constructor

	//read the data from the file
	void readFile(const char* fileName);

	//clear the data member
	void reset();

	//overload 
	void operator +(Integer b);
	void operator -(Integer b);

	//input and output overload
	friend ifstream& operator >> (ifstream& in, Integer& i);
	friend ostream& operator << (ostream& out, const Integer& i);
};
#endif
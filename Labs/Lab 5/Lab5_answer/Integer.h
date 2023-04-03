#ifndef INTEGER_H
#define INTEGER_H 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Integer
{
private:
	//store the number
	vector<int> num;
public:
	bool negative = false;
	//constructor
	Integer(string number);	//default constructor
	//void assignNumValue(vector<int> temp);
	//vector<int> getNumValue();
	//operation overload 
	Integer operator +(const Integer& b);
	Integer operator -(const Integer& b);

	//output overload
	friend ostream& operator << (ostream& out, const Integer& i);
};
#endif
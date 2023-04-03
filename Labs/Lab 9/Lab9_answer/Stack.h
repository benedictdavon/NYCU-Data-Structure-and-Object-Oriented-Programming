#pragma once
#include <iostream>
#include "LinkedList.h"
class Stack{
public:
	LinkedList List;
	void push(int num);
	void pop();
	void print();
};


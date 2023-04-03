#pragma once
#include <iostream>
#include <vector>
#include "LinkedList.h"
class Queue {
public:
	LinkedList List;
	void enqueue(int num);
	void dequeue();
	void print();
};
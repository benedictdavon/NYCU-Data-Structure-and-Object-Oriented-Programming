#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class sort {
	vector<int> insertion;
	vector<int> bucket;
public:
	void process(const char* fileName);
	void InsertionSort();
	void BucketSort();
	void BinarySearch(int, int);
	void output(int, int);
	int getBinarySearch(vector<int> num, int start, int end, int target); // revisi dr binary searchku yg salah
};
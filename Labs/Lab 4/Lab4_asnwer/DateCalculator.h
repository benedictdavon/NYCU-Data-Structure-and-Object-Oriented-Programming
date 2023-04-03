#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class DateCalculator {
private:
	int daysMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int year;
	int month;
	int day;
	int changeDays;
	char oprt;
	//You can add any variable if you need.
public:
	DateCalculator();
	void readFile(const char *filename);
	void getDate(string date);
	void add();
	void minus();
	bool isLeapYear(int year_);
	void showDay();
	//You can add any function if you need.
};
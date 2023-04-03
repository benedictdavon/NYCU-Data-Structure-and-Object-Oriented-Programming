#include "DateCalculator.h"

using namespace std;

DateCalculator::DateCalculator():year(2000), month(1), day(1), changeDays(0), oprt(' '){}


void DateCalculator::readFile(const char *fileName) {
	//TODO:
	//Read the data from the txt file.
	//The file is in the Lab4_template/Lab4.
	// 
	//Hint: You can use get() to get a character in ifstream.
	//      You can use getline() to get one line in the txt file.
	//      You can use atoi() or stoi() to change variable type from string to int
	ifstream input;
	input.open(fileName);
	string date;

	while (1) {
		if (input.eof())
			break;
		input >> oprt >> date >> changeDays;
		getDate(date);
		
		switch (oprt) {
			case '+':
				add();
				break;
			case '-':
				minus();
				break;
			default:
				break;
		}
		showDay();
	}

	input.close();
}

void DateCalculator::getDate(string date) {
	year = stoi(date.substr(0, 4));
	month = stoi(date.substr(5, 2));
	day = stoi(date.substr(8, 2));
}

void DateCalculator::add() {
	//TODO:
	//Calculate the date add the changeDays.
	day += changeDays;

	if (isLeapYear(year))
		daysMonth[2] = 29;
	else
		daysMonth[2] = 28;
	
	while (day > daysMonth[month]){
		day -= daysMonth[month];
		month++;
		if (month > 12) {
			month = 1;
			year++;
			if (isLeapYear(year))
				daysMonth[2] = 29;
			else
				daysMonth[2] = 28;
		}
	}
}

void DateCalculator::minus() {
	//TODO:
	//Calculate the date minus the changeDays.
	/*
	Ex: 
	Date:	2016/02/10 -200 
			2015/02/10 (I minus 1 year)
			2015/02/10 +165 (I add 365 - 200)
	Result: 2015/07/25

	Basicly 2016/02/10 -200 is the same as 2015/02/10 +165
	But if it's leap year I add 1 day to it.
	*/

	if (isLeapYear(year) && month > 2 && changeDays >= 365) {
		day++;
		daysMonth[2] = 29;
	}
	else
		daysMonth[2] = 28;

	year -= changeDays / 365 + 1;
	changeDays = 365 * ((changeDays / 365) + 1) - changeDays;
	day += changeDays;

	while (day > daysMonth[month]) {
		day -= daysMonth[month];
		month++;
		if (month > 12) {
			month = 1;
			year++;
			if (isLeapYear(year)) {
				daysMonth[2] = 29;
				day++;
			}
			else
				daysMonth[2] = 28;
		}
	}
}

bool DateCalculator::isLeapYear(int year_) {
	//TODO: 
	//Determine whether year_ is a leap year.
	if ((year_ % 100 != 0 && year_ % 4 == 0) || year_ % 400 == 0)
		return true;

	return false;
}

void DateCalculator::showDay() {
	//TODO: 
	//The function output the date on the screen.
	//Hint: You can use setw() to set the length of the number.
	//      You can use setfill('c') to fill 'c' to the empty space.
	//      Two functions of above is in iomanip header file. 
	cout << year << "/"
		<< setfill('0') << setw(2)
		<< month << "/"
		<< setfill('0') << setw(2)
		<< day << endl;
}
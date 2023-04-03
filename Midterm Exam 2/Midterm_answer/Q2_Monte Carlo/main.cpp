/*
*	Spring 2022
*	OOP Midterm Two
*	Question
*/
#include <iostream>
#include <vector>
#include <time.h>			// time
using namespace std;

namespace {
	double getRandomNumber(double minValue, double maxValue) {
		return minValue 
			+ (maxValue- minValue) * rand() / (double) RAND_MAX;
	}
};
class MonteCarlo {
protected:
	vector<double> xArr;
	vector<double> yArr;
	int numSamples;			// total number of samples to be generated 
	double area;			// use this variable to store the area in each case
public:
	MonteCarlo() {
		numSamples = 0;
		area = 0;
	}

	void go() {
		bool flg = true;
		while (flg) {
			int option;
			showOptions();
			cout << "Please enter an option:";
			cin >> option;
			flg = handleOption( option );

		}
	}
protected:
	void quit();
	bool handleOption(int option);
	void showOptions() const;
	//
	void showArea() const;
	//
	void inputNumberOfSamples(const char* msg);
	void handle_CaseOne();
	void handle_CaseTwo();
	void handle_CaseThree();
	//
	void generateSamplesFor_CaseOne();
	void computeAreaFor_CaseOne();
	//
	void generateSamplesFor_CaseTwo();
	void computeAreaFor_CaseTwo();
	//

	void generateSamplesFor_CaseThree();
	void computeAreaFor_CaseThree();
	//
};

void MonteCarlo::showArea() const
{
	cout << "Area:" << area << endl;
}

void MonteCarlo::showOptions() const
{
	cout << "Key usage====================" << endl;
	cout << "0: Quit the program" << endl;
	cout << "1: Case One" << endl;
	cout << "2: Case Two" << endl;
	cout << "3: Case Three" << endl;
}


// This function inputNumberOfSamples( const char * ) is correct.
// It asks the user to inpute the number of samples that will be generated.
void MonteCarlo::inputNumberOfSamples(const char *msg)
{
	cout << "Case:" << msg << endl;
	cout << "Please input the number of samples:";
	cin >> numSamples;
}

// This function handleOption( int ) is correct.
bool MonteCarlo::handleOption(int option)
{
	bool flg = true;
	switch (option) {
	case 0:
		quit();
		flg = false;
		break;
	case 1:
		handle_CaseOne();
		break;
	case 2:
		handle_CaseTwo();
	break;
	case 3:
		handle_CaseThree();
		break;
	}
	return flg;
}

void MonteCarlo::quit()
{
	/*
	* Please modify or add your own stuff
	*/
	cout << "The program will be terminated soon...." << endl;
	cout << "Student Name: Benedict Davon Martono" << endl;
	cout << "Student ID: 110550201" << endl;
}
//
void MonteCarlo::generateSamplesFor_CaseOne() {
	/*
	* Please modify or add your own stuff
	*/
	double xmin = 0;
	double xmax = 1;
	double ymin = 0;
	double ymax = 1;
	xArr.clear();
	yArr.clear();
	for (int i = 0; i < numSamples; ++i) {
		double x = 0.0;
		double y = 0.0;

		x = getRandomNumber(xmin, xmax);
		y = getRandomNumber(ymin, ymax);
		xArr.push_back(x);
		yArr.push_back(y);
	}
}

void MonteCarlo::computeAreaFor_CaseOne() {
	int numInteriorPoints = 0;
	int total_sample_num = xArr.size();
	double x, y;
	for (int i = 0; i < xArr.size(); i++) {
	/*
	* Please modify or add your own stuff
	*/
		x = xArr[i];
		y = yArr[i];
		//cout << "x: " << x << " y: " << y << endl;
		if (x * x + y * y <= 1.0)
			numInteriorPoints++;
	}
	/*
	* Please modify or add your own stuff
	*/
	area = double(numInteriorPoints) / double(total_sample_num);// use ratio to compute the area
	// the result should be = 0.78539816339744830961566084581988
}

//
void MonteCarlo::generateSamplesFor_CaseTwo() {
	/*
	* Please modify or add your own stuff
	*/
	double xmin = 0;
	double xmax = 1;
	double ymin = 0;
	double ymax = 1;
	xArr.clear();
	yArr.clear();
	for (int i = 0; i < numSamples; ++i) {
		double x = 0.0;
		double y = 0.0;

		x = getRandomNumber(xmin, xmax);
		y = getRandomNumber(ymin, ymax);
		xArr.push_back(x);
		yArr.push_back(y);
	}
}

void MonteCarlo::computeAreaFor_CaseTwo() {
	int numInteriorPoints = 0;
	int total_sample_num = xArr.size();
	double x, y;
	for (int i = 0; i < xArr.size(); ++i) {
		/*
		* Please modify or add your own stuff
		*/
		x = xArr[i];
		y = yArr[i];
		if (x * x + y * y >= 0.5*0.5 && x * x + y * y <= 1.0)
			numInteriorPoints++;
	}
	/*
	* Please modify or add your own stuff
	*/
	area = double(numInteriorPoints) / double(total_sample_num);// use ratio to compute the area
	// the result should be = 0.58904862254808623221174563436491
}

void MonteCarlo::generateSamplesFor_CaseThree() {
	/*
	* Please modify or add your own stuff
	*/
	double xmin = 0;
	double xmax = 1;
	double ymin = 0;
	double ymax = 1;
	xArr.clear();
	yArr.clear();
	for (int i = 0; i < numSamples; ++i) {
		double x = 0.0;
		double y = 0.0;

		x = getRandomNumber(xmin, xmax);
		y = getRandomNumber(ymin, ymax);
		xArr.push_back(x);
		yArr.push_back(y);
	}
}

void MonteCarlo::computeAreaFor_CaseThree() {
	int numInteriorPoints = 0;
	int total_sample_num = xArr.size();
	double x, y;
	// union c2 and c3 = (area of 1/4 circle with radius 0.5 - 1/2 * 0.5 * 0.5)*2
	double c2c3union = 0.14269908169872415480783042290994; 
	// area of c2 c3 = area of 1/4 square + 2*area of 1/4 circle with the radius 0.5
	double c2c3area = 0.64269908169872415480783042290994;
	for (int i = 0; i < xArr.size(); ++i) {
		/*
		* Please modify or add your own stuff
		*/
		x = xArr[i];
		y = yArr[i];
		
		
		if (x * x + y * y <= c2c3union || (x * x + y * y >= c2c3area && x * x + y * y <= 1))
			numInteriorPoints++;
	}
	/*
	* Please modify or add your own stuff
	*/
	area = double(numInteriorPoints)/double(total_sample_num);					// use ratio to compute the area
	// the area should be 0.39269908169872415480783042290994
}

//
void MonteCarlo::handle_CaseOne()
{
	inputNumberOfSamples("One");
	generateSamplesFor_CaseOne();
	computeAreaFor_CaseOne();
	showArea();
}

void MonteCarlo::handle_CaseTwo()
{
	inputNumberOfSamples("Two");
	generateSamplesFor_CaseTwo();
	computeAreaFor_CaseTwo();
	showArea();
}

void MonteCarlo::handle_CaseThree()
{
	inputNumberOfSamples("Three");
	generateSamplesFor_CaseThree();
	computeAreaFor_CaseThree();
	showArea();
}
int main(int argc, char* argv[])
{
	MonteCarlo m;
	m.go();
	system("pause");
	return 0;
}



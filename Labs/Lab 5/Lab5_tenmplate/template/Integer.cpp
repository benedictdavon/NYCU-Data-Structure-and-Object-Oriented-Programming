#include "Integer.h"

Integer::Integer() {}


void Integer::readFile(const char* fileName) {
	ifstream inputFile;
	//TODO: Read the input file here.
}

void Integer::reset() {
	//TODO: reset all the data member.
}


void Integer::operator +(Integer b) {
	//TODO: perform + opearion overloading
}
void Integer::operator -(Integer b) {
	//TODO: perform - opearion overloading
}

ifstream& operator >> (ifstream& in, Integer& i) {
	//TODO: perform input overloading
}
ostream& operator << (ostream& out, const Integer& i) {
	//TODO: perform output overloading
}

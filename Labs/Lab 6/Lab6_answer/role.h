#pragma once
#ifndef ROLE_H
#include <string>
using namespace std;
class Role {
public:
	Role(string, int, int, int);
	string getID();
	void printAllInfo();
	virtual void ShowRole() = 0; //if you want to overwrite the function in the derived class

private:
	string ID;
	int level;
	int money;
	int hp;

};
#endif
#include "role.h"
#include <string>
#include <iostream>
using namespace std;

Role::Role(string roleID, int roleLevel, int roleMoney, int roleHp): ID(roleID), level(roleLevel), money(roleMoney), hp(roleHp){

}
string Role::getID() {
	// TODO : refer to spec
	return ID;
}
void Role::printAllInfo() {
	// TODO : refer to spec
	cout << "ID is: " << ID << endl
		<< "Level is: " << level << endl
		<< "Money is: " << money << endl
		<< "HP is: " << hp << endl;
}



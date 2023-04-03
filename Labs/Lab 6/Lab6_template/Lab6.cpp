#include "role.h"
#include "magician.h"
#include "warrior.h"
#include "archer.h"
#include "staff.h"
#include <iostream>
#include <string>
using namespace std;



int main() {
	
	// TODO : Read the file
	// 1. Read the input file to get the imformation
	
	// TODO : Create the Role according to the input file
	// 1. Create the role
	// 2. Print this role's Infomation
	// 3. Show Role ( refer to spec )
	// Example :
	// -------------------------------------------------------
	// Role* warrior = new Warrior( warrior's Name, warrior's Level, warrior's Money, warrior's HP);
	// warrior->printAllInfo();
	// warrior->ShowRole();
	// cout << endl;
	// 
	// Role* archer = new Archer(archer's Name, archer's Level, archer's Money, archer's HP);
	// archer->printAllInfo();
	// archer->ShowRole();
	// cout << endl;
	// 
	// Role* magician = new Magician(magician's Name, magician's Level, magician's Money, magician's HP);
	// magician->printAllInfo();
	// magician->ShowRole();
	// cout << endl;
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles


	Staff* staff = new Staff("flame");
	cout << "Checking whether the role can equip a staff.." << endl;

	//
	// TODO : Check wheather all characters can get staff or not
	// Example :
	// -------------------------------------------------------
	// staff->equipable(warrior);
	// staff->equipable(archer);
	// staff->equipable(magician);
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles
	cout << endl;




	system("PAUSE");
	return 0;
}
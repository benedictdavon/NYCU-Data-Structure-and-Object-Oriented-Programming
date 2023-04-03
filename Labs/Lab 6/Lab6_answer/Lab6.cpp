#include "role.h"
#include "magician.h"
#include "warrior.h"
#include "archer.h"
#include "staff.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	
	// TODO : Read the file
	// 1. Read the input file to get the imformation
	ifstream input;
	input.open("input2.txt");

	if (!input) {
		cout << "Invalid File." << endl;
		return 0;
	}
	int row;

	string id, temp, lv, money, hp, role;
	getline(input, temp);
	vector<string> name, roleName;
	row = stoi(temp);
	for (int i = 0; i < row; i++) {
		Role* className;
		getline(input, id, ','); getline(input, temp, ' ');
		getline(input, role, ','); getline(input, temp, ' ');
		getline(input, lv, ','); getline(input, temp, ' ');
		getline(input, money, ','); getline(input, temp, ' ');
		getline(input, hp); 
		name.push_back(id);
		roleName.push_back(role);
		if (role == "Warrior") {
			className = new Warrior(id, stoi(lv), stoi(money), stoi(hp));
		
			className->printAllInfo();
			className->ShowRole();
			cout << endl;
		} else if (role == "Archer") {
			className = new Archer(id, stoi(lv), stoi(money), stoi(hp));
			className->printAllInfo();
			className->ShowRole();
			cout << endl;
		} else if (role == "Magician") {
			className = new Magician(id, stoi(lv), stoi(money), stoi(hp));
			className->printAllInfo();
			className->ShowRole();
			cout << endl;
		} 
	}

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
	
	for (int i = 0; i < row; i++) {
		if (roleName[i] == "Warrior") {
			Role* temp = new Warrior(name[i], 0, 0, 0);
			staff->equipable(temp);
		}
		else if (roleName[i] == "Archer") {
			Role* temp = new Archer(name[i], 0, 0, 0);
			staff->equipable(temp);
		}
		else if (roleName[i] == "Magician") {
			Role* temp = new Magician(name[i], 0, 0, 0);
			staff->equipable(temp);
		}
		
	}
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles
	cout << endl;

	system("PAUSE");
	return 0;
}
#include "Integer.h"

int toDec(char num) {
	switch (num) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return num - '0';
			break;
		case 'a':
		case 'A':
			return 10;
			break;
		case 'b':
		case 'B':
			return 11;
			break;
		case 'c':
		case 'C':
			return 12;
			break;
		case 'd':
		case 'D':
			return 13;
			break;
		case 'e':
		case 'E':
			return 14;
			break;
		case 'f':
		case 'F':
			return 15;
			break;
	}
}

Integer::Integer(string number) 
{
	//TODO: read the string and construct the huge integer
	for (int i = 0; i < number.length(); i++) {
		num.push_back(toDec(number[i]));
	}
	reverse(num.begin(), num.end());
}

bool existAlph(vector<int> number) {
	for (int i = 0; i < number.size(); i++) {
		if (number[i] > 9)
			return true;
	}

	return false;
}

Integer Integer::operator +(const Integer& b) {
	//TODO: perform + opearion overloading
	Integer answer("");
	vector <int> num1, num2;
	// After we convert the hexadecimal to decimal for each number (e31a -> 14 3 1 11),
	// we use mod and div with base 16
	// Ex:
	// 9c9 + 999
	// 9 c 9 -> 9 12  9
	// 9 9 9 -> 9  9  9
	//         ________ +
	//         18 21 18 -> we mod 18 with 16
	//               16 
	//         ________ -
	//         18 21  2 
	//             1    -> add 18 / 16 to the next number
	//         ________ +
	//         18 22  2 
	//            16    -> we mod 22 with 16
	//         ________ -
	//         18  6  2
	//          1		-> add 22 / 16 to the next number
	//         ________ +
	//         19  6  2 -> we mod 19 with 16
	//         16 
	//         ________ -
	//       0  3  6  2
	//       1			-> add 19 / 16 to the next number
	//      ___________ +
	//       1  3  6  2 -> final result
	num1 = this->num;
	num2 = b.num;

	while (num1.size() < b.num.size()) {
		num1.insert(num1.end(), 0);
	}
	while (num2.size() < num1.size()) {
		num2.insert(num2.end(), 0);
	}

	for (int i = 0; i < num1.size(); i++) {
		//cout << num1[i] << " + " << num2[i] << endl;
		if (i >= answer.num.size()) {
			answer.num.push_back(num1[i] + num2[i]);
		}
		else {
			answer.num[i] += num1[i] + num2[i];
		}

		//cout << "vector size: " << answer.num.size() << endl;
		if (answer.num[i] > 15) {
			if (i + 1 >= answer.num.size()) {
				answer.num.push_back(answer.num[i] / 16);
				//cout << "answer.num[i] / 16: " << answer.num[i] / 16 << endl;
			}
			else {
				answer.num[i + 1] += answer.num[i] / 16;
				//cout << "answer.num[i+1]: " << answer.num[i + 1] << endl;
			}
			answer.num[i] = answer.num[i] % 16;
			//cout << "answer.num[i] % 16: " << answer.num[i] % 16 << endl;
		}
	}


	return answer;
}

Integer Integer::operator -(const Integer& b) {
	//TODO: perform - opearion overloading
	Integer answer("");
	vector <int> num1, num2;
	
	// if b bigger than a
	if (this->num.size() < b.num.size()) {
		num1 = b.num;
		num2 = this->num;
		// answer must be negative because we swap the number
		answer.negative = true;
	}
	// if a bigger than b
	else if (b.num.size() < this->num.size()) {
		num1 = this->num;
		num2 = b.num;
	}
	// if they have same length
	else if (this->num.size() == b.num.size()) {
		
		// if first value of a bigger than b
		if (this->num[this->num.size()-1] > b.num[b.num.size() - 1]) {
			//cout << "Here!" << endl;
			//cout << this->num[0] << " , " << b.num[0] << endl;
			num1 = this->num;
			num2 = b.num;
		}
		// if first value of b bigger than a
		else{
			num1 = b.num;
			num2 = this->num;
			// answer must be negative because we swap the number
			answer.negative = true;
		}
	}

	if (num1 == num2) {
		answer.negative = false;
		answer.num.push_back(0);
		return answer;
	}

	while (num2.size() < num1.size()) {
		num2.insert(num2.end(), 0);
	}
	/*
	for (auto element : num1) {
		cout << element << " ";
	}
	cout << endl;
	for (auto element : num2) {
		cout << element << " ";
	}
	cout << endl;
	*/
	int temp = 0;
	for (int i = 0; i < num1.size(); i++) {
		//cout << num1[i] << " + " << num2[i] << endl;
		if (i >= answer.num.size()) {
			if (num1[i] < num2[i]) {
				temp = i;
				do {
					num1[temp] += 16;
					temp++;
					num1[temp]--;
				} while (num1[temp] < 0);
			}
			answer.num.push_back(num1[i] - num2[i]);
		}
		else {
			if (num1[i] < num2[i]) {
				temp = i;
				do {
					num1[temp + 1] += 16;
					temp++;
					num1[temp]--;
				} while (num1[temp] < 0);
			}
			answer.num[i] = num1[i] - num2[i];
		}
		//cout << "vector size: " << answer.num.size() << endl;
		if (answer.num[i] > 15) {
			if (i + 1 >= answer.num.size()) {
				answer.num.push_back(answer.num[i] / 16);
				//cout << "answer.num[i] / 16: " << answer.num[i] / 16 << endl;
			}
			else {
				answer.num[i + 1] += answer.num[i] / 16;
				//cout << "answer.num[i+1]: " << answer.num[i + 1] << endl;
			}
			answer.num[i] = answer.num[i] % 16;
			//cout << "answer.num[i] % 16: " << answer.num[i] % 16 << endl;
		}
	}

	return answer;
}

ostream& operator << (ostream& out, const Integer& i) {
	//TODO: perform output overloading
	if (i.negative)
		out << "-";
	if (i.num[0] == 0 && i.num.size() == 1) {
		out << 0;
		return out;
	}
	int index = i.num.size() - 1;
	while (i.num[index] == 0){
		index--;
	}
	for (int j = index; j >= 0; j--) {
		switch (i.num[j]) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				out << i.num[j];
				break;
			case 10:
				out << 'a';
				break;
			case 11:
				out << 'b';
				break;
			case 12:
				out << 'c';
				break;
			case 13:
				out << 'd';
				break;
			case 14:
				out << 'e';
				break;
			case 15:
				out << 'f';
				break;
			case '-':
				out << '-';
				break;
		}
	}
	
	/*
	for (auto element : i.num) {
		out << element << " ";
	}*/
	return out;
}

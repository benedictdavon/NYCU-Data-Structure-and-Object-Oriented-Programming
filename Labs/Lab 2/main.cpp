#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class PrimeFactorization {
	private:
		int num1, num2;
		int GCD;
		long long int LCM;
		vector<int> num1_factor, num2_factor;
		vector<int> primeNum;

	public:
		PrimeFactorization() {
			num1 = 0; 
			num2 = 0;
			GCD = 1; 
			LCM = 1;
			getPrimeNumber();
		}

		PrimeFactorization(int _a, int _b) {
			//TO_DO: _a means the first integer and _b means the second integer
			num1 = _a;
			num2 = _b;
			GCD = 1;
			LCM = 1;
			getPrimeNumber();
		}

		void getPrimeNumber() {
			// this function is for searching for prime number until 10.000.000
			int* prime;
			prime = new int[10000001];
			for (int i = 0; i <= 10000000; i++)
				prime[i] = 0;

			for (int i = 2; i * i <= 10000000; i++) {
				if (prime[i] == 0) {
					for (int j = i * i; j <= 10000000; j += i)
						prime[j] = 1;
				}
			}

			for (int i = 2; i <= 100000; i++)
				if (prime[i] == 0)
					primeNum.push_back(i);

			delete[] prime;
		}

		// For printing and checking our generated prime number
		void printPrimeNumber() {
			for (auto i = primeNum.begin(); i != primeNum.end(); ++i)
				cout << *i << endl;
		}

		void Get_Prime_Factorization() {
			int i = 0;
			int n1temp, n2temp;
			n1temp = num1; 
			n2temp = num2;
			do {
				while(n1temp % primeNum[i] == 0) {
					num1_factor.push_back(primeNum[i]);
					n1temp /= primeNum[i];
				}
				i++;
			} while (n1temp != 1);

			i = 0;
			do {
				while (n2temp % primeNum[i] == 0) {
					num2_factor.push_back(primeNum[i]);
					n2temp /= primeNum[i];
				} 
				i++;
			} while (n2temp != 1);
		}

		void getGCD() {
			int i, j;
			i = 0; j = 0;
			while (i != num1_factor.size() && j != num2_factor.size()) {
				if (num1_factor[i] == num2_factor[j]) {
					GCD *= num1_factor[i];
					if (i != num1_factor.size())
						i++;

					if (j != num2_factor.size())
						j++;
				}

				if (i == num1_factor.size() || j == num2_factor.size())
					break;

				if (num1_factor[i] < num2_factor[j] && i != num1_factor.size())
					i++;
				else if (num1_factor[i] > num2_factor[j] && j != num2_factor.size())
					j++;
				else if (num1_factor[i] < num2_factor[j] && j != num2_factor.size())
					j++;
				else if (num1_factor[i] > num2_factor[j] && i != num1_factor.size())
					i++;
			}
		}

		void getLCM() {
			LCM = (num1 / GCD) * num2;
		}

		void Print_Prime_Factorization() {
			//TO_DO: Print num1_factor and num2_factor.
			cout << "num1_prime_factor: ";
			for (auto i = num1_factor.begin(); i != num1_factor.end(); ++i)
				cout << *i << " ";

			cout << endl << "num2_prime_factor: ";
			for (auto i = num2_factor.begin(); i != num2_factor.end(); ++i)
				cout << *i << " ";
			cout << endl;
		}

		void Print_GCD() {
			//TO_DO: Use num1_factor and num2_factor to find GCD and print the result.
			getGCD();
			cout << "GCD: " << GCD << endl;
		}

		void Print_LCM() {
			//TO_DO: Use num1, num2, and GCD to find LCM and print the result.
			getLCM();
			cout << "LCM: " << LCM << endl;
		}

};

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;

		cout << "num1 = " << a << endl;
		cout << "num2 = " << b << endl;

		PrimeFactorization PF(a, b);
		PF.Get_Prime_Factorization();
		PF.Print_Prime_Factorization();
		PF.Print_GCD();
		PF.Print_LCM();

		cout << endl;
	}

	system("PAUSE");
	return 0;
}

#pragma once
#include <iostream>
#include <vector>
#include <string> 
using namespace std;

class Matrix_Shape {
public:
	int m, n;
	Matrix_Shape(int m, int n) :m(m), n(n) {}
	bool operator== (const Matrix_Shape& other)const { return m == other.m && n == other.n; }
	bool operator!= (const Matrix_Shape& other)const { return m != other.m || n != other.n; }
	bool CanMultiply(const Matrix_Shape& other)const { return n == other.m; }
	string ToString()const { return "(" + to_string(m) + "," + to_string(n) + ")"; }
};

class Matrix {
private:
	Matrix_Shape mShape;
	vector<vector<int> > M;
public:

	bool isValid = true;

	// Output matrix value with format { mShape.m, mShape.n, M[0][0], M[0][1], ... }
	vector<int> Flattern() const
	{
		vector<int> rawData;
		rawData.push_back(mShape.m);
		rawData.push_back(mShape.n);
		for (size_t i = 0; i < mShape.m; i++)
		{
			for (size_t j = 0; j < mShape.n; j++)
			{
				rawData.push_back(M[i][j]);
			}
		}
		return rawData;
	}
	
	// An empty matrix is an invalid matrix
	Matrix() :isValid(false), mShape(0, 0) {}

	Matrix(const int m, const int n, const vector<int>& rawData) :mShape(m, n)
	{
		// TODO: Construct the matrix
		vector <vector <int>> temp(m, vector<int>(n, 0));
		M = temp;
		int count = 0;
		//cout << "rawdata size: " << rawData.size() << endl;
		if (rawData.size() != 0)
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					//cout << "i: " << i << " j: " << j;
					M[i][j] = rawData[count];
					count++;
					//cout << " m[i][j]: " << M[i][j] << endl;
				}
			}
	}


	static Matrix Add(const Matrix& a, const Matrix& b)
	{
		if ((a.mShape != b.mShape) || !a.isValid || !b.isValid)
		{
			cout << "operands could not be broadcast together with shapes " << a.mShape.ToString() << " " << b.mShape.ToString() << endl;
			return Matrix();
		}
		// TODO: Add matrix A with matrix B

		return a + b;
	}

	static Matrix Minus(const Matrix& a, const Matrix& b)
	{
		if (a.mShape != b.mShape || !a.isValid || !b.isValid)
		{
			cout << "operands could not be broadcast together with shapes " << a.mShape.ToString() << " " << b.mShape.ToString() << endl;
			return Matrix();
		}

		// TODO: Minus matrix A with matrix B

		return a-b;
	}

	static Matrix Transpose(const Matrix& a)
	{
		if (!a.isValid)
		{
			cout << "matrix is not valid " << endl;
			return Matrix();
		}
		vector<int> rawData;
		// TODO: Transpose matrix A
		for (int i = 0; i < a.mShape.n; i++) {
			for (int j = 0; j < a.mShape.m; j++) {
				rawData.push_back(a.M[j][i]);
			}
		}
		//	 0 1 2 
		// _______
		// 0|0 1 2
		// 1|3 4 5
		//   0 1
		// 0|0 3
		// 1|1 4
		// 2|2 5
		return Matrix(a.mShape.n, a.mShape.m, rawData);
	}

	static Matrix Multiply(const Matrix& a, const Matrix& b)
	{
		if (!a.mShape.CanMultiply(b.mShape) || !a.isValid || !b.isValid)
		{
			cout << "operands could not be broadcast together with shapes " << a.mShape.ToString() << " " << b.mShape.ToString() << endl;
			return Matrix();
		}
		vector<int> rawData;

		// TODO: Multiply matrix A with matrix B
		int temp = 0;
		for (int i = 0; i < a.mShape.m; i++) {
			for (int j = 0; j < b.mShape.n; j++) {
				for (int k = 0; k < a.mShape.n; k++) {
					temp += a.M[i][k] * b.M[k][j];
				}
				rawData.push_back(temp);
				temp = 0;
			}
		}

		return Matrix(a.mShape.m, b.mShape.n, rawData);
	}

	Matrix operator+(const Matrix& b) const;
	Matrix operator-(const Matrix& b) const;
	Matrix Deepcopy() const;
	void Print();

};
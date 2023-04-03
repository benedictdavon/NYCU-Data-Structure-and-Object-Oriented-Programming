#include "Matrix.h"

void Matrix::Print()
{
	for (int i = 0; i < mShape.m; i++) {
		for (int j = 0; j < mShape.n; j++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
	// TODO: Print the Matrix
}

Matrix Matrix::operator+(const Matrix& b) const
{
	// TODO: Overloading the operator
	vector <int> temp;
	for (int i = 0; i < mShape.m; i++) {
		for (int j = 0; j < mShape.n; j++) {
			//cout << "M[i][j]: " << M[i][j] << " b.M[i][j]: " << b.M[i][j] << endl;
			temp.push_back(M[i][j] + b.M[i][j]);
			//cout << "+: " << M[i][j] + b.M[i][j] << endl;
		}
	}
	Matrix ans;
	ans = Matrix(mShape.m, mShape.n, temp);
	return ans;
}
Matrix Matrix::operator-(const Matrix& b) const
{
	// TODO: Overloading the operator
	vector <int> temp;
	for (int i = 0; i < mShape.m; i++) {
		for (int j = 0; j < mShape.n; j++) {
			//cout << "M[i][j]: " << M[i][j] << " b.M[i][j]: " << b.M[i][j] << endl;
			temp.push_back(M[i][j] - b.M[i][j]);
			//cout << "+: " << M[i][j] + b.M[i][j] << endl;
		}
	}
	Matrix ans;
	ans = Matrix(mShape.m, mShape.n, temp);
	return ans;
}

Matrix Matrix::Deepcopy() const
{
	// TODO: return Deepcopy version of that matrix
	return *this;
}

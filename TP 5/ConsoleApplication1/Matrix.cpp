#include "Matrix.h"


Matrix::Matrix(void)
{
}


Matrix::~Matrix(void)
{
}

int Matrix::at(int i, int j) const{
	return values[i][j];
}

int& Matrix::at(int i, int j) {
	return values[i][j];
}
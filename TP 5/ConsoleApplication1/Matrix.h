#pragma once
#include <vector>
class Matrix
{
private :
	std::vector<std::vector<int>> values;
public:
	Matrix(void);
	~Matrix(void);

	int at(int i, int j) const;
	int& at(int i, int j);
};


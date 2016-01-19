#pragma once
#include <map>
#include <vector>
#include "Operators.h"
#include "struct.h"

class Grid
{
public:
	std::vector<Operators*> ops;
	int nbX;
	int nbY;
	int nbZ;
	float voxelSize;
	std::map<int, int> voxels;
	point3 base;

	Grid();
	Grid(std::vector<Operators*> &operators, float size);
	~Grid();
	void draw();
	void removeMatter(int i, int j, int k);
	void addMatter(int i, int j, int k);
};


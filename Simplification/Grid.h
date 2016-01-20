#pragma once
#include <map>
#include <vector>
#include "struct.h"
#include "Mesh.h"

class Grid
{
public:
	Mesh& mesh;
	int nbX;
	int nbY;
	int nbZ;
	float voxelSize;
	std::map<int, vector<int>> voxels;
	point3 base;

	Grid();
	Grid(Mesh& m, float size);
	~Grid();
	Mesh getSimplifiedMesh();
};


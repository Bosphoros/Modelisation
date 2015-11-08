#pragma once
#include <vector>
#include "struct.h"

class Mesh
{
public:
	std::vector<point3> points;
	std::vector<int> faces;
	std::vector<point3> normales;
	int edgesNumb;

	Mesh();
	Mesh(std::vector<point3> pts, std::vector<int> fcs, std::vector<point3> nrml);
	void draw();
	void center();
	void normalize();
	void norms();
	void stats(int& edgesNumb);
	void randomDisparition();
	~Mesh();
};


#include "Grid.h"
#include <GL/glut.h>
#include <cfloat>
#include <iostream>

Grid::Grid() : mesh(Mesh())
{
}

Grid::Grid(Mesh& m, float size) : mesh(m), voxelSize(size)
{
	float minX = FLT_MAX, maxX = FLT_MIN, minY = FLT_MAX, maxY = FLT_MIN, minZ = FLT_MAX, maxZ = FLT_MIN;
	for (int i = 0; i < m.points.size(); ++i) {
		minX = std::fmin(minX, m.points.at(i).x);
		maxX = std::fmax(maxX, m.points.at(i).x);
		minY = std::fmin(minY, m.points.at(i).y);
		maxY = std::fmax(maxY, m.points.at(i).y);
		minZ = std::fmin(minZ, m.points.at(i).z);
		maxZ = std::fmax(maxZ, m.points.at(i).z);
	}
	float coef = 1 / voxelSize;

	nbX = (std::abs(maxX - minX))*coef + 1;
	nbY = (std::abs(maxY - minY))*coef + 1;
	nbZ = (std::abs(maxZ - minZ))*coef + 1;

	base = point3(minX, minY, minZ);

	float dif = voxelSize * 0.5;

	for (float i = 0; i < nbX; ++i) {
		for (float j = 0; j < nbY; ++j) {
			for (float k = 0; k < nbZ; ++k) {
				for (int o = 0; o < m.points.size(); ++o) {
					int x = (m.points.at(o).x - base.x) * coef;
					int y = (m.points.at(o).y - base.z) * coef;
					int z = (m.points.at(o).z - base.z) * coef;
					voxels[x*nbX*nbY + y*nbY + z].push_back(o);
				}
			}
		}
	}
}

Grid::~Grid()
{
}

Mesh Grid::getSimplifiedMesh()
{
	std::map<int, point3> correspondances;
	std::map<int, int> corrMin;
	
	for (float i = 0; i < nbX; ++i) {
		for (float j = 0; j < nbY; ++j) {
			for (float k = 0; k < nbZ; ++k) {
				point3 tmp(0, 0, 0);
				int min = INT_MAX;
				std::vector<int> pts = voxels[i*nbX*nbY + j*nbY + k];
				int s = pts.size();
				for (int o = 0; o < s; ++o) {
					min = std::fmin(min, pts.at(o));
					tmp = tmp + mesh.points.at(pts.at(o));
				}
				tmp /= s;
				for (int o = 0; o < pts.size(); ++o) {
					correspondances[pts.at(o)] = tmp;
					corrMin[pts.at(o)] = min;
				}
			}
		}
	}

	std::vector<point3> pointsMesh;
	std::vector<int> faces;
	for (std::map<int, point3>::iterator it = correspondances.begin(); it != correspondances.end(); ++it) {
		pointsMesh.push_back(it->second);
	}
	for (int i = 0; i < mesh.faces.size(); i += 3) {
		int i1 = corrMin[mesh.faces.at(i)];
		int i2 = corrMin[mesh.faces.at(i+1)];
		int i3 = corrMin[mesh.faces.at(i+2)];
		if (i1 != i2 && i1 != i3 && i2 != i3) {
			faces.push_back(corrMin[mesh.faces.at(i)]);
			faces.push_back(corrMin[mesh.faces.at(i+1)]);
			faces.push_back(corrMin[mesh.faces.at(i+2)]);
		}
	}
	std::vector<point3> normales;
	
	return Mesh(pointsMesh, faces, normales);
}



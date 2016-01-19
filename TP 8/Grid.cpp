#include "Grid.h"
#include <GL/glut.h>
#include <cfloat>
#include <iostream>

Grid::Grid()
{
}

Grid::Grid(std::vector<Operators*>& operators, float size) : ops(operators), voxelSize(size)
{
	float minX = FLT_MAX, maxX = FLT_MIN, minY = FLT_MAX, maxY = FLT_MIN, minZ = FLT_MAX, maxZ = FLT_MIN;
	for (int i = 0; i < ops.size(); ++i) {
		minX = std::fmin(minX, ops.at(i)->minExtentX());
		maxX = std::fmax(maxX, ops.at(i)->maxExtentX());
		minY = std::fmin(minY, ops.at(i)->minExtentY());
		maxY = std::fmax(maxY, ops.at(i)->maxExtentY());
		minZ = std::fmin(minZ, ops.at(i)->minExtentZ());
		maxZ = std::fmax(maxZ, ops.at(i)->maxExtentZ());
	}
	float coef = 1 / voxelSize;

	nbX = (std::abs(maxX - minX))*coef + 1;
	nbY = (std::abs(maxY - minY))*coef + 1;
	nbZ = (std::abs(maxZ - minZ))*coef + 1;

	//voxels.resize(nbX*nbY*nbZ);

	base = point3(minX, minY, minZ);

	float dif = voxelSize * 0.5;

	for (float i = 0; i < nbX; ++i) {
		for (float j = 0; j < nbY; ++j) {
			for (float k = 0; k < nbZ; ++k) {
				point3 tmp(base.x + i*voxelSize + dif, base.y + j * voxelSize + dif, base.z + k*voxelSize + dif);
				for (int o = 0; o < ops.size(); ++o) {
					if(ops.at(o)->isInside(tmp))
						voxels[i*nbX*nbY + j * nbY + k] = 1;
				}
			}
		}
	}
}

Grid::~Grid()
{
}

void drawPoint(point3& p) {
	glBegin(GL_POINTS);
		glVertex3f(p.x, p.y, p.z);
	glEnd();
}

void drawFace(point3& p1, point3& p2, point3& p3, point3& p4, point3& normal) {
	glNormal3f(normal.x, normal.y, normal.z);
	glBegin(GL_TRIANGLES);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}


void drawCube(point3& p, float dif) {
	point3 p1(p.x - dif, p.y - dif, p.z - dif);
	point3 p2(p.x + dif, p.y - dif, p.z - dif);
	point3 p3(p.x + dif, p.y - dif, p.z + dif);
	point3 p4(p.x - dif, p.y - dif, p.z + dif);
	point3 p5(p.x - dif, p.y + dif, p.z - dif);
	point3 p6(p.x + dif, p.y + dif, p.z - dif);
	point3 p7(p.x + dif, p.y + dif, p.z + dif);
	point3 p8(p.x - dif, p.y + dif, p.z + dif);

	point3 up(0, 1, 0);
	point3 down(0, -1, 0);
	point3 right(1, 0, 0);
	point3 left(-1, 0, 0);
	point3 forward(0, 0, 1);
	point3 backward(0, 0, -1);

	drawFace(p1, p4, p3, p2, down);
	drawFace(p5, p6, p7, p8, up);
	drawFace(p1, p2, p6, p5, backward);
	drawFace(p4, p8, p7, p3, forward);
	drawFace(p1, p5, p8, p4, left);
	drawFace(p2, p6, p7, p3, right);
}

void Grid::draw()
{
	float dif = voxelSize * 0.5;
	for (float i = 0; i < nbX; ++i) {
		for (float j = 0; j < nbY; ++j) {
			for (float k = 0; k < nbZ; ++k) {
				if (voxels[i * nbX*nbY + j * nbY + k] == 1) {
					if(voxels[(i+1) * nbX*nbY + j * nbY + k] != 1 || voxels[(i - 1) * nbX*nbY + j * nbY + k] != 1 || voxels[i * nbX*nbY + (j+1) * nbY + k] != 1 || voxels[i * nbX*nbY + (j-1) * nbY + k] != 1 || voxels[i * nbX*nbY + j * nbY + k + 1] != 1 || voxels[i * nbX*nbY + j * nbY + k - 1] != 1)
					drawCube(point3(base.x + i * voxelSize, base.y + j * voxelSize, base.z + k * voxelSize), dif);
				}
			}
		}
	}
}

void Grid::removeMatter(int i, int j, int k)
{
	voxels[i*nbX*nbY + j * nbY + k] = 0;
}

void Grid::addMatter(int i, int j, int k)
{
	voxels[i*nbX*nbY + j * nbY + k] = 1;
}

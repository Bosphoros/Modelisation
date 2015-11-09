#include <map>
#include <algorithm>
#include "Mesh.h"
#include "glut.h" 

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<point3> pts, std::vector<int> fcs, std::vector<point3> nrml) : points(pts), faces(fcs), normales(nrml), edgesNumb(0)
{

}

void Mesh::draw() {
	int taille = faces.size();
	int face = 0;
	for(int i = 0; i < taille; i += 3) {
		point3 un = points.at(faces.at(i));
		point3 deux = points.at(faces.at(i+1));
		point3 trois = points.at(faces.at(i+2));
		if(face < normales.size())
			glNormal3d(normales.at(face).x, normales.at(face).y, normales.at(face).z);
		glBegin(GL_TRIANGLES);
			glVertex3d(un.x,un.y,un.z);
			glVertex3d(deux.x,deux.y,deux.z);
			glVertex3d(trois.x, trois.y, trois.z);
		glEnd();
		++face;
	}
}

void Mesh::center() {
	double moyX = 0;
	double moyY = 0;
	double moyZ = 0;
	int nb = points.size();
	for(int i = 0; i < nb; ++i) {
		point3 p = points.at(i);
		moyX += p.x;
		moyY += p.y;
		moyZ += p.z;
	}
	moyX /= nb;
	moyY /= nb;
	moyZ /= nb;

	for(int i = 0; i < nb; ++i) {
		point3& p = points[i];
		p.x -= moyX;
		p.y -= moyY;
		p.z -= moyZ;
	}
}

void Mesh::normalize() {
	double max = 0;
	int nb = points.size();
	for(int i = 0; i < nb; ++i) {
		point3 p = points.at(i);
		if(max <abs(p.x)) max = abs(p.x);
		if(max <abs(p.y)) max = abs(p.y);
		if(max <abs(p.z)) max = abs(p.z);
	}

	for(int i = 0; i < nb; ++i) {
		point3& p = points[i];
		p.x /= max;
		p.y /= max;
		p.z /= max;
	}

	/*double min = 50;
	for (int i = 0; i < nb; ++i) {
		point3 p = points.at(i);
		if (max <p.x) max = p.x;
		if (max <p.y) max = p.y;
		if (max <p.z) max = p.z;
		if (min >p.x) min = p.x;
		if (min >p.y) min = p.y;
		if (min >p.z) min = p.z;
	}

	std::cout << min << " > " << max << std::endl;*/
}

void Mesh::norms() {
	normales.resize(faces.size()/3);
	for(int i = 0; i < faces.size(); i += 3) {
		point3 un = points.at(faces.at(i));
		point3 deux = points.at(faces.at(i+1));
		point3 trois = points.at(faces.at(i+2));

		point3 v1(deux.x - un.x, deux.y - un.y, deux.z - un.z);
		point3 v2(trois.x - un.x, trois.y - un.y, trois.z - un.z);

		point3 n(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y* v2.x);
		double l = sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
		n /= l;
		normales[i/3] = n;
	}
}

void Mesh::stats()
{
	map<int, map<int, int>> verticesUses;
	map<int, int> edges;
	for (int i = 0; i < faces.size(); i += 3) {
		int un = faces[i];
		int deux = faces[i + 1];
		int trois = faces[i + 2];
		
		edges[max<int>(un, deux)*max<int>(un, deux) + 2 * min<int>(un, deux)]++;
		edges[max<int>(un, trois)*max<int>(un, trois) + 2 * min<int>(un, trois)]++;
		edges[max<int>(trois, deux)*max<int>(trois, deux) + 2 * min<int>(trois, deux)]++;

		if (verticesUses.count(un) == 0) {
			map<int, int> sub;
			sub[deux] = 1;
			sub[trois] = 1;
			verticesUses[un] = sub;
		}
		else {
			verticesUses[un][deux]++;
			verticesUses[un][trois]++;
		}

		if (verticesUses.count(deux) == 0) {
			map<int, int> sub;
			sub[un] = 1;
			sub[trois] = 1;
			verticesUses[deux] = sub;
		}
		else {
			verticesUses[deux][un]++;
			verticesUses[deux][trois]++;
		}

		if (verticesUses.count(trois) == 0) {
			map<int, int> sub;
			sub[deux] = 1;
			sub[un] = 1;
			verticesUses[trois] = sub;
		}
		else {
			verticesUses[trois][deux]++;
			verticesUses[trois][un]++;
		}
	}

	int min = 50;
	int max = -1;
	int countNot2 = 0;


	for (std::map<int, map<int, int>>::iterator it = verticesUses.begin(); it != verticesUses.end(); ++it) {
		if ((int)it->second.size() > max) {
			max = it->second.size();
		}
		if (it->second.size() < min) {
			min = it->second.size();
		}
	}

	for (std::map<int, int>::iterator it = edges.begin(); it != edges.end(); ++it) {
		if (it->second < 2) {
			countNot2++;
		}
	}

	std::cout << "Vertices : " << points.size() << std::endl
		<< "Edges : " << edges.size() << std::endl
		<< "Faces : " << faces.size() / 3 << std::endl
		<< "Edges per face : 3" << std::endl
		<< "Edges per vertice (min) : " << min << std::endl
		<< "Edges per vertice (max) : " << max << std::endl
		<< "Edges not shared by two faces : " << countNot2 << std::endl;

	edgesNumb = edges.size();
}

void Mesh::randomDisparition()
{
	for (int i = 0; i < 4000; ++i) {
		faces.erase(faces.begin() + i * 3, faces.begin() + i * 3 + 3);
	}
}

Mesh::~Mesh()
{
}

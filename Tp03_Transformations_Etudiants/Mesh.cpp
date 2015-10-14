#include "Mesh.h"
#include "glut.h" 

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<point3> pts, std::vector<int> fcs, std::vector<point3> nrml) : points(pts), faces(fcs), normales(nrml)
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

Mesh::~Mesh()
{
}

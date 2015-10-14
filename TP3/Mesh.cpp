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
	for(int i = 0; i < taille; i += 3) {
		point3 un = points.at(faces.at(i));
		point3 deux = points.at(faces.at(i+1));
		point3 trois = points.at(faces.at(i+2));
		glBegin(GL_TRIANGLES);
			glVertex3d(un.x*100,un.y*100,un.z*100);
			glVertex3d(deux.x*100,deux.y*100,deux.z*100);
			glVertex3d(trois.x*100, trois.y*100, trois.z*100);
		glEnd();
	}
}

void Mesh::center() {
	
}

Mesh::~Mesh()
{
}

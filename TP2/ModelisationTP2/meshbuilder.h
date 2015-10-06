#ifndef MESHBUILDER_H
#define MESHBUILDER_H
#include "mesh.h"
#include <QVector3D>
#include <QString>
#include <QVector2D>

class MeshBuilder
{
private:

public:
    MeshBuilder();
    Mesh cube(QVector3D& a,QVector3D& b);
    Mesh cylindre(float rayon, float hauteur, int meridiens);
    Mesh sphere(float rayon, int paralleles, int meridiens);
    Mesh cone(float rayon, float hauteur, float hauteurTronc, int echantillons);
    Mesh sphereTranche(float rayon, int paralleles, int meridiens, int retrait);
    Mesh loadMesh(QString& nom);
    void saveMesh(QString& nom, Mesh &mesh);
    ~MeshBuilder();


};
#endif // MESHBUILDER_H

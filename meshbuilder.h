#ifndef MESHBUILDER_H
#define MESHBUILDER_H
#include "mesh.h"
#include <QVector3D>
#include <QString>
#include "fonction3d.h"
#include "terrain.h"
#include <QVector2D>
#include "arbre.h"
#include "foret.h"
class MeshBuilder
{
private:

public:
    MeshBuilder();
    Mesh cube(QVector3D& a,QVector3D& b);
    Mesh cylindre(float rayon, float hauteur, int meridiens);
    Mesh loadMesh(QString& nom);
    void saveMesh(QString& nom, Mesh &mesh);
    ~MeshBuilder();


};
#endif // MESHBUILDER_H

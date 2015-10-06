#ifndef MESH_H
#define MESH_H
#include <QVector3D>
#include <QMatrix3x3>
#include<QList>

class Mesh
{
private:
    QList<QVector3D> geom;
    QList<int> topo;
    QList<QVector3D> norm;
public:
    Mesh();
    Mesh(const Mesh& m);
    Mesh(QList<QVector3D>& v, QList<int>& t, QList<QVector3D>& n);
    void translate(QVector3D& t);
    void rotate(const QMatrix3x3& mat);
    void homotecie(QVector3D &c, float h);
    void merge(const Mesh& mesh);
    int containsGeom(const QVector3D& g);
    int containsNorm(const QVector3D &n);
    QList<QVector3D>& getGeom();
    QList<QVector3D>& getNorm();
    QList<int>& getTopo();
    ~Mesh();
};

#endif // MESH_H

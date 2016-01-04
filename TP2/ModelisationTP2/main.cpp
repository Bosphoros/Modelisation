#include "meshbuilder.h"
#include "mesh.h"

int main(int argc, char *argv[])
{
    MeshBuilder mb;
    Mesh c = mb.cone(1, 10, 10, 6);
    //c.changeUp();
    QMatrix3x3 rot;
    rot(0,0) = 1;
    rot(0, 1) = 0;
    rot(0,2) = 0;

    rot(1,0) = 0;
    rot(1,1) = 0;
    rot(1,2) = 1;

    rot(2,0) = 0;
    rot(2,1) = -1;
    rot(2,2) = 0;
    QVector3D up(0,5.5,0);
    c.translate(up);
    c.rotate(rot);

    QVector3D a(-0.5,0,-0.5);
    QVector3D b(0.5,1,0.5);
    Mesh cube = mb.cube(a,b);
    c.merge(cube);
    //Mesh m = mb.sphere(2, 20, 10);
    //Mesh m = mb.cone(3,10,10,8);
    //Mesh m = mb.cone(3,10,6,8);
    //Mesh m = mb.sphereTranche(2,20,10,3);
    QString n("C:\\Users\\etu\\Desktop\\arbre.obj");
    mb.saveMesh(n,c);

    return 0;
}

#include "meshbuilder.h"
#include "mesh.h"

int main(int argc, char *argv[])
{
    MeshBuilder mb;
    //Mesh m = mb.cylindre(3,10,8);
    //Mesh m = mb.sphere(2, 20, 10);
    //Mesh m = mb.cone(3,10,10,8);
    //Mesh m = mb.cone(3,10,6,8);
    //Mesh m = mb.sphereTranche(2,20,10,3);
    QString n("C:\\Users\\etu\\Desktop\\mesh.obj");
    mb.saveMesh(n,m);

    return 0;
}

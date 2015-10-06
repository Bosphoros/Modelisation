#include "meshbuilder.h"
#include "mesh.h"

int main(int argc, char *argv[])
{
    MeshBuilder mb;
    Mesh m = mb.sphere(1,16,5);
    QString n("C:\\Users\\etu\\Desktop\\sphere.obj");
    mb.saveMesh(n,m);

    return 0;
}

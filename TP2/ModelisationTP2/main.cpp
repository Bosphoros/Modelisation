#include "meshbuilder.h"
#include "mesh.h"

int main(int argc, char *argv[])
{
    MeshBuilder mb;
    Mesh m = mb.sphere(2, 20, 10);
    QString n("C:\\Users\\etu\\Desktop\\cone.obj");
    mb.saveMesh(n,m);

    return 0;
}

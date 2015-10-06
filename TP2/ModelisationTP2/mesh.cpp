#include "mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh &m):geom(m.geom),norm(m.norm),topo(m.topo)
{

}

Mesh::Mesh(QList<QVector3D> &v, QList<int> &t, QList<QVector3D> &n):geom(v),topo(t),norm(n)
{

}

void Mesh::translate(QVector3D &t)
{
    QList<QVector3D>::iterator itv=geom.begin();
        for(;itv!=geom.end();++itv){
            (*itv)+=t;
        }
}

void Mesh::rotate(const QMatrix3x3 &mat)
{
    QList<QVector3D>::iterator itv=geom.begin();
        for(;itv!=geom.end();++itv){
            float x=(*itv).x()*mat(0,0)+(*itv).y()*mat(0,1)+(*itv).z()*mat(0,2);
            float y=(*itv).x()*mat(1,0)+(*itv).y()*mat(1,1)+(*itv).z()*mat(1,2);
            float z=(*itv).x()*mat(2,0)+(*itv).y()*mat(2,1)+(*itv).z()*mat(2,2);
            (*itv).setX(x);
            (*itv).setY(y);
            (*itv).setZ(z);
        }
}

void Mesh::homotecie(QVector3D &c, float h)
{
    QList<QVector3D>::iterator itv=geom.begin();
        for(;itv!=geom.end();++itv){
            (*itv)=(((*itv)-c)*h)+c;
        }
}

void Mesh::merge(const Mesh &mesh)
{
    QList<int> posv;
        QList<int> posn;
        for(int i=0;i<mesh.geom.size();i++){
            int n=containsGeom(mesh.geom[i]);
            if(n==-1){
                n=geom.size();
                geom.append(mesh.geom[i]);
            }
            posv.append(n);
        }

        for(int i=0;i<mesh.norm.size();i++){
            int n=containsNorm(mesh.norm[i]);
            if(n==-1){
                n=norm.size();
                norm.append(mesh.norm[i]);
            }
            posn.append(n);
        }
        for(int i=0;i<mesh.topo.size();i+=3){
            topo.append(posv[mesh.topo[i]]);
            topo.append(0);
            topo.append(posn[mesh.topo[i+2]]);
        }
}

int Mesh::containsGeom(const QVector3D &g)
{
    return geom.indexOf(g);
}

int Mesh::containsNorm(const QVector3D &n)
{
    return norm.indexOf(n);
}

QList<QVector3D>& Mesh::getGeom(){
    return geom;
}

QList<QVector3D>& Mesh::getNorm(){
    return norm;
}

QList<int>& Mesh::getTopo(){
    return topo;
}

Mesh::~Mesh()
{

}

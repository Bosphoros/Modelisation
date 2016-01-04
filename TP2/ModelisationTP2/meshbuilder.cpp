 #include "meshbuilder.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <cmath>
#ifndef fmin
#define fmin(a,b) a<b?a:b
#endif

#define PI 3.14159265358979323846
using namespace std;
MeshBuilder::MeshBuilder()
{
}

Mesh MeshBuilder::cube(QVector3D &a, QVector3D &b)
{
    QList<QVector3D> v;
        QList<QVector3D> vn;
        QList<int> t;

        float ax=a.x();
        float bx=b.x();
        float ay=a.y();
        float by=b.y();
        float az=a.z();
        float bz=b.z();


        v.append(a);
        v.append(QVector3D(bx,ay,az));
        v.append(QVector3D(ax,by,az));
        v.append(QVector3D(bx,by,az));
        v.append(QVector3D(ax,ay,bz));
        v.append(QVector3D(bx,ay,bz));
        v.append(QVector3D(ax,by,bz));
        v.append(b);

        vn.append(QVector3D(1.0,0.0,0.0));
        vn.append(QVector3D(-1.0,0.0,0.0));
        vn.append(QVector3D(0.0,1.0,0.0));
        vn.append(QVector3D(0.0,-1.0,0.0));
        vn.append(QVector3D(0.0,0.0,1.0));
        vn.append(QVector3D(0.0,0.0,-1.0));

        t.append(1);
        t.append(0);
        t.append(0);
        t.append(3);
        t.append(0);
        t.append(0);
        t.append(7);
        t.append(0);
        t.append(0);

        t.append(1);
        t.append(0);
        t.append(0);
        t.append(7);
        t.append(0);
        t.append(0);
        t.append(5);
        t.append(0);
        t.append(0);

        t.append(2);
        t.append(0);
        t.append(1);
        t.append(0);
        t.append(0);
        t.append(1);
        t.append(4);
        t.append(0);
        t.append(1);

        t.append(2);
        t.append(0);
        t.append(1);
        t.append(4);
        t.append(0);
        t.append(1);
        t.append(6);
        t.append(0);
        t.append(1);

        t.append(3);
        t.append(0);
        t.append(2);
        t.append(2);
        t.append(0);
        t.append(2);
        t.append(6);
        t.append(0);
        t.append(2);

        t.append(3);
        t.append(0);
        t.append(2);
        t.append(6);
        t.append(0);
        t.append(2);
        t.append(7);
        t.append(0);
        t.append(2);

        t.append(0);
        t.append(0);
        t.append(3);
        t.append(1);
        t.append(0);
        t.append(3);
        t.append(5);
        t.append(0);
        t.append(3);

        t.append(0);
        t.append(0);
        t.append(3);
        t.append(5);
        t.append(0);
        t.append(3);
        t.append(4);
        t.append(0);
        t.append(3);

        t.append(4);
        t.append(0);
        t.append(4);
        t.append(5);
        t.append(0);
        t.append(4);
        t.append(7);
        t.append(0);
        t.append(4);

        t.append(4);
        t.append(0);
        t.append(4);
        t.append(7);
        t.append(0);
        t.append(4);
        t.append(6);
        t.append(0);
        t.append(4);

        t.append(2);
        t.append(0);
        t.append(5);
        t.append(3);
        t.append(0);
        t.append(5);
        t.append(1);
        t.append(0);
        t.append(5);

        t.append(2);
        t.append(0);
        t.append(5);
        t.append(1);
        t.append(0);
        t.append(5);
        t.append(0);
        t.append(0);
        t.append(5);

        return Mesh(v,t,vn);
}

Mesh MeshBuilder::cylindre(float rayon, float hauteur, int meridiens){
    float demihauteur = hauteur/2;
    QVector3D base(0, 0, -demihauteur);
    QVector3D top(0, 0, demihauteur);
    QList<QVector3D> points;
    QList<int> topo;
    QList<QVector3D> normales;

    for(int i = 0; i < meridiens; ++i) {
        QVector3D pointbase(rayon*cos(i*2*PI/meridiens), rayon*sin(i*2*PI/meridiens), -demihauteur);
        points.append(pointbase);
        QVector3D n = pointbase;
        n.setZ(0);
        n.normalize();
        normales.append(n);

        topo.append(i);
        topo.append(0);
        topo.append(i);

        topo.append((i+1)%meridiens);
        topo.append(0);
        topo.append((i+1)%meridiens);


        topo.append(2*meridiens);
        topo.append(0);
        topo.append(2*meridiens);
    }

    for(int i = meridiens; i < 2*meridiens; ++i) {
        QVector3D pointtop(rayon*cos(i*2*PI/meridiens), rayon*sin(i*2*PI/meridiens), demihauteur);
        points.append(pointtop);
        QVector3D n = pointtop;
        n.setZ(0);
        n.normalize();
        normales.append(n);

        topo.append(i);
        topo.append(0);
        topo.append(i);

        topo.append(meridiens+(i+1)%(meridiens));
        topo.append(0);
        topo.append(meridiens+(i+1)%(meridiens));

        topo.append((2*meridiens)+1);
        topo.append(0);
        topo.append((2*meridiens)+1);
    }

    points.append(base);
    points.append(top);
    QVector3D nbase(0,0,-1);
    QVector3D ntop(0,0,1);
    normales.append(nbase);
    normales.append(ntop);

    for(int i = 0; i < meridiens; ++i) {
        topo.append(i);
        topo.append(0);
        topo.append(i);

        topo.append((i+1)%meridiens);
        topo.append(0);
        topo.append((i+1)%meridiens);

        topo.append(i+meridiens);
        topo.append(0);
        topo.append(i+meridiens);



        topo.append((i+1)%meridiens);
        topo.append(0);
        topo.append((i+1)%meridiens);

        topo.append((i+1)%meridiens+meridiens);
        topo.append(0);
        topo.append((i+1)%meridiens+meridiens);

        topo.append(i+meridiens);
        topo.append(0);
        topo.append(i+meridiens);
    }

    Mesh m(points, topo, normales);
    return m;
}

Mesh MeshBuilder::sphere(float rayon, int paralleles, int meridiens)
{
    QList<QVector3D> points;
    QList<int> topo;
    QList<QVector3D> normales;

    QVector3D bot(0, -rayon, 0);
    QVector3D top(0, rayon, 0);
    for(int j = 0; j < meridiens; ++j) { //i*(PI*2)/paralleles
    // -PI -> PI
    // 2+meridiens
    // j/meridiens*(2*PI)-PI j 1 -> meridiens-1
        for(int i = 0; i < paralleles; ++i) {
            QVector3D p(rayon*(cos(i*(2*PI)/paralleles))*cos((j+1)*PI/(meridiens+1)-PI/2), rayon*sin((j+1)*PI/(meridiens+1)-PI/2),rayon*(sin(i*2*PI/paralleles))*cos((j+1)*PI/(meridiens+1)-PI/2));
            points.append(p);
            QVector3D n = p;
            normales.append(n);

            if(j < meridiens - 1){
                topo.append(j*paralleles+(i+1)%paralleles);
                topo.append(0);
                topo.append(j*paralleles+(i+1)%paralleles);

                topo.append(j*paralleles+i);
                topo.append(0);
                topo.append(j*paralleles+i);

                topo.append((j+1)*paralleles+i);
                topo.append(0);
                topo.append((j+1)*paralleles+i);


                topo.append((j+1)*paralleles+(i+1)%paralleles);
                topo.append(0);
                topo.append((j+1)*paralleles+(i+1)%paralleles);

                topo.append(j*paralleles+(i+1)%paralleles);
                topo.append(0);
                topo.append(j*paralleles+(i+1)%paralleles);

                topo.append((j+1)*paralleles+i);
                topo.append(0);
                topo.append((j+1)*paralleles+i);
            }
        }
    }
    points.append(bot);
    points.append(top);
    QVector3D nbot(0,0,-1);
    QVector3D ntop(0,0,1);
    normales.append(nbot);
    normales.append(ntop);

    for(int i = 0; i < paralleles; ++i) {


        topo.append(paralleles*meridiens);
        topo.append(0);
        topo.append(paralleles*meridiens);

        topo.append(i);
        topo.append(0);
        topo.append(i);

        topo.append((i+1)%paralleles);
        topo.append(0);
        topo.append((i+1)%paralleles);

        topo.append(paralleles*(meridiens-1)+i);
        topo.append(0);
        topo.append(paralleles*(meridiens-1)+i);

        topo.append(paralleles*meridiens+1);
        topo.append(0);
        topo.append(paralleles*meridiens+1);

        topo.append(paralleles*(meridiens-1)+(i+1)%paralleles);
        topo.append(0);
        topo.append(paralleles*(meridiens-1)+(i+1)%paralleles);
    }

    Mesh m(points, topo, normales);
    return m;
}

Mesh MeshBuilder::cone(float rayon, float hauteur, float hauteurTronc, int echantillons)
{
    QVector3D base(0,-hauteurTronc/2, 0);
    bool coupe = hauteur > hauteurTronc;

    QList<QVector3D> points;
    QList<int> topo;
    QList<QVector3D> normales;

    points.append(base);
    QVector3D nbase(0, -1, 0);
    normales.append(nbase);

    for(int i = 0; i < echantillons; ++i) {
        QVector3D p(rayon*cos(i*2*PI/echantillons), base.y(), rayon*sin(i*2*PI/echantillons));
        points.append(p);
        QVector3D n = p;
        normales.append(n);

        topo.append(i+1);
        topo.append(0);
        topo.append(i+1);

        topo.append(1+((i+1)%(echantillons)));
        topo.append(0);
        topo.append(1+((i+1)%(echantillons)));

        topo.append(0);
        topo.append(0);
        topo.append(0);
    }

    if(!coupe){
        QVector3D top(0,hauteur/2, 0);
        points.append(top);
        QVector3D ntop(0, 1, 0);
        normales.append(ntop);

        for(int i = 0; i < echantillons; ++i) {
            topo.append(i+1);
            topo.append(0);
            topo.append(i+1);

            topo.append(echantillons+1);
            topo.append(0);
            topo.append(echantillons+1);

            topo.append(1+(i+1)%(echantillons));
            topo.append(0);
            topo.append(1+(i+1)%(echantillons));

        }
    }
    else {
        QVector3D top(0,hauteurTronc/2, 0);
        QVector3D ntop(0, 1, 0);

        float petitRayon = rayon*(hauteur-hauteurTronc)/hauteur;

        for(int i = 0; i < echantillons; ++i) {
            QVector3D p(petitRayon*cos(i*2*PI/echantillons), top.y(), petitRayon*sin(i*2*PI/echantillons));
            points.append(p);
            QVector3D n = p;
            normales.append(n);

            topo.append(i+echantillons+1);
            topo.append(0);
            topo.append(i+echantillons+1);

            topo.append(2*echantillons+1);
            topo.append(0);
            topo.append(2*echantillons+1);

            topo.append(1+(i+1)%(echantillons)+echantillons);
            topo.append(0);
            topo.append(1+(i+1)%(echantillons)+echantillons);



            topo.append(i+1);
            topo.append(0);
            topo.append(i+1);

            topo.append(i+1+echantillons);
            topo.append(0);
            topo.append(i+1+echantillons);

            topo.append(1+((i+1)%(echantillons)));
            topo.append(0);
            topo.append(1+((i+1)%(echantillons)));



            topo.append(1+((i+1)%(echantillons)));
            topo.append(0);
            topo.append(1+((i+1)%(echantillons)));

            topo.append(i+1+echantillons);
            topo.append(0);
            topo.append(i+1+echantillons);

            topo.append(1+(i+1)%(echantillons)+echantillons);
            topo.append(0);
            topo.append(1+(i+1)%(echantillons)+echantillons);


        }
        points.append(top);
        normales.append(ntop);
    }

    Mesh m(points, topo, normales);
    return m;
}

Mesh MeshBuilder::sphereTranche(float rayon, int paralleles, int meridiens, int retrait)
{
    QList<QVector3D> points;
    QList<int> topo;
    QList<QVector3D> normales;

    QVector3D bot(0, -rayon, 0);
    QVector3D top(0, rayon, 0);
    int nbrayon = paralleles - retrait;
    for(int j = 0; j < meridiens; ++j) { //i*(PI*2)/paralleles
    // -PI -> PI
    // 2+meridiens
    // j/meridiens*(2*PI)-PI j 1 -> meridiens-1
        for(int i = 0; i < nbrayon; ++i) {
            QVector3D p(rayon*(cos(i*(2*PI)/paralleles))*cos((j+1)*PI/(meridiens+1)-PI/2), rayon*sin((j+1)*PI/(meridiens+1)-PI/2),rayon*(sin(i*2*PI/paralleles))*cos((j+1)*PI/(meridiens+1)-PI/2));
            points.append(p);
            QVector3D n = p;
            normales.append(n);

            if(j < meridiens - 1){
                if(i < nbrayon - 1) {
                    topo.append(j*nbrayon+(i+1)%nbrayon);
                    topo.append(0);
                    topo.append(j*nbrayon+(i+1)%nbrayon);

                    topo.append(j*nbrayon+i);
                    topo.append(0);
                    topo.append(j*nbrayon+i);

                    topo.append((j+1)*nbrayon+i);
                    topo.append(0);
                    topo.append((j+1)*nbrayon+i);


                    topo.append((j+1)*nbrayon+(i+1)%nbrayon);
                    topo.append(0);
                    topo.append((j+1)*nbrayon+(i+1)%nbrayon);

                    topo.append(j*nbrayon+(i+1)%nbrayon);
                    topo.append(0);
                    topo.append(j*nbrayon+(i+1)%nbrayon);

                    topo.append((j+1)*nbrayon+i);
                    topo.append(0);
                    topo.append((j+1)*nbrayon+i);
                }
                else
                {
                    topo.append(j*nbrayon+(i+1)%nbrayon);
                    topo.append(0);
                    topo.append(j*nbrayon+(i+1)%nbrayon);

                    topo.append(nbrayon*meridiens+2);
                    topo.append(0);
                    topo.append(nbrayon*meridiens+2);

                    topo.append((j+1)*nbrayon+(i+1)%nbrayon);
                    topo.append(0);
                    topo.append((j+1)*nbrayon+(i+1)%nbrayon);


                    topo.append(nbrayon*meridiens+2);
                    topo.append(0);
                    topo.append(nbrayon*meridiens+2);

                    topo.append(j*nbrayon+i);
                    topo.append(0);
                    topo.append(j*nbrayon+i);

                    topo.append((j+1)*nbrayon+i);
                    topo.append(0);
                    topo.append((j+1)*nbrayon+i);
                }
            }
        }
    }
    points.append(bot);
    points.append(top);
    QVector3D nbot(0,0,-1);
    QVector3D ntop(0,0,1);
    normales.append(nbot);
    normales.append(ntop);

    for(int i = 0; i < nbrayon - 1; ++i) {

        topo.append(nbrayon*meridiens);
        topo.append(0);
        topo.append(nbrayon*meridiens);

        topo.append(i);
        topo.append(0);
        topo.append(i);

        topo.append((i+1)%nbrayon);
        topo.append(0);
        topo.append((i+1)%nbrayon);

        topo.append(nbrayon*(meridiens-1)+i);
        topo.append(0);
        topo.append(nbrayon*(meridiens-1)+i);

        topo.append(nbrayon*meridiens+1);
        topo.append(0);
        topo.append(nbrayon*meridiens+1);

        topo.append(nbrayon*(meridiens-1)+(i+1)%nbrayon);
        topo.append(0);
        topo.append(nbrayon*(meridiens-1)+(i+1)%nbrayon);
    }

    // Centre base

    topo.append(nbrayon*meridiens+2);
    topo.append(0);
    topo.append(nbrayon*meridiens+2);

    topo.append(0);
    topo.append(0);
    topo.append(0);

    topo.append(nbrayon*meridiens);
    topo.append(0);
    topo.append(nbrayon*meridiens);

    topo.append(nbrayon*meridiens+2);
    topo.append(0);
    topo.append(nbrayon*meridiens+2);

    topo.append(nbrayon*meridiens);
    topo.append(0);
    topo.append(nbrayon*meridiens);

    topo.append(nbrayon-1);
    topo.append(0);
    topo.append(nbrayon-1);

    // Centre top

    topo.append(nbrayon*meridiens+2);
    topo.append(0);
    topo.append(nbrayon*meridiens+2);

    topo.append(nbrayon*meridiens-1);
    topo.append(0);
    topo.append(nbrayon*meridiens-1);

    topo.append(nbrayon*meridiens+1);
    topo.append(0);
    topo.append(nbrayon*meridiens+1);



    topo.append(nbrayon*meridiens+2);
    topo.append(0);
    topo.append(nbrayon*meridiens+2);

    topo.append(nbrayon*meridiens+1);
    topo.append(0);
    topo.append(nbrayon*meridiens+1);

    topo.append(nbrayon*(meridiens-1));
    topo.append(0);
    topo.append(nbrayon*(meridiens-1));

    QVector3D centre(0,0,0);
    points.append(centre);
    normales.append(ntop);

    Mesh m(points, topo, normales);
    return m;
}


void MeshBuilder::saveMesh(QString &nom, Mesh& mesh)
{
    QFile file(nom);
    cout<<"fichier créé"<<endl;
    file.open((QIODevice::WriteOnly | QIODevice::Text));
    cout<<"fichier ouvert"<<endl;
    QTextStream out(&file);
    cout<<"flux créé"<<endl;

    for(QList<QVector3D>::iterator itVect = mesh.getGeom().begin(); itVect != mesh.getGeom().end(); ++itVect) {
    out << "v " << itVect->x() << " " << itVect->y() << " " << itVect->z() << "\n";
    }
    out << "\n";

    cout<<"geom ok"<<endl;

    for(QList<QVector3D>::iterator itNorm = mesh.getNorm().begin(); itNorm != mesh.getNorm().end(); ++itNorm) {
    out << "vn " << itNorm->x() << " " << itNorm->y() << " " << itNorm->z() << "\n";
    }
    out << "\n";

    out << "vt 0.0 0.0 \n\n";

    for(QList<int>::iterator it = mesh.getTopo().begin(); it != mesh.getTopo().end();) {
    out << "f ";
    for(int i = 0; i < 3; i++) {
    int face = (*(it++)) + 1;
    int texture = (*(it++)) + 1;
    int normale = (*(it++)) + 1;
    out << face << "/" << texture << "/" << normale << " ";
    }
    out << "\n";
    }

    file.close();
    cout<<"fichier fermé"<<endl;
}

MeshBuilder::~MeshBuilder()
{

}

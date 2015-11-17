/*
 *	Tableau des points permettant de gérer les points de controles
 * On sélectionne le point en se déplaçant avec + et -, ...
 * On sélectionne ensuite si on veut faire monter, descendre amener vers la gauche ou la droite le point.
 *   d : translation à droite
 *   q : à gauche
 *   z : en haut
 *   s : en bas
 *   
 */



#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "structu.h"
#include <vector>

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ESC 27

float tx=0.0;
float ty=0.0;

// Tableau des points de contrôles en global ...
point3 TabPC[4];
point3 precedentTabPC[4];
point3 CasteljauTabPC[20];
point3 TabPC2[4];
point3 precedentTabPC2[4];
point3 CasteljauTabPC2[20];
// Ordre de la courbre  : Ordre
// Degré de la courbe = Ordre - 1
int Ordre = 4;

int factsBernstein[4];
bool dual = false;


// Point de controle selectionné
int numPoint = 0;

// Fonction Factorielle
float fact(int n)
{
 if(n > 1) {
	 return fact(n-1)*n;
 }
 return 1;
}

point3 cubiqueHermite(point3 P0, point3 P1, point3 V0, point3 V1, float u) {
	float f1 = 2*u*u*u-3*u*u+1;
	float f2 = -2*u*u*u+3*u*u;
	float f3 = u*u*u-2*u*u+u;
	float f4 = u*u*u-u*u;
	float x = f1*P0.x + f2*P1.x + f3*V0.x + f4*V1.x;
	float y = f1*P0.y + f2*P1.y + f3*V0.y + f4*V1.y;
	float z = f1*P0.z + f2*P1.z + f3*V0.z + f4*V1.z;
	return point3(x,y,z);
}

void Hermite(point3 P0, point3 P1, point3 V0, point3 V1, int echantillons){
	glColor3f (0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for(float i = 0.0; i <= echantillons ; ++i){
		point3 p = cubiqueHermite(P0, P1, V0, V1, i/echantillons);
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd(); 	
	glColor3f(0.0,0.0,0.0);
}

void processFactsBernstein() {
	for(int i = 0; i < Ordre; ++i) {
		factsBernstein[i] = fact(Ordre-1)/(fact(i)*fact(Ordre-1-i));
		std::cout << factsBernstein[i] << std::endl;
	}
}

float Bernstein(int i, int n, float t)
{
	 return factsBernstein[i]*powf(t,i)*powf((1-t),n-i);
}

point3 Bezier(float t, point3* pts) {
	point3 p(0,0,0);
	for(int i = 0; i < Ordre; ++i) {
		p = p + pts[i]*Bernstein(i, Ordre-1, t);
	}
	return p;
}

void traceBezier(int echantillons, point3* pts) {
	glColor3f (0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= echantillons; ++i) {
		point3 tmp = Bezier((float)i/echantillons, pts);
		glVertex3f(tmp.x, tmp.y, tmp.z);
	}
	glEnd();
	
}

point3 Casteljau(float t, std::vector<point3> p) {
	if (p.size() == 1) {
		return p[0];
	}
	else {
		std::vector<point3> pts;
		point3 lien = p[0];
		for (int i = 1; i < p.size(); ++i) {
			point3 tmp = (p[i] - lien)*t + lien;
			pts.push_back(tmp);
			lien = p[i];
		}
		return Casteljau(t, pts);
	}
	
}

void traceCasteljau(int echantillons, point3* p, point3* pcPrecedents, point3* precedents) {
	
	std::vector<point3> pts;
	bool identique = true;
	for (int i = 0; i < Ordre; ++i) {
		if(p[i] != pcPrecedents[i]) {
			identique = false;
		}
		pts.push_back(p[i]);
	}

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= echantillons; ++i) {
		if(!identique) {
			point3 tmp = Casteljau((float)i / echantillons, pts);
			precedents[i] = tmp;
		}
		glVertex3f(precedents[i].x, precedents[i].y, precedents[i].z);
	}
	glEnd();
}

void jointure(point3* c1, point3* c2) {
	int pos = numPoint == Ordre -2 ? -1 : numPoint == Ordre -1 ? 0 : numPoint == Ordre ? 10 : numPoint == Ordre + 1 ? 1 : 2;
	
	if (pos == -1) {
		c2[1] = (c1[3] - c1[2]) + c1[3];
		c2[0] = c1[3];
	}
	else if (pos == 0) {
		point3 tmp = (c1[3] - c1[2]);
		c1[2] = c1[3] - tmp;
		c2[1] = tmp + c1[3];
		c2[0] = c1[3];
	}
	else if (pos == 10) {
		point3 tmp = (c2[0] - c1[2]);
		c1[2] = c2[0] - tmp;
		c2[1] = tmp + c2[0];
		c1[3] = c2[0];
	}
	else if(pos == 1) {
		c1[2] = (c2[0] - c2[1]) + c2[0];
		c2[0] = c1[3];
	}
	else {
		c2[0] = c1[3];
	}
}


/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	// Initialisation des points de contrôles
	// On choisit de les intialiser selon une ligne
	/*for (int i = 0; i < Ordre; i++)
	{
     TabPC[i] = point3(i,i,i);
    }//*/
 
	TabPC[0] = point3(-2,-2,0);
	TabPC[1] = point3(-1,1,0);
	TabPC[2] = point3(1,1,0);
	TabPC[3] = point3(2,-2,0);

	TabPC2[0] = point3(2,-2,0);
	TabPC2[1] = point3(2.5,-3,0);
	TabPC2[2] = point3(3.5, -3, 0);
	TabPC2[3] = point3(5, -2, 0);

	processFactsBernstein();

}

void update(bool cadres, bool twoCurves) {

	dual = twoCurves;
	if(twoCurves) {
		if(numPoint>=Ordre){
			int indice = numPoint%Ordre;
			TabPC2[indice]=TabPC2[indice]+point3(tx,ty,0);
		}
		else{
			TabPC[numPoint]=TabPC[numPoint]+point3(tx,ty,0);
		}
	}
	else {
		TabPC[numPoint]=TabPC[numPoint]+point3(tx,ty,0);
	}
	
	jointure(TabPC, TabPC2);

	// Enveloppe des points de controles
	if(cadres) {
		glColor3f (1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
			for (int i =0; i < Ordre; i++)
			{
			 glVertex3f(TabPC[i].x, TabPC[i].y, TabPC[i].z);
			}
			glEnd();
		if(dual) {
			glColor3f(1.0, 1.0, 0.0);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < Ordre; ++i) {
				glVertex3f(TabPC2[i].x, TabPC2[i].y, TabPC2[i].z);
			}
			glEnd();
		}}//*/


	// Affichage du point de controle courant
	// On se déplace ensuite avec + et - 
    // � d'un point de contrôle au suivant (+)
    // � d'un point de contrôle au précédent (-)
	if(cadres) {
		glColor3f (0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		if(dual){
			if(numPoint>=Ordre){
				glVertex3f(TabPC2[numPoint%Ordre].x+0.1, TabPC2[numPoint%Ordre].y+0.1, TabPC2[numPoint%Ordre].z);
				glVertex3f(TabPC2[numPoint%Ordre].x+0.1, TabPC2[numPoint%Ordre].y-0.1, TabPC2[numPoint%Ordre].z);
				glVertex3f(TabPC2[numPoint%Ordre].x-0.1, TabPC2[numPoint%Ordre].y-0.1, TabPC2[numPoint%Ordre].z);
				glVertex3f(TabPC2[numPoint%Ordre].x-0.1, TabPC2[numPoint%Ordre].y+0.1, TabPC2[numPoint%Ordre].z);
			}
			else {
				glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
			}
		}
		else {
				glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
		}
		glEnd();
	}
}

/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
   
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(tx,ty,0.0);
  	

	point3 Ptemp;
	
	update(false, false);

	// Dessiner ici la courbe de Bézier.
	/*point3 p0(0,0,0);
	point3 p1(2,0,0);
	point3 v0(2,2,0);
	point3 v1(2,2,0);
	Hermite(p0,p1,v0,v1,20);//*/

	traceBezier(10, TabPC);//*/

	/*traceCasteljau(20, TabPC,precedentTabPC, CasteljauTabPC);
	traceCasteljau(20, TabPC2, precedentTabPC2, CasteljauTabPC2);//*/

	// Vous devez avoir implémenté Bernstein précédemment.
	
	glEnd(); 
	glFlush();
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2, 5, -5, 5, -10, 10);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		if(dual) {
		   if (numPoint < Ordre*2-1)
		   numPoint = numPoint + 1;
        else
            numPoint = 0;
	   }
		else if (numPoint < Ordre-1)
		   numPoint = numPoint + 1;
        else
            numPoint = 0;
		tx=0;
		ty=0;
		break;
	case '-':
		if(dual) {
		   if (numPoint > 0)
		   numPoint = numPoint - 1;
        else
            numPoint = 0;
	   }
		else if (numPoint > 0) 
		   numPoint = numPoint - 1;
        else
            numPoint = Ordre-1;
		tx=0;
		ty=0;
		break;

	case 'd':
         tx=0.1;
		 ty=0;
      break;
	case 'q':
         tx=-0.1;
		 ty=0;
      break;
	case 'z':
         ty=0.1;
		 tx=0;
      break;
	case 's':
         ty=-0.1;
		 tx=0;
      break;
	case ESC:
      exit(0);
      break;
	case '0' :
	   numPoint = 0;
		tx=0;
		ty=0;
	   break;
	case '1':
	   numPoint = 1;
	   tx=0;
		ty=0;
	   break;
	case '2':
	   numPoint = 2;
	   tx=0;
		ty=0;
	   break;
	case '3':
	   numPoint = 3;
	   tx=0;
		ty=0;
	   break;
	case '4':
		if(dual) {
	   numPoint = 4;
	   tx=0;
		ty=0;
		}
	   break;
	case '5':
		if(dual) {
	   numPoint = 5;
	   tx=0;
		ty=0;
		}
	   break;
	case '6':
		{
	   numPoint = 6;
	   tx=0;
		ty=0;
		}
	   break;
	case '7':
		if(dual) {
	   numPoint = 7;
	   tx=0;
		ty=0;
		}
	   break;
   default :
	   tx=0;
	   ty=0;
   }
   glutPostRedisplay();
}



int main(int argc, char **argv)
{
   glutInitWindowSize(800, 800);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow("Courbe de Bézier");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}

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
static int a = 0;
bool rotation = false;

// Tableau des points de contrôles en global ...
point3 TabPC[5];

// Ordre de la courbre  : Ordre
// Degré de la courbe = Ordre - 1
int Ordre = 5;

// Point de controle selectionné
int numPoint = 0;

// Fonction Factorielle

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
 
	TabPC[0] = point3(-3,-2,0);
	TabPC[1] = point3(-2,1,0);
	TabPC[2] = point3(0,1.5,0);
	TabPC[3] = point3(1,0,0);
	TabPC[4] = point3(-1, -1, 0);

}

std::vector<point3> subdivide(std::vector<point3>& pts) {
	std::vector<point3> points;
	for (int i = 0; i < pts.size(); ++i) {
		point3 dir = pts.at((i + 1)%pts.size()) - pts.at(i);
		point3 pt1 = pts.at(i) + dir * 0.25f;
		point3 pt2 = pts.at(i) + dir * 0.75f;
		points.push_back(pt1);
		points.push_back(pt2);
	}

	return points;
}


std::vector<point3> getSubdivision(int profondeur, point3* points, int size) {
	std::vector<point3> pts;
	for (int i = 0; i < size; ++i) {
		pts.push_back(points[i]);
	}
	std::vector<point3> ptReturn;
	for (int i = 0; i < profondeur; ++i) {
		ptReturn = subdivide(pts);
		pts = ptReturn;
	}

	return ptReturn;
}

void drawSubdivide(int profondeur, point3* points, int size) {

	std::vector<point3> pts = getSubdivision(profondeur, points, size);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < pts.size(); ++i) {
		glVertex3f(pts.at(i).x, pts.at(i).y, pts.at(i).z);
	}
	glEnd();
}

void update() {

	// Enveloppe des points de controles
	
		glColor3f (1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (int i =0; i < Ordre; i++)
		{
			 glVertex3f(TabPC[i].x, TabPC[i].y, TabPC[i].z);
		}
		glEnd();
		
		//*/


	// Affichage du point de controle courant
	// On se déplace ensuite avec + et - 
    // � d'un point de contrôle au suivant (+)
    // � d'un point de contrôle au précédent (-)

		glColor3f (0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		
				glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
				glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);

		glEnd();
}

/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
   
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(tx,ty,0.0);
	
	point3 Ptemp;
	
	update();

	drawSubdivide(3, TabPC, 4);

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
   glOrtho(-4, 4, -5, 5, -10, 10);
   glMatrixMode(GL_MODELVIEW);
   //glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ': rotation = !rotation;
		break;
	case '+':
		if (numPoint < Ordre-1)
		   numPoint = numPoint + 1;
        else
            numPoint = 0;
		tx=0;
		ty=0;
		break;
	case '-':
		if (numPoint > 0) 
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
   default :
	   tx=0;
	   ty=0;
   }
   glutPostRedisplay();
}

GLvoid window_idle()
{
	if(rotation) a = (a + 1) % (360 * 64);
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
   glutIdleFunc(window_idle);
   glutMainLoop();
   return 0;
}

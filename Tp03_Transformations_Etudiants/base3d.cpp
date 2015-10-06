#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include "glut.h" 

#define WIDTH  480
#define HEIGHT 480

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define PI 3.14159

#define KEY_ESC 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_idle(); 
static int a = 0;


int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // définition et création de la fenêtre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Primitives graphiques");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);
  glutIdleFunc(&window_idle);
  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
    	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
    	glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
  glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-25.0, 25.0, -15.0, 30.0, -25.0, 25.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
	
  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }     
}

GLvoid window_idle() 
{  
	a = (a + 1)%(360*4);
  glutPostRedisplay();
}


void render_scene()
{
//c'est ici qu'on dessine
	//glLoadIdentity();
	glBegin(GL_LINES);
		glColor3d(1,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,20,0);
	glEnd();
	
	//glRotated(1,0,1,0);

	glPushMatrix();
		for(int i = 0; i < 4; ++i) 
		{
			glRotated(a*0.25*(1+i),0,1,0);
			glPushMatrix();
				glTranslated(10,0,0);
				glPushMatrix();

					glRotated(2*a*(1+i),0,1,0);
					glColor3d(0,0,0.5);
					glutWireTeapot(5.0-i);
					glColor3d(1,1,1);

					// La sphere tourne autour de la théière
					
					glRotated(-a*(1+i),0,1,0);
					glTranslated(10.0-i,0,0);
					glColor3d(0,1,0);
					glutSolidSphere(1,10,5);
					glColor3d(1,1,1);

				glPopMatrix();
			glPopMatrix();
			glTranslated(0,7-i,0);
		}
	glPopMatrix();

 }
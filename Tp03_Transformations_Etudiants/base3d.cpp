#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include "glut.h" 
#include "OffReader.h"
#include "Mesh.h"

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
void render_scene_mesh();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_idle(); 
static int a = 0;
static Mesh m;

// Paramètres de la source de lumière 0 (directionnelle)
GLfloat Light0Position[]= { 4.0f, 4.0f, 2.0f, 0.0f };
GLfloat Light0Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat Light0Diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat Light0Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };
 
// Paramètres de la source de lumière 1 (ponctuelle)
GLfloat Light1Position[]= { 4.0f, 8.0f, 2.0f, 1.0f };
GLfloat Light1Ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat Light1Diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat Light1Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };


int main(int argc, char **argv) 
{  
	OffReader or;
	m = or.import("C:\\Users\\Florian\\Dropbox\\bunny.off");
	m.normalize();
	m.center();
	m.norms();
	m.stats();


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
  //m.randomDisparition();
  //or.export(m, "D:/bunny.off");
  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
	glClearColor(0.6f, 0.6f, 0.7f, 1.0f);               // Couleur servant à effacer la fenêtre (celle du brouillard)
    glShadeModel(GL_SMOOTH);                            // Modèle d'ombrage : lissage de Gouraud
    //glEnable(GL_CULL_FACE);                             // Ne traitre pas les faces cachées
    glEnable(GL_DEPTH_TEST);                            // Active le Z-Buffer
    glDepthFunc(GL_LEQUAL);                             // Fonctionnement du Z-Buffer
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Active la correction de perspective (pour ombrage, texture, ...)
 
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);    // Couleur ambiante de la source de lumière 0 (directionnelle)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);    // Couleur diffuse de la source de lumière 0
    glLightfv(GL_LIGHT0, GL_SPECULAR,Light0Specular);   // Couleur spéculaire de la source de lumière 0
    glLightfv(GL_LIGHT0, GL_POSITION,Light0Position);   // Direction de la source de lumière 0
    glEnable(GL_LIGHT0);                                // Activation de la source de lumière 0
 
    glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Ambient);    // Couleur ambiante de la source de lumière 1
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Diffuse);    // Couleur diffuse de la source de lumière 1
    glLightfv(GL_LIGHT1, GL_SPECULAR,Light1Specular);   // Couleur spéculaire de la source de lumière 1
    glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);   // Position de la source de lumière 1
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02);   // Atténuation de la source de lumière 1
    //glEnable(GL_LIGHT1);                              // Activation de la source de lumière 1
 
    glEnable(GL_LIGHTING); 
    	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
    	glEnable(GL_DEPTH_TEST);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_scene_mesh();

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
  //glOrtho(-25.0, 25.0, -15.0, 30.0, -25.0, 25.0); //taille Camera théières
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //taille Camera Mesh normalisé

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
		glVertex3d(0,1,0);
		glColor3d(1,1,1);
	glEnd();//*/


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
	glPopMatrix();//*/

 }

void render_scene_mesh()
{
	m.draw();
	glRotated(1, 0, 1, 0);
}
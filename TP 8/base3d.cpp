#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include <GL/glut.h>
#include "Grid.h"
#include "Sphere.h"
#include "Difference.h"

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

int dimension = 0; // 0 x, 1 y, 2 z
int posGridX = 0;
int posGridY = 0;
int posGridZ = 0;

Grid grid;

// Param�tres de la source de lumi�re 0 (directionnelle)
GLfloat Light0Position[]= { 4.0f, 4.0f, 2.0f, 0.0f };
GLfloat Light0Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat Light0Diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat Light0Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };
 
// Param�tres de la source de lumi�re 1 (ponctuelle)
GLfloat Light1Position[]= { 4.0f, 8.0f, 2.0f, 1.0f };
GLfloat Light1Ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat Light1Diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat Light1Specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };


int main(int argc, char **argv) 
{  
	
  // initialisation  des param�tres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // d�finition et cr�ation de la fen�tre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Primitives graphiques");

  // initialisation de OpenGL et de la sc�ne
  initGL();  
  init_scene();
  
  
  // choix des proc�dures de callback pour 
  // le trac� graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&window_key);
  glutIdleFunc(&window_idle);

  

  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();  
  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque

GLvoid initGL() 
{
	glClearColor(0.6f, 0.6f, 0.7f, 1.0f);               // Couleur servant � effacer la fen�tre (celle du brouillard)
    glShadeModel(GL_SMOOTH);                            // Mod�le d'ombrage : lissage de Gouraud
    //glEnable(GL_CULL_FACE);                             // Ne traitre pas les faces cach�es
    glEnable(GL_DEPTH_TEST);                            // Active le Z-Buffer
    glDepthFunc(GL_LEQUAL);                             // Fonctionnement du Z-Buffer
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Active la correction de perspective (pour ombrage, texture, ...)
 
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);    // Couleur ambiante de la source de lumi�re 0 (directionnelle)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);    // Couleur diffuse de la source de lumi�re 0
    glLightfv(GL_LIGHT0, GL_SPECULAR,Light0Specular);   // Couleur sp�culaire de la source de lumi�re 0
    glLightfv(GL_LIGHT0, GL_POSITION,Light0Position);   // Direction de la source de lumi�re 0
    glEnable(GL_LIGHT0);                                // Activation de la source de lumi�re 0
 
    glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Ambient);    // Couleur ambiante de la source de lumi�re 1
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Diffuse);    // Couleur diffuse de la source de lumi�re 1
    glLightfv(GL_LIGHT1, GL_SPECULAR,Light1Specular);   // Couleur sp�culaire de la source de lumi�re 1
    glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);   // Position de la source de lumi�re 1
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02);   // Att�nuation de la source de lumi�re 1
    //glEnable(GL_LIGHT1);                              // Activation de la source de lumi�re 1
 
    glEnable(GL_LIGHTING); 
    	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
    	glEnable(GL_DEPTH_TEST);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void init_scene()
{
	std::vector<Operators*> ops;
	Sphere sph(point3(0, 0, 0), 2.5f);
	Sphere sph2(point3(1, 1, 1), 1.5f);
	Difference diff(&sph, &sph2);
	ops.push_back(&diff);
	//ops.push_back(&sph2);
	grid = Grid(ops, 0.25f);
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_scene();

  // trace la sc�ne grapnique qui vient juste d'�tre d�finie
  glFlush();
  glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0); //taille Camera th�i�res
  //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //taille Camera Mesh normalis�

  // toutes les transformations suivantes s�appliquent au mod�le de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
  case 'd':
	  std::cout << posGridX << "/" << posGridY << "/" << posGridZ << std::endl;
	  if (dimension == 0) {
		  posGridX = std::fmin(posGridX + 1, grid.nbX);
	  }
	  if (dimension == 1) {
		  posGridY = std::fmin(posGridY + 1, grid.nbY);
	  }
	  if (dimension == 2) {
		  posGridZ = std::fmin(posGridZ + 1, grid.nbZ);
	  }
	  break;
  case 'q':
	  if (dimension == 0) {
		  posGridX = std::fmax(posGridX - 1, 0);
	  }
	  if (dimension == 1) {
		  posGridY = std::fmax(posGridY - 1, 0);
	  }
	  if (dimension == 2) {
		  posGridZ = std::fmax(posGridZ - 1, 0);
	  }
	  break;
  case 'x': dimension = 0;
	  break;
  case 'y': dimension = 1;
	  break;
  case 'z': dimension = 2;
	  break;
  case '+': grid.addMatter(posGridX, posGridY, posGridZ);
	  break;
  case '-': grid.removeMatter(posGridX, posGridY, posGridZ);
	  break;
  default:
    printf ("La touche %d n�est pas active.\n", key);
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


	glRotated(1, 0, 1, 0);
//c'est ici qu'on dessine
	//glLoadIdentity();
	glBegin(GL_LINES);
		glColor3d(1,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,20,0);
		glColor3d(1,1,1);
	glEnd();//*/

	grid.draw();

 }
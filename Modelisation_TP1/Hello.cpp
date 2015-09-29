/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * hello.c
 * This is a simple, introductory OpenGL program.
 */
#include <iostream>
#include <cmath>
#include "glut.h"

#define C_PI 3.14159265359


void cercle(float x, float y, float r, int e) {
	glBegin(GL_LINE_LOOP);
	glColor3f (0.0, 0.0, 0.0);
		for(int i = 0; i < e; ++i) {
			glVertex3f(x + r*cos(i*2*C_PI/e), y + r*sin(i*2*C_PI/e), 0);
		}
	glEnd();

}

void cerclesCommun(float r, float e, float nbCercles, float reduction) {
	float x = 0.5, y = 0.5;
	float nr = r;
	for(int i = 0; i < nbCercles; ++i) {
		cercle(x,y,nr,e);
		x-=(nr-nr*reduction);
		nr*=reduction;
		
	}
}

void cerclesAlignes(float x, float y, float r, int e, int nbCercles, float reduction) {
	float nx = x, ny = y;
	float nr = r;
	for(int i = 0; i < nbCercles; ++i) {
		cercle(x,y,nr,e);
		x+=(nr+nr*reduction);
		nr*=reduction;
	}
}

void floconKoch(float ax, float ay, float az, float bx, float by, float bz, int iterations) {
	if(iterations <= 0)
	{
		glBegin(GL_LINE_STRIP);
		glColor3f (0.0, 0.0, 0.0);
			glVertex3f(ax, ay, az);
			glVertex3f(bx, by, bz);
		glEnd();

	}
	else
	{
		float mx, my, mz, nx, ny, nz;
		mx = ax + (bx - ax)/3;
		my = ay + (by - ay)/3;
		mz = 0;

		nx = ax + (bx - ax)/3*2;
		ny = ay + (by - ay)/3*2;
		nz = 0;

		float ix, iy, iz, inx, iny, inz, ox, oy, oz;
		ix = ax + (bx - ax)/2;
		iy = ay + (by - ay)/2;
		iz = 0;

		inx = (nx-ix);
		iny = (ny-iy);
		inz = 0;

		ox = ix + iny*sin(-C_PI/3);
		oy = iy - inx*sin(-C_PI/3);
		oz = 0;

		floconKoch(ax,ay,az,mx,my,mz,iterations-1);
		floconKoch(mx,my,mz,ox,oy,oz,iterations-1);
		floconKoch(ox,oy,oz,nx,ny,nz,iterations-1);
		floconKoch(nx,ny,nz,bx,by,bz,iterations-1);
	}
	

}

void display(void)
{
/* clear all pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

/* draw white polygon (rectangle) with corners at
 * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0) 
 */
  
   /*glBegin(GL_LINE_LOOP);
   glColor3f (1.0, 1.0, 1.0);
      glVertex3f (0.05, 0.75, 0.0);
      glVertex3f (0.05, 0.45, 0.0);
      glVertex3f (0.35, 0.45, 0.0);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f (0.0, 0.0, 1.0);
      glVertex3f (0.4, 0.65, 0.0);
      glVertex3f (0.4, 0.45, 0.0);
      glVertex3f (0.6, 0.45, 0.0);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor3f (0.0, 1.0, 0.0);
      glVertex3f (0.65, 0.55, 0.0);
      glVertex3f (0.65, 0.45, 0.0);
      glVertex3f (0.75, 0.45, 0.0);
   glEnd();*/

   //cercle(0.5,0.5,0.3,30);

   //cerclesCommun(0.48,40,6,0.8);
   //cerclesAlignes(0.2,0.5,0.15,40,6,0.7);

   floconKoch(0.1,0.2,0 , 0.5, 0.8,0,1);
   floconKoch(0.5,0.8,0, 0.9,0.2,0, 2);
   floconKoch(0.9,0.2,0, 0.1,0.2,0, 4);

/* Swap the buffers to show the one
 * on which we writed
 */
   glutSwapBuffers();
}



void init (void)
{
/* select clearing color     */
   glClearColor (1.0, 1.0, 1.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/*
 * Declare initial window size, position, and display mode
 * (double buffer and RGB).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (250, 250);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   init ();
   glutDisplayFunc(display);
   //glutDisplayFunc(cercle(0.5,0.5,0.3,30));
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}

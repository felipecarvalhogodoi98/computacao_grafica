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
 *  alpha.c
 *  This program draws several overlapping filled polygons
 *  to demonstrate the effect order has on alpha blending results.
 *  Use the 't' key to toggle the order of drawing polygons.
 */
#include <GL/glut.h>
#include <stdlib.h>

static int leftFirst = GL_TRUE;

float cubeT = 1.0, coneT = 1.0, sphereT = 1.0;


/*  Initialize alpha blending function.
 */
static void init(void)
{
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glShadeModel (GL_FLAT);
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

void drawCube() {
  glPushMatrix ();
    glColor4f(1.0, 0.0, 1.0, cubeT);
    glTranslatef (0.15, 0.15, 0.0);
    glRotatef (15.0, 1.0, 1.0, 0.0);
    glRotatef (30.0, 0.0, 1.0, 0.0);
    
    glutSolidCube(0.4);
  glPopMatrix (); 
}

void drawCone() {
  glPushMatrix ();
    glColor4f(0.0, 1.0, 1.0, coneT);
    glRotatef(60.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.2, 0.6, 20.0, 20.0);
    glRotatef(-60.0, 1.0, 0.0, 0.0);
  glPopMatrix (); 
}

void drawSphere() {
  glPushMatrix ();
    glColor4f(1.0, 1.0, 0.0, sphereT);
    glutSolidSphere(0.4, 16, 16);
  glPopMatrix (); 
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
  
  drawSphere();
  drawCone();
  drawCube();
  

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h) 
      gluOrtho2D (1.5, -1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w);
   else 
      gluOrtho2D (1.5, -1.5*(GLfloat)w/(GLfloat)h, 1.5, -1.5);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'n':
      case 'N':
         if(coneT == 0.5) {
           coneT = 1.0;
         } else {
          coneT = 0.5;
         }
         break;

      case 'b':
      case 'B':
         if(cubeT == 0.5) {
           cubeT = 1.0;
         } else {
          cubeT = 0.5;
         }
         break;
      case 's':
      case 'S':
         if(sphereT == 0.5) {
           sphereT = 1.0;
         } else {
          sphereT = 0.5;
         }
         break;
      case 27:  /*  Escape key  */
         exit(0);
         break;
      default:
         break;
   }
   glutPostRedisplay();
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutCreateWindow (argv[0]);
   init();
   glutReshapeFunc (reshape);
   glutKeyboardFunc (keyboard);
   glutDisplayFunc (display);
   glutMainLoop();
   return 0;
}
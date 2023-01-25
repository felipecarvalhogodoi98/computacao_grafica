#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

static int shoulder = 0, elbow = 0, difusaEnable = 0, especularEnable = 0;
GLfloat posicao[] = { 30.0, 30.0, 60.0, 1.0 };
GLfloat difusa0[] = { 0.9, 0.9, 0.9, 1.0 };
GLfloat difusa1[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat ambiente[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat especularidade[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat luzEspecular[] = { 1.0, 0.0, 1.0, 1.0 };

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);

   glMateriali(GL_FRONT, GL_SHININESS, 50);
   glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa0);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao);

   glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa1);
   glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);   
   glLightfv(GL_LIGHT1, GL_POSITION, posicao);

   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

   glColor3f(0.0f,0.0f,0.7f);
   glPushMatrix();
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();

   //dedos
   glTranslatef (0.0, 0.0, 0.0);
   glRotatef ((GLfloat) 0, 0.0, 0.0, 1.0);
   glTranslatef (1.1, 0.15, 0.4);
   glPushMatrix();
   glScalef (0.2, 0.1, 0.2);
   glColor3f(1.0f,1.0f,0.0f);
   glutSolidCube (1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (0.0, 0.0, 0.0);
   glRotatef ((GLfloat) 0, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, -0.4);
   glPushMatrix();
   glScalef (0.2, 0.1, 0.2);
   glColor3f(1.0f,0.0f,0.0f);
   glutSolidCube (1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (0.0, 0.0, 0.0);
   glRotatef ((GLfloat) 0, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, -0.4);
   glPushMatrix();
   glScalef (0.2, 0.1, 0.2);
   glColor3f(0.0f,1.0f,0.0f);
   glutSolidCube (1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (0.0, 0.0, 0.0);
   glRotatef ((GLfloat) 0, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.3, 0.4);
   glPushMatrix();
   glScalef (0.2, 0.1, 0.2);
   glColor3f(0.0f,1.0f,1.0f);
   glutSolidCube (1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glutSolidCube (1.0);
   glPopMatrix();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   float l = 4;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0); 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.9);
}

void keyboard (unsigned char key, int x, int y)
{
   printf("key %c\n", key);
   switch (key) {
      case 's':
         shoulder = (shoulder + 5) % 360;
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
         break;
      case 'e':
         elbow = (elbow + 5) % 360;
         break;
      case 'E':
         elbow = (elbow - 5) % 360;
         break;
      case '0':
         glDisable(GL_LIGHT0);
         glDisable(GL_LIGHT1);
         break;
      case '1':
         glEnable(GL_LIGHT0);
         glDisable(GL_LIGHT1);
         break;
      case '2':
         glDisable(GL_LIGHT0);
         glEnable(GL_LIGHT1);
         break;
      case '3':
         glEnable(GL_LIGHT0);
         glEnable(GL_LIGHT1);
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
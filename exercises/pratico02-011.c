#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int zbuffer = 0;
int backface = 0;

// void init(void) 
// {
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = { 50.0 };
//    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

//    glClearColor (0.0, 0.0, 0.0, 0.0);
//    glShadeModel (GL_SMOOTH);

//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
// }

void changeAlg() {
  printf("zbuffer %d\n", zbuffer);
  printf("backface %d\n", backface);

  if(zbuffer) {
    glEnable(GL_DEPTH_TEST); 
  } else {
    glDisable(GL_DEPTH_TEST);
  }

  if(backface) {
    glEnable(GL_CULL_FACE); 
  } else {
    glDisable(GL_CULL_FACE);
  }
  glFlush ();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  changeAlg(); 
  glCullFace(GL_FRONT); 

  glBegin(GL_QUADS);
  
	// frente
  glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f( 0.5f, -0.5f, 0.5f);
	glVertex3f( 0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// tras
  glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f( 0.5f, 0.5f, -0.5f);
	glVertex3f( 0.5f, -0.5f, -0.5f);

	
	// esquerda
  glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	
  // direta
  glColor3f(0.5f, 0.0f, 0.0f);
	glVertex3f( 0.5f, -0.5f, -0.5f);
	glVertex3f( 0.5f, 0.5f, -0.5f);
	glVertex3f( 0.5f, 0.5f, 0.5f);
	glVertex3f( 0.5f, -0.5f, 0.5f);

	// cima
  glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f( 0.5f, 0.5f, 0.5f);
	glVertex3f( 0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// baixo
  glColor3f(0.0f, 0.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f( 0.5f, -0.5f, -0.5f);
	glVertex3f( 0.5f, -0.5f, 0.5f);

	glEnd();
  glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef (45.0, 1.0, 0.0, 0.0);
   glRotatef (45.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      case 'z':
        if(zbuffer) {
          zbuffer = 0;
        } else {
          zbuffer = 1;
        }
        break;

      case 'b':
        if(backface) {
          backface = 0;
        } else {
          backface = 1;
        }
        break;
   }

   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
  //  init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
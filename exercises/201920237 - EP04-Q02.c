#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glut.h>

int breakpoint = 0;

void init(void)
{
   glEnable (GL_LINE_SMOOTH);
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
   glLineWidth (1.0);

   glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Bresenham(int x1, int y1, int x2, int y2)
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = x1 < x2 ? 1 : -1;
  int sy = y1 < y2 ? 1 : -1;
  int err = dx - dy;

  
  glColor3f((rand() % 5) / (rand()%50*1.0) , (rand() % 50) / (rand()%100*1.0) , (rand() % 50) / (rand()%100*1.0) );

  while(1) {

    glVertex2i(x1, y1);

    if (x1 == x2 && y1 == y2) break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  } 
}

void paintRandomPoint() {
  int x1, y1, x2, y2;
  x1 = rand() % 800 - 400;
  y1 = rand() % 800 - 400;
  x2 = rand() % 800 - 400;
  y2 = rand() % 800 - 400;

  Bresenham(x1, y1, x2, y2);
}

static void display()
{  
  glPushMatrix();
  glBegin(GL_POINTS);
  
  paintRandomPoint();

  glEnd();
  glPopMatrix();
  glFlush ();

  if(!breakpoint) {
    usleep(500000);
    glutPostRedisplay();
  }
}
  

void KeyboardFunc(unsigned char key, int x, int y) {
  printf("key %d\n", key);
  printf("key %c\n", key);

  breakpoint = breakpoint ? 0 : 1;

  glutPostRedisplay();
}

void SpecialFunc(int key, int x, int y) {
  printf("special %d\n", key);
  
  glutPostRedisplay();
}
  
int main(int argc, char* argv[]) { 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100); 
  init();
  glutCreateWindow("OpenGL - Pratico04-01");   
  glutDisplayFunc(display);
  gluOrtho2D(-400, 400, -400, 400); 
  glutKeyboardFunc(KeyboardFunc);
  glutSpecialFunc(SpecialFunc);
  glutMainLoop(); 
  return 0;
} 
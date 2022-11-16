#include <GL/glut.h>
#include <stdio.h>

GLint open = 0;
double asp=1;
GLfloat fovy = 30.0;

  
void RenderScene(void) {
  glClearColor(0.0f,0.0f,0.0f,0.0f); 
  glClear( GL_COLOR_BUFFER_BIT ); 
  glBegin( GL_LINES ); 
    glColor3f(0.0f,0.0f,1.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(2.0f,0.0f,0.0f); 
    glColor3f(1.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,2.0f,0.0f); 
    glColor3f(0.0f,1.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,2.0f); 
  glEnd(); 
  glBegin( GL_POLYGON ); 
    glColor3f(1.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.2f,0.0f); 
    glVertex3f(0.2f,0.3f,0.0f); 
    glVertex3f(0.4f,0.2f,0.0f); 
    glVertex3f(0.4f,0.0f,0.0f); 
  glEnd(); 
  glBegin( GL_QUADS ); 
    glColor3f(0.0f,0.0f,1.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.4f); 
    glVertex3f(0.0f,0.2f,0.4f); 
    glVertex3f(0.0f,0.2f,0.0f); 
  glEnd(); 
  glBegin( GL_QUAD_STRIP ); 
    glColor3f(0.0f,1.0f,0.0f); 
    glVertex3f(0.0f,0.2f,0.0f); 
    glVertex3f(0.0f,0.2f,0.4f); 
    glVertex3f(0.2f,0.3f,0.0f); 
    glVertex3f(0.2f,0.3f,0.4f); 
    glVertex3f(0.4f,0.2f,0.0f); 
    glVertex3f(0.4f,0.2f,0.4f); 
  glEnd(); 
  glColor3f(0.0f,1.0f,1.0f); 
  glBegin( GL_QUADS ); 
    glVertex3f(0.4f,0.0f,0.0f);
    glVertex3f(0.4f,0.2f,0.0f);
    glVertex3f(0.4f,0.2f,0.4f);
    glVertex3f(0.4f,0.0f,0.4f);
  glEnd(); 
  glColor3f(1.0f,1.0f,1.0f); 
  glBegin( GL_QUADS ); 
    glVertex3f(0.15f,0.0f,0.4f);
    glVertex3f(0.0f,0.0f,0.4f);
    glVertex3f(0.0f,0.2f,0.4f);
    glVertex3f(0.15f,0.2f,0.4f);

    glVertex3f(0.25f,0.2f,0.4f);
    glVertex3f(0.25f,0.175f,0.4f);
    glVertex3f(0.15f,0.175f,0.4f);
    glVertex3f(0.15f,0.2f,0.4f);
    
    glVertex3f(0.25f,0.2f,0.4f);
    glVertex3f(0.25f,0.0f,0.4f);
    glVertex3f(0.4f,0.0f,0.4f);
    glVertex3f(0.4f,0.2f,0.4f);
  glEnd(); 
      glColor3f(1.0f,0.9f,1.0f);
  glBegin( GL_TRIANGLES ); 
    glVertex3f(0.0f,0.2f,0.4f);
    glVertex3f(0.2f,0.3f,0.4f);
    glVertex3f(0.4f,0.2f,0.4f);
  glEnd(); 

  glPushMatrix();
  glColor3f(1.0f,1.0f,0.0f);

  if(open){
    glTranslatef(0.15f,0.0f,0.4f);
    glRotatef(-65.0f, 0.0f,1.0f, 0.0f); 
    glBegin( GL_QUADS );
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(0.0f,0.175f,0.0f);
      glVertex3f(0.1f,0.175f,0.0f);
      glVertex3f(0.1f,0.0f,0.0f);
    glEnd();
  } else {
    glBegin( GL_QUADS ); 
      glVertex3f(0.15f,0.0f,0.4f);
      glVertex3f(0.15f,0.175f,0.4f);
      glVertex3f(0.25f,0.175f,0.4f);
      glVertex3f(0.25f,0.0f,0.4f);
    glEnd();
  }
  glPopMatrix();

  glFlush(); 
} 
  
void ChangeSize(GLsizei w,GLsizei h) {
  asp = w/h;
  glViewport(0,0,w,h); 
  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity(); 
  gluPerspective(fovy,asp,0.0,10.0); 
  glMatrixMode( GL_MODELVIEW ); 

  glTranslatef(0.0f,0.0f,-3.0f); 
  glRotatef(30.0f,1.0f,0.0f,0.0f); 
  glRotatef(-45.0f,0.0f,1.0f,0.0f);


} 

void MouseOptions(int button, int state, int x, int y)
{
  if (state == GLUT_UP) {
    if(open){
      open = 0;
    } else {
      open = 1;
    }
    RenderScene(); 
  } 
         
    glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y) {
  printf("%c\n", key);
  if(key == 'p'){
    fovy += 1.0;
  }

  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity(); 
  gluPerspective(fovy,asp,0.0,10.0); 

  glutPostRedisplay();
}
  
int main(int argc, char* argv[]) { 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow("OpenGL - Pratico02"); 
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutMouseFunc(MouseOptions);
  glutKeyboardFunc(KeyboardFunc);
  glutMainLoop(); 
  return 0;
} 
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

const double DISTANCE = 3.0;
const double PI = 3.14;

GLint open = 0;
double asp = 1.0;

GLfloat fovy = 30.0;

GLint camAngleX = 224;
GLint camAngleY = -29;

GLfloat eyex = 0;
GLfloat eyey = 0;
GLfloat eyez = 0;

#define	checkImageWidth 96
#define	checkImageHeight 96
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint textureId;

void makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         if (c) {
          checkImage[i][j][0] = (GLubyte) 201;
          checkImage[i][j][1] = (GLubyte) 69;
          checkImage[i][j][2] = (GLubyte) 43;
          checkImage[i][j][3] = (GLubyte) 255;
         } else {
          checkImage[i][j][0] = (GLubyte) 243;
          checkImage[i][j][1] = (GLubyte) 130;
          checkImage[i][j][2] = (GLubyte) 91;
          checkImage[i][j][3] = (GLubyte) 255;
         }
         
      }
   }
}

void init() {
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  makeCheckImage();

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(
    GL_TEXTURE_2D, 
    0, 
    GL_RGBA, 
    checkImageWidth, 
    checkImageHeight,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    checkImage
  );

}

void renderRoof() {
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);    
  glBindTexture(GL_TEXTURE_2D, textureId);
  
  glBegin( GL_QUADS ); 
    glColor3f(1.0f,1.0f,1.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0f,0.2f,0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.0f,0.2f,0.4f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.2f,0.3f,0.4f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.2f,0.3f,0.0f);

    glTexCoord2f(0.0, 0.0); glVertex3f(0.2f,0.3f,0.0f);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.2f,0.3f,0.4f);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.4f,0.2f,0.4f);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.4f,0.2f,0.0f);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}
  
void RenderScene(void) {
  glClearColor(0.0f,0.0f,0.0f,0.0f); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
  renderRoof(); 
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

void movement() {
  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity(); 
  gluPerspective(fovy,asp,1.0,10.0); 
 
  glMatrixMode( GL_MODELVIEW ); 
  glLoadIdentity(); 
  gluLookAt(eyex, eyey, eyez,
            0.0, 0.0, 0.0,
            0.0, 2.0, 0.0
  );
}
  
void ChangeSize(GLsizei w,GLsizei h) {
  asp = (double) w/ (double) h;
  glViewport(0,0,w,h); 

  movement();
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
  if(key == 'o'){
    fovy -= 1.0;
  }
  
  movement();

  glutPostRedisplay();
}

void SpecialFunc(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      camAngleY += 1;
      break;
    case GLUT_KEY_DOWN:
      camAngleY -= 1;
      break;
    case GLUT_KEY_LEFT:
      camAngleX -= 1;
      break;
    case GLUT_KEY_RIGHT:
      camAngleX += 1;

      break;
  }

  eyex = DISTANCE * -sinf(camAngleX*(PI/180)) * cosf((camAngleY)*(PI/180));
  eyey = DISTANCE * -sinf((camAngleY)*(PI/180));
  eyez = -DISTANCE * cosf((camAngleX)*(PI/180)) * cosf((camAngleY)*(PI/180));

  movement();

  glutPostRedisplay();
}
  
int main(int argc, char* argv[]) {
  eyex = DISTANCE * -sinf(camAngleX*(PI/180)) * cosf((camAngleY)*(PI/180));
  eyey = DISTANCE * -sinf((camAngleY)*(PI/180));
  eyez = -DISTANCE * cosf((camAngleX)*(PI/180)) * cosf((camAngleY)*(PI/180));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow("OpenGL - Pratico02"); 
  init();
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutMouseFunc(MouseOptions);
  glutKeyboardFunc(KeyboardFunc);
  glutSpecialFunc(SpecialFunc);
  glutMainLoop(); 
  return 0;
} 
// Actions
// Mouse Left -> menu
// CTRL + (left or right) -> rotate item
// Keys up, down, left, right -> move item
#include <stdio.h>
#include <GL/glut.h>

#define BED 0
#define CABINET 1
#define CHAIR 2
#define TABLE 3

struct Item;

typedef void (*callback)();

typedef struct {
  int isVisible;
  int type;
  GLfloat x;
  GLfloat y;
  GLfloat angle;
  callback render;

  GLfloat dimensionX;
  GLfloat dimensionY;
} Item;

Item itens[4];
int selected = -1;

void createItem(
  Item *item, 
  int isVisible, 
  int type, 
  GLfloat x, 
  GLfloat y,
  GLfloat angle, 
  callback render,
  GLfloat dimensionX, 
  GLfloat dimensionY
) {
  item->isVisible = isVisible;
  item->type = type;
  item->x = x;
  item->y = y;
  item->angle = angle;
  item->render = render;
  item->dimensionX = dimensionX; 
  item->dimensionY = dimensionY;
}

void renderBed() {
  glBegin( GL_LINE_LOOP );
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,1.0f,0.0f);
    glVertex3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
  glEnd();
  glBegin( GL_LINES );
    glVertex3f(1.95f,1.0f,0.0f);
    glVertex3f(1.95f,0.0f,0.0f);
  glEnd();
  glBegin( GL_LINE_LOOP );
    glVertex3f(1.90f,0.15f,0.0f);
    glVertex3f(1.90f,0.85f,0.0f);
    glVertex3f(1.55f,0.85f,0.0f);
    glVertex3f(1.55f,0.15f,0.0f);
  glEnd();
}

void renderCabinet() {
  glBegin( GL_LINE_LOOP );
    glVertex3f(0.9f,0.0f,0.0f);
    glVertex3f(0.9f,0.45f,0.0f);
    glVertex3f(0.0f,0.45f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
  glEnd();
  glBegin( GL_LINE_LOOP );
    glVertex3f(0.85f,0.05f,0.0f);
    glVertex3f(0.85f,0.4f,0.0f);
    glVertex3f(0.05f,0.4f,0.0f);
    glVertex3f(0.05f,0.05f,0.0f);
  glEnd();
}

void renderChair() {
  glBegin( GL_LINE_STRIP );
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3f(0.35f,0.45f,0.0f);
    glVertex3f(0.35f,0.05f,0.0f);
    glVertex3f(0.05f,0.05f,0.0f);
    glVertex3f(0.05f,0.45f,0.0f);
    glVertex3f(0.0f,0.45f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.4f,0.0f,0.0f);
    glVertex3f(0.4f,0.0f,0.0f);
    glVertex3f(0.4f,0.0f,0.0f);
    glVertex3f(0.4f,0.45f,0.0f);
    glVertex3f(0.0f,0.45f,0.0f);
  glEnd();
}

void renderTable() {
  glBegin( GL_LINE_LOOP );
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(1.6f,0.0f,0.0f);
    glVertex3f(1.6f,0.6f,0.0f);
    glVertex3f(0.0f,0.6f,0.0f);
  glEnd();
  glBegin( GL_LINE_LOOP );
    glVertex3f(0.2f,0.3f,0.0f);
    glVertex3f(0.6f,0.3f,0.0f);
    glVertex3f(0.6f,0.5f,0.0f);
    glVertex3f(0.2f,0.5f,0.0f);
  glEnd();
  glBegin( GL_LINE_LOOP );
    glVertex3f(0.3f,0.1f,0.0f);
    glVertex3f(0.5f,0.1f,0.0f);
    glVertex3f(0.5f,0.2f,0.0f);
    glVertex3f(0.3f,0.2f,0.0f);
  glEnd();
  
}

void renderItem(Item* item) {
  if(!item->isVisible || selected == -1) return;
  
  glPushMatrix();

  glTranslatef(item->x,item->y,0.4f);

  glTranslatef(item->dimensionX/2,item->dimensionY/2,0.4f);
  glRotatef(item->angle, 0.0f, 0.0f, 1.0f);
  glTranslatef(-item->dimensionX/2,-item->dimensionY/2,0.4f);

  item->render();

  
  glPopMatrix();
}

void RenderScene(void) { 
  glClearColor(0.0f,0.0f,0.0f,0.0f); 
  glClear( GL_COLOR_BUFFER_BIT );
  // BEDROOM
  glBegin( GL_LINES ); 
    glColor3f(1.0f,1.0f,1.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(3.5f,0.0f,0.0f); 

    glVertex3f(3.5f,0.0f,0.0f); 
    glVertex3f(3.5f,2.5f,0.0f); 

    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,2.5f,0.0f);

    glVertex3f(0.0f,2.5f,0.0f);
    glVertex3f(3.5f,2.5f,0.0f);

    glColor3f(0.5f,0.5f,0.5f);
  	glVertex3f(0.05f,2.5f,0.0f);
    glVertex3f(0.75f,2.5f,0.0f);

    glVertex3f(1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
  glEnd(); 

  glColor3f(0.9f,0.9f,0.9f);

  for (int i = 0; i < 4; i++) {
    renderItem(&itens[i]);
  }

  glFlush(); 
}
  
void ChangeSize(GLsizei width,GLsizei height) { 
  glViewport(0,0,width,height); 
  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity(); 
  gluPerspective(30.0,width/height,1.0,10.0); 
  glMatrixMode( GL_MODELVIEW ); 
  glLoadIdentity(); 
  glTranslatef(-1.5f,-1.5f,-10.0f);   
} 

void KeyboardFunc(unsigned char key, int x, int y) {
  printf("key %d\n", key);
  printf("key %c\n", key);
  glutPostRedisplay();
}

void SpecialFunc(int key, int x, int y) {
  printf("special %d\n", key);

  int ctrl = glutGetModifiers() == 2; // 1 shift, 2 ctrl, 4 alt
  
  if(selected == -1) return;
  
  if(ctrl) {
    switch (key) {
      case GLUT_KEY_LEFT:
        itens[selected].angle -= 1.0;
        break;
      case GLUT_KEY_RIGHT:
        itens[selected].angle += 1.0;
        break;
    }
    glutPostRedisplay();
    return;
  } 

  switch (key) {
    case GLUT_KEY_UP:
      itens[selected].y += 0.05;
      break;
    case GLUT_KEY_DOWN:
      itens[selected].y -= 0.05;
      break;
    case GLUT_KEY_LEFT:
      itens[selected].x -= 0.05;
      break;
    case GLUT_KEY_RIGHT:
      itens[selected].x += 0.05;
      break;
  }
  
  glutPostRedisplay();
}

void AddItens(int op) {
  switch(op) {
    case TABLE:
      itens[TABLE].isVisible = 1;
      break;
    case CHAIR:
      itens[CHAIR].isVisible = 1;
      break;
    case BED:
      itens[BED].isVisible = 1;
      break;
    case CABINET:
      itens[CABINET].isVisible = 1;
      break;
  }
  selected = op;
  glutPostRedisplay();
}

void RemoveItens(int op) {
  switch(op) {
    case TABLE:
      itens[TABLE].isVisible = 0;
      break;
    case CHAIR:
      itens[CHAIR].isVisible = 0;
      break;
    case BED:
      itens[BED].isVisible = 0;
      break;
    case CABINET:
      itens[CABINET].isVisible = 0;
      break;
  }
  selected = op;
  glutPostRedisplay();
}

void SelectItem(int op) {
  selected = op;
  glutPostRedisplay();
}

void Menu(int op) {}

void CreateMenu() {
  int menu, addItens, removeItens, selectItem;

  addItens = glutCreateMenu(AddItens);
  glutAddMenuEntry("Escrivaninha", TABLE);
  glutAddMenuEntry("Cadeira",CHAIR);
  glutAddMenuEntry("Armario",CABINET);
  glutAddMenuEntry("Cama",BED);

  removeItens = glutCreateMenu(RemoveItens);
  glutAddMenuEntry("Escrivaninha", TABLE);
  glutAddMenuEntry("Cadeira",CHAIR);
  glutAddMenuEntry("Armario",CABINET);
  glutAddMenuEntry("Cama",BED);

  selectItem = glutCreateMenu(SelectItem);
  glutAddMenuEntry("Escrivaninha", TABLE);
  glutAddMenuEntry("Cadeira",CHAIR);
  glutAddMenuEntry("Armario",CABINET);
  glutAddMenuEntry("Cama",BED);

  menu = glutCreateMenu(Menu);
  glutAddSubMenu("ADD",addItens);
  glutAddSubMenu("REMOVE",removeItens);
  glutAddSubMenu("SELECT",selectItem);
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MouseFunc(int button, int state, int x, int y){        
  switch(button) {
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) 
      CreateMenu();
      break;
  }
        
  glutPostRedisplay();
}

void MainMenu(int item){
  printf("menu %d\n", item);
}
  
int main(int argc, char* argv[]) { 
  createItem(&itens[0], 0, BED, 0, 0, 0, renderBed, 2.0f, 1.0f);
  createItem(&itens[1], 0, CABINET, 0, 0, 0, &renderCabinet, 0.9f, 0.45f);
  createItem(&itens[2], 0, CHAIR, 0, 0, 0, &renderChair, 0.4f, 0.45f);
  createItem(&itens[3], 0, TABLE, 0, 0, 0, &renderTable, 1.6f, 0.6f);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow("OpenGL - Poligonos");   
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(ChangeSize);
  glutKeyboardFunc(KeyboardFunc);
  glutSpecialFunc(SpecialFunc);
  glutMouseFunc(MouseFunc);
  glutMainLoop(); 
  return 0;
} 
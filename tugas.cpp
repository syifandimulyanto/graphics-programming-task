// Compile: g++ tugas.cpp -o tugas -lglut -lGL -lGLU
#include "GL/glut.h"
GLUquadric *q = gluNewQuadric();
GLfloat camY = 0.0;
GLfloat camX = 0.0;
GLfloat angle = 1;
GLfloat direction = 1;

void initGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
   gluLookAt(
    camX, camY, 0, 
    0, 0,-15,
    0,1,0);

  glTranslatef(0, -1, -20);
  glColor3f(0,1,0);
  glEnable(GL_TEXTURE_2D);
  gluQuadricTexture(q, true);
  gluCylinder(q, 1, 1, 2, 8, 8);
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
    glTranslatef(5, 0, 0); 
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5,0);
        glVertex3f(1.5,-1,0);
        glTexCoord2f(0,1);
        glVertex3f(-1.5,-1,0);
        glTexCoord2f(1,1);
        glVertex3f(0,2,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  glPopMatrix(); 

  glPushMatrix();
    glTranslatef(-5, 0, 0);
    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(q, true);
    gluSphere(q, 1.5, 8, 8);
    glDisable(GL_TEXTURE_2D);
  glPopMatrix(); 

  glutSwapBuffers();
}

void timer(int value)
{
  glutPostRedisplay();
  glutTimerFunc(15, timer, 0);
}

void reshape(GLsizei width, GLsizei height)
{
  if (height == 0)
    height = 1;
  GLfloat aspect = (GLfloat)width / (GLfloat)height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keyControl(int k, int x, int y)
{
  switch(k) {
    case GLUT_KEY_UP: camY ++; break;
    case GLUT_KEY_DOWN: camY --; break;
    case GLUT_KEY_LEFT: camX --; break;
    case GLUT_KEY_RIGHT: camX ++; break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("3d-animation");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  initGL();
  glutTimerFunc(0, timer, 0);
  glutSpecialFunc(keyControl);
  glutMainLoop();
  return 0;
}
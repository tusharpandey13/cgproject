#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
// #include <bits/stdc++.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

using namespace std;

#define MAX_ASTEROIDS  100

int x;
int y;
int i;
int IDX;
int rocketLife = 10000;

double asteroidSpeed = 5;
double dv = 1.5;
double maxspeed = 7;
double dx = 0;
double dy = 0;
double xR = 0, yR = 0;
double xA[MAX_ASTEROIDS], yA[MAX_ASTEROIDS];

GLint asteroidLeft[MAX_ASTEROIDS];


void Rocket() {
  glColor3f(0.306, 0.306, 0.298);

  glPushMatrix();


  glBegin(GL_POLYGON);
  glVertex2f(40, 25);
  glVertex2f(120, 25);
  glVertex2f(120, -25);
  glVertex2f(40, -25);
  glEnd();

  glColor3f(1, 1, 1);
  glBegin(GL_POLYGON);
  glVertex2f(20, 0);
  glVertex2f(40, 25);
  glVertex2f(40, -25);
  glEnd();

  glColor3f(1, 1, 1);
  glBegin(GL_POLYGON);
  glVertex2f(120, 25);
  glVertex2f(140, 45);
  glVertex2f(140, -45);
  glVertex2f(120, -25);
  glEnd();


  glColor3f(1, 1, 1);

  glBegin(GL_POLYGON);
  glVertex2f(65, 25);
  glVertex2f(90, 45);
  glVertex2f(90, 25);
  glEnd();

  glColor3f(1, 1, 1);

  glBegin(GL_POLYGON);
  glVertex2f(65, -25);
  glVertex2f(90, -45);
  glVertex2f(90, -25);
  glEnd();


  glPopMatrix();


}

void Asteroid() {
  glPushMatrix();
  glLoadIdentity();
  glColor3f(1, 0, 0);
  glTranslated(xA[IDX], yA[IDX], 0);
  glScalef(18, 20, 0);
  glutSolidSphere(1.5, 20, 100);
  glPopMatrix();
}

void setAsteroidPosition() {

  for (int i = 0; i < MAX_ASTEROIDS ; i++) {
    asteroidLeft[i] = true;
  }

  xA[0] = -(200 * MAX_ASTEROIDS) - 600;

  for (int i = 0; i < MAX_ASTEROIDS ; i++) {
    yA[i] = rand() % 600;
    if (int(yA[i]) % 2)
      yA[i] *= -1;
    xA[i + 1] = xA[i] + 200;
  }
}


void GenerateAsteroids() {

  for (int i = 0; i < MAX_ASTEROIDS ; i++) {
    IDX = i;
    xA[i] += asteroidSpeed;

    if (asteroidLeft[i])
      Asteroid();
  }

}

bool isRocketSafe() {
  for (int i = 0 ; i < MAX_ASTEROIDS ; i++) {
    if (asteroidLeft[i] & (((xR >= xA[i] / 2 - 25) && (xR <= xA[i] / 2 + 25))
                           && ((yR >= yA[i] / 2 - 80) && (yR <= yA[i] / 2 + 80)))) {
      asteroidLeft[i] = 0;
      return false;
    }
  }
  return true;
}

void CreateRocket(int x, int y) {
  glPushMatrix();
  glTranslated(min(max(-500, x), 500), min(max(-500, y), 500), 0);
  if (!isRocketSafe() && rocketLife) rocketLife -= 1;
  Rocket();
  glEnd();
  glPopMatrix();
}

void DisplayLife() {
  char temp[40];
  glColor3f(1, 1, 1);
  sprintf(temp, "CRASHES LEFT = %d", rocketLife);
  glRasterPos3f(500, 500, 0);
  int l = strlen(temp);
  for (int i = 0 ; i < l ; i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i]);
  glColor3f(1, 0, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  DisplayLife();
  glScalef(2, 2, 0);
  xR += dx;
  yR += dy;
  if(abs(xR) >= 500) dx = 0;
  if(abs(yR) >= 500) dy = 0;
  if (rocketLife) CreateRocket(xR, yR);
  GenerateAsteroids();
  glFlush();
  glLoadIdentity();
  glutSwapBuffers();
}

void keys(int key, int x, int y) {
  if (key == GLUT_KEY_RIGHT) dx = min(dx + dv, maxspeed);
  else if (key == GLUT_KEY_LEFT) dx = max(dx - dv, -maxspeed);
  else if (key == GLUT_KEY_UP) dy = min(dy + dv, maxspeed);
  else if (key == GLUT_KEY_DOWN) dy = max(dy - dv, -maxspeed);
  else if (key && GLUT_KEY_RIGHT && GLUT_KEY_DOWN){
    dx = min(dx + dv, maxspeed);
    dy = max(dy - dv, -maxspeed);
  }
  else if (key && GLUT_KEY_RIGHT && GLUT_KEY_UP){
    dx = min(dx + dv, maxspeed);
    dy = max(dy + dv, maxspeed);
  }
  else if (key && GLUT_KEY_LEFT && GLUT_KEY_DOWN){
    dx = max(dx - dv, -maxspeed);
    dy = max(dy - dv, -maxspeed);
  }
  else if (key && GLUT_KEY_LEFT && GLUT_KEY_UP){
    dx = max(dx - dv, -maxspeed);
    dy = max(dy + dv, maxspeed);
  }
  display();
}
void init() {
  glClearColor(0, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-1000, 1000, -1000, 1000);
  glMatrixMode(GL_MODELVIEW);
}

void idleCallBack() {
  display();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitContextVersion(2, 0);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("ASTEROIDS GAME");
  glewInit();

  glutDisplayFunc(display);
  glutSpecialFunc(keys);
  glutIdleFunc(idleCallBack);
  init();
  setAsteroidPosition();
  glutMainLoop();
  return 0;
}
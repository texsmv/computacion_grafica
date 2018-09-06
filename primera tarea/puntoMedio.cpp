#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
int height = 600;
int width = 800;



float toNC(int max, int v){
  return v / (float) max;
}

void write_pixel(int x, int y){
  float pos_x = toNC(width / 2, x);
  float pos_y = toNC(height / 2, y);
  glVertex2f(pos_x, pos_y);
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glLoadIdentity();

    int x1, y1, x2, y2;
    x1 = 0;
    y1 = 0;
    x2 = 350;
    y2 = 40;

    int dx, dy, incE, incNE, d, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;
    glBegin(GL_POINTS);

    write_pixel(x, y);
    while (x < x2) {
      if(d <= 0){
        d = d + incE;
        x = x + 1;
      }
      else{
        d = d + incNE;
        x = x + 1;
        y = y + 1;
      }
      write_pixel(x, y);
    }

    glEnd();
    glFlush();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glClearColor(0, 0, 0, 0);
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}

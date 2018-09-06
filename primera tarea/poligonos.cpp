#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
float pi2 = 6.28318530718;


void draw_line(float x1, float y1, float x2, float y2){
  glBegin(GL_LINES);

      glVertex3f(x1, y1, 0.0f);
      glVertex3f(x2, y2, 0.0f);


  glEnd();
}


void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glLoadIdentity();

    int num_vertices = 100;
    float radio = 0.8;
    float d_teta;
    d_teta = (pi2) / num_vertices;
    float teta = 0;




    float x2, y2,x1, y1;

    for(int i = 0; i < num_vertices; i++){
      // cout<<atan(teta)<<endl;
      x1 = cos(d_teta * i) * radio;
      y1 = sin(d_teta * i) * radio;
      x2 = cos(d_teta * (i + 1)) * radio;
      y2 = sin(d_teta * (i + 1)) * radio;
      // cout<<x1<<" "<<y1<<endl;
      // cout<<teta<<endl;
      // draw_line(0, 0, x2, y2);
      draw_line(x1, y1, x2, y2);

    }
      glFlush();



}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glClearColor(0, 0, 0, 0);
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}

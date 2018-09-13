#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
float pi2 = 6.28318530718;


void draw_line(float x1, float y1, float x2, float y2, float z1, float z2){
  glBegin(GL_LINES);

      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y2, z2);


  glEnd();
}

void draw_turtle(float radio, int num_vertices, float pos_x, float pos_y, float pos_z){
  float d_teta;
  d_teta = (pi2) / num_vertices;
  float teta = 0;




  float x2, y2,x1, y1;

  for(int i = 0; i < num_vertices; i++){
    x1 = cos(d_teta * i) * radio;
    y1 = sin(d_teta * i) * radio;
    x2 = cos(d_teta * (i + 1)) * radio;
    y2 = sin(d_teta * (i + 1)) * radio;
    draw_line(pos_x + x1, pos_y + y1, pos_x + x2, pos_y + y2, pos_z, pos_z);

  }
    glFlush();

}



void display(void) {


  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
  // glLoadIdentity();

  // dibujando caparazon
  draw_turtle(0.4, 34, 0.0, 0.0, 0.0);
  draw_turtle(0.3, 34, 0.0, 0.0, 0.1);
  draw_turtle(0.2, 34, 0.0, 0.0, 0.15);
  draw_turtle(0.1, 34, 0.0, 0.0, 0.165);

  // dibujando cabeza
  draw_turtle(0.15, 24, 0.0, 0.5, 0.0);

  //dibujando extremidades
  draw_turtle(0.1, 24, -0.4, 0.3, 0.0);
  draw_turtle(0.1, 24, 0.4,  0.3, 0.0);
  draw_turtle(0.1, 24, -0.4, -0.3, 0.0);
  draw_turtle(0.1, 24, 0.4,  -0.3, 0.0);



  glutSwapBuffers();

}

void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-2.0, 3.0, 4.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '8':
		glRotatef(1.0,1.,0.,0.);
		break;
	case '5':
		glRotatef(1.0,-1.,0.,0.);
		break;
	case '4':
		glRotatef(1.0,0.,0.,1.);
		break;
	case '6':
		glRotatef(1.0,0.,0.,-1.);
		break;
	case 'w':
		glTranslatef(0.0,0.1,0.);
		break;
	case 'a':
		glTranslatef(-0.1,0.,0.0);
		break;
	case 's':
		glTranslatef(0.0,-0.1,0.);
		break;
	case 'd':
		glTranslatef(0.1,0.0,0.0);
		break;
	case 'q':
		exit(0);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("tecnunLogo");
  glClearColor(0, 0, 0, 0);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}

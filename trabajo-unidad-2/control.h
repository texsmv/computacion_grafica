#ifndef CONTROL_H
#define CONTROL_H

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "poligono.h"

using namespace std;

#define window_height 800
#define window_width 800

vector<int> cola_puntos_x;
vector<int> cola_puntos_y;
vector<figura*> figuras;
int numberOfLists = 0;
bool save_points = false;

int color_option, menu_option, draw_option, action_option;

// Funciones de control
void color_controller(int id){
  glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
  switch (id)
  {
  case 1 : /* change color to red */
      glColor3d (1.0, 0.0, 0.0);
      break;
  case 2 : /* change color to green */
      glColor3d (0.0, 1.0, 0.0);
      break;
  case 3 : /* change color to blue */
      glColor3d (0.0, 0.0, 1.0);
      break;
  case 4 : /* change color to black */
      glColor3d (0.0, 0.0, 0.0);
      break;
  default : /* for any case not covered above, leave color unchanged */
      break;
  }
  glEndList ();
}
void menu_controller(int id){

}
void draw_controller(int id){

  glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
  switch (id){
      case 1 :

          break;
      case 2 :
          save_points = true;
          break;
      case 3 :

          break;
      case 4:
          break;
      case 5 :
          break;
      default : /* for any case not covered above, leave line thickness unchanged */
          break;
  }
  glEndList ();
}
void action_controller(int id){

}


void init(){
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,0,0);
  glPointSize(3);
  gluOrtho2D(-window_width/2, window_width/2, -window_height/2, window_height/2);



  color_option = glutCreateMenu(color_controller);
      glutAddMenuEntry ("Rojo", 1);
      glutAddMenuEntry ("Verde", 2);
      glutAddMenuEntry ("Azul", 3);
      glutAddMenuEntry ("Negro", 4);

  draw_option =  glutCreateMenu (draw_controller);
      glutAddMenuEntry ("P.regular", 1);
      glutAddMenuEntry ("P.irregular", 2);
      glutAddMenuEntry ("Linea", 3);
      glutAddMenuEntry ("Circulo", 4);
      glutAddMenuEntry ("Parabola", 5);
  action_option = glutCreateMenu(action_controller);
      glutAddMenuEntry ("Mover", 1);
      glutAddMenuEntry ("Escalar", 2);
      glutAddMenuEntry ("Rotar", 3);

  menu_option = glutCreateMenu (menu_controller);
      glutAddSubMenu ("Color", color_option);
      glutAddSubMenu ("Figura", draw_option);
      glutAddSubMenu ("Accion", action_option);
      glutAddMenuEntry ("Limpiar ventana", 2);
      glutAddMenuEntry ("Salir", 3);
  glutAttachMenu (GLUT_RIGHT_BUTTON);


}


void mouse_controller(int button, int state, int mouse_x, int mouse_y){
  if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    if(save_points){
      int pos_x, pos_y;
      user_coors(pos_x, pos_y, mouse_x, window_height - mouse_y);
      cola_puntos_x.push_back(pos_x);
      cola_puntos_y.push_back(pos_y);
      // cout<<cola_puntos.size()<<endl;
    }
  }

}


void keyboard_controller(unsigned char key, int x, int y){
  figura* fig;
	switch (key){
	case 'd':
    fig = new poligono(cola_puntos_x, cola_puntos_y);
		fig->draw();
    fig->calc_min_max();
    cout<<"asa"<<endl;
    fig->fill_lienzo();

    cola_puntos_x.clear();
    cola_puntos_y.clear();
    save_points = false;
    glFlush();
		break;
	case 'q':
		exit(0);
		break;
	}


}


void display(){
  vector<int> xs;
  vector<int> ys;

  calc_regular_polygon(0, 0, 7, 100, xs, ys);

  // draw_line(0, 0, 100, 100);
  draw_polygon(xs, ys);


  glFlush();
}






#endif

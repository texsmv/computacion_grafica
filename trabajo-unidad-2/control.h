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
bool b_move = false;
bool b_rotate = false;
bool b_scale = false;

int color_option, menu_option, draw_option, action_option;
int fig_pos = 0;
float* mat_transformacion = new float[9];
float* mat_temp = new float[9];





// Funciones de control



void refresh(){
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,0,0);
  glPointSize(3);

  for(int i = 0; i < figuras.size(); i++){
    figuras.at(i)->redraw();
  }
}


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
  glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
  switch (id){
      case 1 :
          b_move = true;
          break;
      case 2 :
          b_scale = true;
          break;
      case 3 :


          b_rotate = true;
          break;

      default : /* for any case not covered above, leave line thickness unchanged */
          break;
  }
  glEndList ();
}


void init(){
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,0,0);
  glPointSize(3);
  gluOrtho2D(-window_width/2, window_width/2, -window_height/2, window_height/2);



  load_identity(mat_transformacion);


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
    int pos_x, pos_y;
    user_coors(pos_x, pos_y, mouse_x, window_height - mouse_y);
    if(save_points){
      cola_puntos_x.push_back(pos_x);
      cola_puntos_y.push_back(pos_y);
      // cout<<cola_puntos.size()<<endl;
    }
    if(b_move){

      float* mat_temp = get_mat_traslacion(pos_x - figuras.at(fig_pos)->xmin, pos_y - figuras.at(fig_pos)->ymin);
      mat_transformacion = mat_mult(mat_temp, mat_transformacion);
      b_move = false;
    }
    if(b_rotate){
      float teta;
      cout<<"inserte angulo: ";
      cin>>teta;

      float* mat_traslacion = get_mat_traslacion( -pos_x , -pos_y);
      float* mat_traslacion_inversa = get_mat_traslacion( pos_x , pos_y);
      float* mat_rotacion = get_mat_rotacion(teta);

      mat_transformacion = mat_mult(mat_traslacion, mat_transformacion);
      mat_transformacion = mat_mult(mat_rotacion, mat_transformacion);
      mat_transformacion = mat_mult(mat_traslacion_inversa, mat_transformacion);
      b_rotate = false;
    }

    if(b_scale){
      float sx, sy;
      cout<<"inserte sx: ";
      cin>>sx;
      cout<<"inserte sy: ";
      cin>>sy;

      float* mat_traslacion = get_mat_traslacion( -pos_x , -pos_y);
      float* mat_traslacion_inversa = get_mat_traslacion( pos_x , pos_y);
      float* mat_escalamiento = get_mat_escalamiento(sx, sy);

      mat_transformacion = mat_mult(mat_traslacion, mat_transformacion);
      mat_transformacion = mat_mult(mat_escalamiento, mat_transformacion);
      mat_transformacion = mat_mult(mat_traslacion_inversa, mat_transformacion);
      b_scale = false;
    }


  }

}


void keyboard_controller(unsigned char key, int x, int y){
  figura* fig;
  float* mat;
	switch (key){
	case 'd':
    fig = new poligono(cola_puntos_x, cola_puntos_y);
    figuras.push_back(fig);
    fig->draw();
    fig->calc_min_max();
    fig->fill_lienzo();



    cola_puntos_x.clear();
    cola_puntos_y.clear();
    save_points = false;
    glFlush();

    // refresh();
		break;

  case 'o':
    cout<<"Done"<<endl;
    figuras.at(fig_pos)->apply_trans(mat_transformacion);
    load_identity(mat_transformacion);
    refresh();
    break;

	case 'q':
		exit(0);
		break;
	}


}


void display(){
  // vector<int> xs;
  // vector<int> ys;

  // calc_regular_polygon(0, 0, 7, 100, xs, ys);

  // draw_line(0, 0, 100, 100);
  // draw_polygon(xs, ys);


  glFlush();
}






#endif

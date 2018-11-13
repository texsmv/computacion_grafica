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

bool b_pol_reg_c = false;
bool b_pol_reg_r = false;
int temp_x, temp_y;

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
  glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
  switch (id){

      case 2 :
          figuras.clear();
          refresh();
          fig_pos = 0;
          break;
      case 3 :

          exit(0);
          break;

      default : /* for any case not covered above, leave line thickness unchanged */
          break;
  }
  glEndList ();
}
void draw_controller(int id){

  glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
  switch (id){
      case 1 :
          system("clear");
          cout<<"Seleccione un punto como centro del poligono"<<endl;
          b_pol_reg_c = true;
          b_pol_reg_r = true;

          break;
      case 2 :
          system("clear");
          cout<<"Seleccione los vertices del poligono"<<endl;
          cout<<"Presione  d  al terminar"<<endl;
          save_points = true;
          break;

      default : /* for any case not covered above, leave line thickness unchanged */
          break;
  }
  glEndList ();
}
void action_controller(int id){
  glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
  switch (id){
      case 0:
          system("clear");
          cout<<"Ingrese el numero de la figura que modificara"<<endl;
          cin>>fig_pos;
          break;
      case 1:
          system("clear");
          cout<<"Seleccione el punto al que se movera con click izquierdo"<<endl;

          b_move = true;
          break;
      case 2 :
          system("clear");
          cout<<"Seleccione el punto de referencia para escalar con click izquierdo"<<endl;
          b_scale = true;
          break;
      case 3 :

          system("clear");
          cout<<"Seleccione el punto de referencia para rotar con click izquierdo"<<endl;
          b_rotate = true;
          break;
      case 4 :
          figuras[fig_pos]->paint();
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

  action_option = glutCreateMenu(action_controller);
      glutAddMenuEntry ("Seleccionar Figura", 0);
      glutAddMenuEntry ("Mover", 1);
      glutAddMenuEntry ("Escalar", 2);
      glutAddMenuEntry ("Rotar", 3);
      glutAddMenuEntry ("Colorear", 4);

  menu_option = glutCreateMenu (menu_controller);
      glutAddSubMenu ("Figura", draw_option);
      glutAddSubMenu ("Color", color_option);
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
      cout<<"Presione r para realizar la transformacion"<<endl;

    }
    if(b_rotate){
      float teta;
      cout<<"Inserte angulo en degrees: ";
      cin>>teta;
      teta *= 0.0174533;

      float* mat_traslacion = get_mat_traslacion( -pos_x , -pos_y);
      float* mat_traslacion_inversa = get_mat_traslacion( pos_x , pos_y);
      float* mat_rotacion = get_mat_rotacion(teta);

      mat_transformacion = mat_mult(mat_traslacion, mat_transformacion);
      mat_transformacion = mat_mult(mat_rotacion, mat_transformacion);
      mat_transformacion = mat_mult(mat_traslacion_inversa, mat_transformacion);
      b_rotate = false;
      cout<<"Presione r para realizar la transformacion"<<endl;

    }

    if(b_scale){
      float sx, sy;
      cout<<"Inserte sx: ";
      cin>>sx;
      cout<<"Inserte sy: ";
      cin>>sy;

      float* mat_traslacion = get_mat_traslacion( -pos_x , -pos_y);
      float* mat_traslacion_inversa = get_mat_traslacion( pos_x , pos_y);
      float* mat_escalamiento = get_mat_escalamiento(sx, sy);

      mat_transformacion = mat_mult(mat_traslacion, mat_transformacion);
      mat_transformacion = mat_mult(mat_escalamiento, mat_transformacion);
      mat_transformacion = mat_mult(mat_traslacion_inversa, mat_transformacion);
      b_scale = false;
      cout<<"Presione r para realizar la transformacion"<<endl;

    }
    if(b_pol_reg_r){
      if(b_pol_reg_c){
        temp_x = pos_x;
        temp_y = pos_y;
        b_pol_reg_c = false;

        cout<<"Seleccione un punto para calcular el radio desde el centro"<<endl;
      }
      else{
        int radio = sqrt(pow(temp_x - pos_x, 2) + pow(temp_y - pos_y, 2));
        vector<int> xs, ys;
        int n_lados;
        cout<<"Ingrese el numero de lados: ";
        cin>>n_lados;
        calc_regular_polygon(temp_x, temp_y, n_lados, radio, xs, ys);
        figura * fig = new poligono(xs, ys);
        fig->draw();
        fig->calc_min_max();
        fig->fill_lienzo();
        glFlush();
        figuras.push_back(fig);
        b_pol_reg_r = false;
        cout<<"Figura "<<figuras.size() - 1<<" creada"<<endl;

      }
    }


  }

}


void keyboard_controller(unsigned char key, int x, int y){
  figura* fig;
  float* mat;
	switch (key){
	case 'd':
    if(save_points){

      fig = new poligono(cola_puntos_x, cola_puntos_y);
      figuras.push_back(fig);
      fig->draw();
      fig->calc_min_max();
      fig->fill_lienzo();




      cola_puntos_x.clear();
      cola_puntos_y.clear();
      save_points = false;

      cout<<"Figura "<<figuras.size() - 1<<" creada"<<endl;
      refresh();
    }
		break;

  case 'r':
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



  glFlush();
}






#endif

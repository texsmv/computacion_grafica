#ifndef DIBUJADO_H
#define DIBUJADO_H

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

#define window_height 800
#define window_width 800
#define pi2 6.28318530718

// declaracion de Funciones

void draw_line(int, int, int, int);
void draw_line(int, int, int, int, vector<int>&, vector<int>&);
void draw_polygon(vector<int>, vector<int>);








// Funciones de dibujado

void draw_pixel(int x, int y){
    glVertex2i(x, y);
}



void draw_line(int x1, int y1, int x2, int y2){
  int v_x = x2 - x1;
  int v_y = y2 - y1;

  int octante = -1;

  int * la;

  if(v_x >= 0 && v_y >= 0){
    if(v_x > v_y)
      octante = 0;
    else
      octante = 1;
  }
  else if(v_x <= 0 && v_y >= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 3;
    else
      octante = 2;
  }
  else if(v_x <= 0 && v_y <= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 4;
    else
      octante = 5;
  }
  else if(v_x >= 0 && v_y <= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 7;
    else
      octante = 6;
  }
  if(octante == -1)
    cout<<"Error reconociendo octante"<<endl;

  // cout<< "octante: "<<octante<<endl;
  // cout<<x2<<" "<<y2<<endl;

  int tx = -x1;
  int ty = -y1;

  x1 = 0;
  y1 = 0;

  x2 += tx;
  y2 += ty;


  int temp;
  switch (octante) {

    case 1: temp = x2;
      x2 = y2;
      y2 = temp;
      break;
    case 2: temp = x2;
      x2 = y2;
      y2 = -temp;
      break;

    case 3:
      x2 = -x2;
      break;

    case 4:
      x2 = -x2;
      y2 = -y2;
      break;

    case 5: temp = x2;
      x2 = -y2;
      y2 = -temp;
      break;

    case 6: temp = x2;
      x2 = -y2;
      y2 = temp;
      break;

    case 7:
      y2 = -y2;
      break;


  }

  // cout<<x2<<" "<<y2<<endl;

  int dx, dy, incE, incNE, d, x, y;

  dx = x2 - x1;
  dy = y2 - y1;
  d = 2 * dy - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  x = x1;
  y = y1;




  glBegin(GL_POINTS);



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

    switch (octante) {
      case 0: draw_pixel(x - tx, y - ty);
        break;
      case 1: draw_pixel(y - tx, x - ty);
        break;
      case 2: draw_pixel(-y - tx, x - ty);
        break;
      case 3: draw_pixel(-x - tx, y - ty);
        break;
      case 4: draw_pixel(-x - tx, -y - ty);
        break;
      case 5: draw_pixel(-y - tx, -x - ty);
        break;
      case 6: draw_pixel(y - tx, -x - ty);
        break;
      case 7: draw_pixel(x - tx, -y - ty);
        break;
    }

  }

  glEnd();
}

void draw_line(int x1, int y1, int x2, int y2, vector<int>& xs, vector<int>& ys){
  int v_x = x2 - x1;
  int v_y = y2 - y1;

  int octante = -1;

  int * la;

  if(v_x >= 0 && v_y >= 0){
    if(v_x > v_y)
      octante = 0;
    else
      octante = 1;
  }
  else if(v_x <= 0 && v_y >= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 3;
    else
      octante = 2;
  }
  else if(v_x <= 0 && v_y <= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 4;
    else
      octante = 5;
  }
  else if(v_x >= 0 && v_y <= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 7;
    else
      octante = 6;
  }
  if(octante == -1)
    cout<<"Error reconociendo octante"<<endl;

  // cout<< "octante: "<<octante<<endl;
  // cout<<x2<<" "<<y2<<endl;

  int tx = -x1;
  int ty = -y1;

  x1 = 0;
  y1 = 0;

  x2 += tx;
  y2 += ty;


  int temp;
  switch (octante) {

    case 1: temp = x2;
      x2 = y2;
      y2 = temp;
      break;
    case 2: temp = x2;
      x2 = y2;
      y2 = -temp;
      break;

    case 3:
      x2 = -x2;
      break;

    case 4:
      x2 = -x2;
      y2 = -y2;
      break;

    case 5: temp = x2;
      x2 = -y2;
      y2 = -temp;
      break;

    case 6: temp = x2;
      x2 = -y2;
      y2 = temp;
      break;

    case 7:
      y2 = -y2;
      break;


  }

  // cout<<x2<<" "<<y2<<endl;

  int dx, dy, incE, incNE, d, x, y;

  dx = x2 - x1;
  dy = y2 - y1;
  d = 2 * dy - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  x = x1;
  y = y1;




  glBegin(GL_POINTS);



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

    switch (octante) {
      case 0: draw_pixel(x - tx, y - ty);
        xs.push_back(x - tx);
        ys.push_back(y - ty);
        break;
      case 1: draw_pixel(y - tx, x - ty);
        xs.push_back(y - tx);
        ys.push_back(x - ty);
        break;
      case 2: draw_pixel(-y - tx, x - ty);
        xs.push_back(-y - tx);
        ys.push_back(x - ty);
        break;
      case 3: draw_pixel(-x - tx, y - ty);
        xs.push_back(-x - tx);
        ys.push_back(y - ty);
        break;
      case 4: draw_pixel(-x - tx, -y - ty);
        xs.push_back(-x - tx);
        ys.push_back(-y - ty);
        break;
      case 5: draw_pixel(-y - tx, -x - ty);
        xs.push_back(-y - tx);
        ys.push_back(-x - ty);
        break;
      case 6: draw_pixel(y - tx, -x - ty);
        xs.push_back(y - tx);
        ys.push_back(-x - ty);
        break;
      case 7: draw_pixel(x - tx, -y - ty);
        xs.push_back(x - tx);
        ys.push_back(-y - ty);
        break;
    }

  }

  glEnd();
}


void coordinates_conversion(int x1_min, int y1_min, int x1_max, int y1_max, int x2_min, int y2_min, int x2_max, int y2_max, int& x1, int& y1, int x2, int y2){
  x1 = ((x2 - x2_min) / (float)(x2_max - x2_min) * (x1_max - x1_min)) + x1_min;
  y1 = ((y2 - y2_min) / (float)(y2_max - y2_min) * (y1_max - y1_min)) + y1_min;
}

int user_coors(int& x1, int& y1, int x2, int y2){
  coordinates_conversion(-window_width/2, -window_height/2, window_width/2, window_height/2, 0, 0, window_width, window_height, x1, y1, x2, y2);
}

void draw_polygon(vector<int> puntos_x, vector<int> puntos_y, vector<int>& xs, vector<int>& ys){
  for(int i = 0; i < puntos_x.size() - 1; i++){
    draw_line(puntos_x.at(i), puntos_y.at(i), puntos_x.at(i + 1), puntos_y.at(i + 1), xs, ys);
  }
  draw_line(puntos_x.at(puntos_x.size() - 1), puntos_y.at(puntos_x.size() - 1), puntos_x.at(0), puntos_y.at(0), xs, ys);
}

void draw_polygon(vector<int> puntos_x, vector<int> puntos_y){
  for(int i = 0; i < puntos_x.size() - 1; i++){
    draw_line(puntos_x.at(i), puntos_y.at(i), puntos_x.at(i + 1), puntos_y.at(i + 1));
  }
  draw_line(puntos_x.at(puntos_x.size() - 1), puntos_y.at(puntos_x.size() - 1), puntos_x.at(0), puntos_y.at(0));
}



void calc_regular_polygon(int x, int y, int n_lados, int radio, vector<int>& puntos_x, vector<int>& puntos_y){

  float d_teta;
  d_teta = (pi2) / n_lados;


  float x1, y1;

  for(int i = 0; i < n_lados; i++){
    // cout<<atan(teta)<<endl;
    x1 = cos(d_teta * i) * radio;
    y1 = sin(d_teta * i) * radio;

    puntos_x.push_back(x1);
    puntos_y.push_back(y1);

  }
}

#endif

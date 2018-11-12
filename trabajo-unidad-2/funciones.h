#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>


#define window_height 800
#define window_width 800


// Funciones de control 

void init(){
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,0,0);
  glPointSize(3);
  gluOrtho2D(-window_width/2, window_width/2, -window_height/2, window_height/2);
}

void display(){
  glFlush();
}






// Funciones de dibujado


void draw_line(int x1, int y1, int x2, int y2){
  int v_x = x2 - x1;
  int v_y = y2 - y1;

  int octante;

  int * la;

  if(v_x > 0 && v_y > 0){
    if(v_x > v_y)
      octante = 0;
    else
      octante = 1;
  }
  else if(v_x < 0 && v_y > 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 3;
    else
      octante = 2;
  }
  else if(v_x < 0 && v_y < 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 4;
    else
      octante = 5;
  }
  else if(v_x > 0 && v_y < 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 7;
    else
      octante = 6;
  }

  cout<< "octante: "<<octante<<endl;
  cout<<x2<<" "<<y2<<endl;

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

  cout<<x2<<" "<<y2<<endl;

  int dx, dy, incE, incNE, d, x, y;

  dx = x2 - x1;
  dy = y2 - y1;
  d = 2 * dy - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  x = x1;
  y = y1;




  glBegin(GL_POINTS);

  // setPixel(0, 0);
  // setPixel(50, 50);
  // setPixel(-50, -50);
  // setPixel(50, -50);
  // setPixel(-50, 50);

  // setPixel(x, y);


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
      case 0: setPixel(x - tx, y - ty);
        break;
      case 1: setPixel(y - tx, x - ty);
        break;
      case 2: setPixel(-y - tx, x - ty);
        break;
      case 3: setPixel(-x - tx, y - ty);
        break;
      case 4: setPixel(-x - tx, -y - ty);
        break;
      case 5: setPixel(-y - tx, -x - ty);
        break;
      case 6: setPixel(y - tx, -x - ty);
        break;
      case 7: setPixel(x - tx, -y - ty);
        break;
    }

  }

  glEnd();
  glFlush();
}

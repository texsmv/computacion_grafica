#ifndef POLIGONO_H
#define POLIGONO_H

#include "dibujado.h"
#include "poligono.h"

class poligono:public  figura{

    public:
        int tipo, radio,n_lados;
        int ox, oy;
        

        poligono(int n,int t){n_lados = n; tipo = t; ox = oy = radio = 0;}
        poligono(vector<int> xs, vector<int> ys){
          vertices_x = xs;
          vertices_y = ys;
        }

        void draw(){
          draw_polygon(vertices_x, vertices_y, puntos_x, puntos_y);
        }



        poligono(){}
        ~poligono(){}

};


#endif

#ifndef FIGURA_H
#define FIGURA_H


#include "dibujado.h"

class figura{
    public:
        int xmin, ymin, xmax, ymax, h, w;
        bool **lienzo;
        vector<int> puntos_x;
        vector<int> puntos_y;
        vector<int> vertices_x;
        vector<int> vertices_y;
        figura(){}
        ~figura(){}
        virtual void draw(){}
        virtual void redraw(){
          glBegin(GL_POINTS);
          for(int i = 0; i < puntos_x.size(); i++){
            draw_pixel(puntos_x.at(i), puntos_y.at(i));

          }
          glEnd();
          glFlush();
        }

        virtual void paint(){
          bool pintar = false;
          bool cambio = false;
          glBegin(GL_POINTS);
          for(int j = 0; j < h; j++){
            pintar = false;
            cambio = false;
            for(int i = 0; i < w; i++){
              if(!is_in(i + xmin, j + ymin, vertices_x, vertices_y)){
                if(lienzo[j][i] == true){
                  cambio = true;
                }
                if(cambio && !lienzo[j][i]){
                  if(pintar)
                  pintar = false;
                  else
                  pintar = true;
                  cambio = false;
                }
                if(pintar){
                  draw_pixel(i + xmin, j + ymin);
                  puntos_x.push_back(i + xmin);
                  puntos_y.push_back(j + ymin);
                }

              }

            }
          }
          glEnd();
          calc_min_max();
          fill_lienzo();
        }

        virtual void apply_trans(float* mat){


        	vector<int> res_x;
        	vector<int> res_y;


        	int punto_x, punto_y, n_punto_x, n_punto_y;
        	for(int j = 0; j < h; j++){
        		for(int i = 0; i < w; i++){
        			if(lienzo[j][i]){
        				// cout<<j + ymin<<" "<<i + xmin<<endl;
        				punto_y = j + ymin ;
        				punto_x = i + xmin ;
                // cout<<"j: "<<j<<" i: "<<i<<" h: "<<h<<" w: "<<w<<" cos : "<<cos(teta)<<" "<<punto_x<<" sin : "<<sin(teta)<<" "<<punto_y <<endl;
                // cout<<cos(teta) * (float)punto_x<<" "<<sin(teta) * (float)punto_y<<endl;
        				// cout<<punto_x<<" "<<punto_y<<endl;
        				n_punto_x = mat[0] * (float)punto_x + mat[1] * (float)punto_y + mat[2] * 1;
        				n_punto_y = mat[3] * (float)punto_x + mat[4] * (float)punto_y + mat[5] * 1;

                // glBegin(GL_POINTS);
                // draw_pixel(n_punto_x, n_punto_y);
                // glEnd();
                // glFlush();

        				res_x.push_back(n_punto_x);
        				res_y.push_back(n_punto_y);

        				// cout<<n_punto_x<<" "<<n_punto_y<<endl;
        			}
        		}
        	}
          puntos_x = res_x;
          puntos_y = res_y;
          glFlush();
          calc_min_max();
          fill_lienzo();

        }


        virtual void calc_min_max(){
          xmin = xmax = puntos_x.at(0);
          for(int i = 0; i < puntos_x.size(); i++){
            if(xmin > puntos_x.at(i)){
              xmin = puntos_x.at(i);
            }
            if(xmax < puntos_x.at(i)){
              xmax = puntos_x.at(i);
            }
          }
          ymin = ymax = puntos_y.at(0);
          for(int i = 0; i < puntos_y.size(); i++){
            if(ymin > puntos_y.at(i)){
              ymin = puntos_y.at(i);
            }
            if(ymax < puntos_y.at(i)){
              ymax = puntos_y.at(i);
            }
          }

        }
        virtual void fill_lienzo(){
          h = fabs(ymax - ymin) + 1;
        	w = fabs(xmax - xmin) + 1;
        	lienzo = new bool*[h];

        	for (size_t i = 0; i < h; i++) {
        		lienzo[i] = new bool[w];
            for(int j = 0; j < w; j++){
              lienzo[i][j] = false;
            }
        	}



          for(int i = 0; i < puntos_x.size(); i++){
            // cout<<i<<" "<<puntos_x.at(i)<<" "<<puntos_x.at(i) - xmin<<" "<<puntos_y.at(i)<<" "<<puntos_y.at(i) - ymin<<endl;
            lienzo[puntos_y.at(i) - ymin][puntos_x.at(i) - xmin] = true;

          }

        }

};


#endif

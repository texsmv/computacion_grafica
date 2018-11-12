#ifndef FIGURA_H
#define FIGURA_H

#include "dibujado.h"

class figura{
    public:
        int xmin, ymin, xmax, ymax, h, w;
        bool **lienzo;
        vector<int> puntos_x;
        vector<int> puntos_y;
        figura(){}
        ~figura(){}
        virtual void draw(){}
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
        	}



          cout<<xmin<<" "<< xmax<<endl;
          cout<<ymin<<" "<< ymax<<endl;
          cout<<"dimensiones: "<<h<<" "<<w<<endl;

          for(int i = 0; i < puntos_x.size(); i++){
            // cout<<i<<" "<<puntos_x.at(i)<<" "<<puntos_x.at(i) - xmin<<" "<<puntos_y.at(i)<<" "<<puntos_y.at(i) - ymin<<endl;
            lienzo[puntos_y.at(i) - ymin][puntos_x.at(i) - xmin] = true;
          }
          cout<<"lienzo filled"<<endl;


        	// --------------

        	float teta = 0.785398;

        	vector<int> res_x;
        	vector<int> res_y;

        	int centro_x = xmin;
        	int centro_y = ymin;

        	int t_x = -centro_x;
        	int t_y = -centro_y;

          glBegin(GL_POINTS);
        	int punto_x, punto_y, n_punto_x, n_punto_y;
          cout<<"asassdds"<<endl;
        	for(int j = 0; j < h; j++){
        		for(int i = 0; i < w; i++){
        			if(lienzo[j][i]){
        				// cout<<j + ymin<<" "<<i + xmin<<endl;
        				punto_y = j + ymin + t_y;
        				punto_x = i + xmin + t_x;
        				cout<<punto_x<<" "<<punto_y<<endl;
        				n_punto_x = cos(teta) * punto_x - sin(teta) * punto_y;
        				n_punto_y = sin(teta) * punto_x + cos(teta) * punto_y;
                draw_pixel(n_punto_x, n_punto_y);
        				res_x.push_back(n_punto_x);
        				res_y.push_back(n_punto_y);

        				cout<<n_punto_x<<" "<<n_punto_y<<endl;
        			}
        		}
        	}
          glEnd();
          glFlush();
        }

};


#endif

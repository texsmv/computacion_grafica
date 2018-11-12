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
        virtual void redraw(){
          glBegin(GL_POINTS);
          for(int i = 0; i < puntos_x.size(); i++){
            draw_pixel(puntos_x.at(i), puntos_y.at(i));

          }
          glEnd();
          glFlush();
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
          cout<<"inicio"<<endl;
          h = fabs(ymax - ymin) + 1;
        	w = fabs(xmax - xmin) + 1;
        	lienzo = new bool*[h];

        	for (size_t i = 0; i < h; i++) {
        		lienzo[i] = new bool[w];
            for(int j = 0; j < w; j++){
              lienzo[i][j] = false;
            }
        	}





          cout<<xmin<<" "<< xmax<<endl;
          cout<<ymin<<" "<< ymax<<endl;
          cout<<"dimensiones: "<<h<<" "<<w<<endl;

          for(int i = 0; i < puntos_x.size(); i++){
            // cout<<i<<" "<<puntos_x.at(i)<<" "<<puntos_x.at(i) - xmin<<" "<<puntos_y.at(i)<<" "<<puntos_y.at(i) - ymin<<endl;
            lienzo[puntos_y.at(i) - ymin][puntos_x.at(i) - xmin] = true;

          }
          cout<<"lienzo filled"<<endl;



          //
        	// float teta = 1.905398;
          //
        	// vector<int> res_x;
        	// vector<int> res_y;
          //
        	// int centro_x = (xmin + xmax) / 2;
        	// int centro_y = (ymin + ymax) / 2;
          //
        	// int t_x = -centro_x;
        	// int t_y = -centro_y;
          //
        	// int punto_x, punto_y, n_punto_x, n_punto_y;
          // cout<<"asassdds"<<endl;
        	// for(int j = 0; j < h; j++){
        	// 	for(int i = 0; i < w; i++){
        	// 		if(lienzo[j][i]){
        	// 			// cout<<j + ymin<<" "<<i + xmin<<endl;
        	// 			punto_y = j + ymin ;
        	// 			punto_x = i + xmin ;
          //       cout<<"j: "<<j<<" i: "<<i<<" h: "<<h<<" w: "<<w<<" cos : "<<cos(teta)<<" "<<punto_x<<" sin : "<<sin(teta)<<" "<<punto_y <<endl;
          //       cout<<cos(teta) * (float)punto_x<<" "<<sin(teta) * (float)punto_y<<endl;
        	// 			cout<<punto_x<<" "<<punto_y<<endl;
        	// 			n_punto_x = cos(teta) * (float)punto_x - sin(teta) * (float)punto_y;
        	// 			n_punto_y = sin(teta) * (float)punto_x + cos(teta) * (float)punto_y;
          //       glBegin(GL_POINTS);
          //       draw_pixel(n_punto_x, n_punto_y);
          //       glEnd();
          //       glFlush();
          //       // getchar();
        	// 			res_x.push_back(n_punto_x);
        	// 			res_y.push_back(n_punto_y);
          //
        	// 			cout<<n_punto_x<<" "<<n_punto_y<<endl;
        	// 		}
        	// 	}
        	// }
          // cout<<"fin"<<endl;
        }

};


#endif

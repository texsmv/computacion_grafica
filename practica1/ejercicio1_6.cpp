#include <iostream>
#include <math.h>
using namespace std;

void inp_to_ndc(int ndh, int ndv, int dcx, int dcy, float& ndcx, float& ndcy){

  ndcx = (float) dcx / ndh;
  ndcy = (float) dcy / ndv;
}


void ndc_to_user(float  xmax, float ymax, float xmin, float ymin, float ndcx, float ndcy, float& x, float& y){
  x = (xmax - xmin) * ndcx + xmin;
  y = (ymax - ymin) * ndcy + ymin;
}

void user_to_ndc(float  xmax, float ymax, float xmin, float ymin, float& ndcx, float& ndcy, float x, float y){
  ndcx = (x - xmin) / (xmax - xmin);
  ndcy = (y - ymin) / (ymax - ymin);
}

void ndc_to_dc(int ndh, int ndv, int& dcx, int& dcy, float ndcx, float ndcy){
  dcx = ceil(ndcx * ndh);
  dcy = ceil(ndcy * ndv);
}


int main(int argc, char** argv)
{
  int ndh = 1024;
  int ndv = 720;

  int dcx = 512;
  int dcy = 360;

  float ndcx;
  float ndcy;

  float xmin = -50;
  float ymin = -50;

  float xmax = 50;
  float ymax = 50;

  float x;
  float y;

  inp_to_ndc(ndh, ndv, dcx, dcy, ndcx, ndcy);
  ndc_to_user(xmax, ymax, xmin, ymin, ndcx, ndcy, x, y);

  cout<<ndcx<<" "<<ndcy<<endl;
  cout<<x<<" "<<y<<endl;

  user_to_ndc(xmax, ymax, xmin, ymin, ndcx, ndcy, x, y);
  cout<<ndcx<<" "<<ndcy<<endl;
  cout<<x<<" "<<y<<endl;

  ndc_to_dc(ndh, ndv, dcx, dcy, ndcx, ndcy);
  cout<<dcx<<" "<<dcy<<endl;

  return 0;
}

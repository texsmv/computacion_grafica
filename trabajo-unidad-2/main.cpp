#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "funciones.h"

using namespace std;
float pi2 = 6.28318530718;





int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_height, window_width);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Graficadora");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

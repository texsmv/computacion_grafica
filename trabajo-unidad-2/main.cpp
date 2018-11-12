#include "figura.h"
#include "control.h"







int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_height, window_width);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Graficadora");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse_controller);
    glutKeyboardFunc(keyboard_controller);
    glutMainLoop();
    return 0;
}

#include <GL/glut.h>
#include "car.h"
void TimeStep(int n) {
     glutTimerFunc(25, TimeStep, 0); glutPostRedisplay();
     }
void glDraw() {
    double static dx=-0.75;
    Point p={dx,-0.75};
    car zh(p);
    zh.move(&dx);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    zh.draw(); glutSwapBuffers(); glFlush();
}
int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Car");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw);
    glutTimerFunc(25, TimeStep, 0);
    glutMainLoop();
}
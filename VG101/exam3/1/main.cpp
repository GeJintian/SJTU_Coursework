#include <iostream>
#include<GL/freeglut.h>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include"figures.h"
#include "machine.h"


using namespace std;

void TimeStep(int n){
    glutTimerFunc(25,TimeStep,0);
    glutPostRedisplay();
}
void glDraw() {
     double static width=1, height=1.5, owidth=.175;
     machine zh;
     zh.turn();
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     zh.draw(); glutSwapBuffers(); glFlush();
     }
 int main (int argc, char *argv[]) {
     glutInit(&argc, argv);
     // glutInitWindowSize(500, 500);
     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
     glutCreateWindow("Home sweet home");
     glClearColor(1.0, 1.0, 1.0, 0.0); glClear(GL_COLOR_BUFFER_BIT);
     glutDisplayFunc(glDraw); glutTimerFunc(25, TimeStep, 0);
     glutMainLoop();
     }
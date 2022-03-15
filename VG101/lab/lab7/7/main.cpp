#include <iostream>
#include <GL/glut.h>
#include "figure.h"
void display(){
    Trapezium shape3;Parallelogram shape4;_triangle shape1;_rectangle shape2;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shape3.draw();shape3.move(0.5,0);shape3.draw();
    shape4.draw();shape4.move(0.5,0);shape4.draw();
    shape2.draw();shape2.move(0.5,0);shape2.draw();
    shape1.draw();shape1.move(0.5,0);shape1.draw();
    glutSwapBuffers(); glFlush();

}
int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    // glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("picture");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutMainLoop();
}
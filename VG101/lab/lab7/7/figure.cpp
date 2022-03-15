//
// Created by 69009 on 2017/12/6.
//

#include "figure.h"
#include <GL/glut.h>
Shape::~Shape(){}
_rectangle::_rectangle(Point pt1, Point pt2,
                     float red, float green, float blue) {
    p1=pt1; p2=pt2; r=red; g=green; b=blue;
}
void _rectangle::draw() {
    glColor3f(r, g, b); glBegin(GL_QUADS);
    glVertex2f(p1.x, p1.y); glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y); glVertex2f(p1.x, p2.y); glEnd();
}
void _rectangle::move(float dx, float dy) {
    p1.x+=dx;p1.y+=dy;p2.x+=dx;p2.y+=dy;
}
void _rectangle::zoom(float scale) {
    p1.x*=scale;p1.y*=scale;p2.x*=scale;p2.y*=scale;
}
_triangle::_triangle(Point pt1, Point pt2, Point pt3,
                   float red, float green, float blue) {
    p1=pt1; p2=pt2; p3=pt3; r=red; g=green; b=blue;
}
void _triangle::draw() {
    glColor3f(r, g, b); glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(p1.x, p1.y); glVertex2f(p2.x, p2.y); glVertex2f(p3.x, p3.y);
    glEnd();
}
void _triangle::move(float dx, float dy) {
    p1.x+=dx;p1.y+=dy;p2.x+=dx;p2.y+=dy;p3.x+=dx;p3.y+=dy;
}
void _triangle::zoom(float scale) {
    p1.x*=scale;p1.y*=scale;p2.x*=scale;p2.y*=scale;p3.x*=scale;p3.y*=scale;
}
Parallelogram::Parallelogram(Point pt1, Point pt2, Point pt3, float red, float green, float blue) {
    p1=pt1;p2=pt2;p3=pt3;r=red;g=green;b=blue;
}
void Parallelogram::draw() {
    glColor3f(r,g,b);glBegin(GL_QUADS);
    glVertex2f(p1.x,p1.y);glVertex2f(p2.x,p2.y);
    glVertex2f(p3.x,p3.y);glVertex2f(p1.x+p3.x-p2.x,p3.y);
    glEnd();
}
void Parallelogram::move(float dx, float dy) {
    p1.x+=dx;p1.y+=dy;p2.x+=dx;p2.y+=dy;p3.x+=dx;p3.y+=dy;
}
void Parallelogram::zoom(float scale) {
    p1.x*=scale;p1.y*=scale;p2.x*=scale;p2.y*=scale;p3.x*=scale;p3.y*=scale;
}
Trapezium::Trapezium(Point pt1, Point pt2, Point pt3, Point pt4, float red, float green, float blue) {
    p1=pt1;p2=pt2;p3=pt3;p4=pt4;r=red;g=green;b=blue;
}
void Trapezium::draw() {
    glColor3f(r,g,b);glBegin(GL_QUADS);
    glVertex2f(p1.x,p1.y);glVertex2f(p2.x,p2.y);glVertex2f(p3.x,p3.y);glVertex2f(p4.x,p4.y);
    glEnd();
}
void Trapezium::move(float dx, float dy) {
    p1.x+=dx;p1.y+=dy;p2.x+=dx;p2.y+=dy;p3.x+=dx;p3.y+=dy;p4.x+=dx;p4.y+=dy;
}
void Trapezium::zoom(float scale) {
    p1.x*=scale;p1.y*=scale;p2.x*=scale;p2.y*=scale;p3.x*=scale;p3.y*=scale;p4.x*=scale;p4.y*=scale;
}
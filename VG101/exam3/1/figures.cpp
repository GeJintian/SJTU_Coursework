//
// Created by 69009 on 2017/12/15.
//
#define PI 3.1415926
#include <GL/glut.h>
#include <cmath>
#include "figures.h"
 Shape::~Shape(){}
 Rectanglen::Rectanglen(Point pt1, Point pt2,
 float red, float green, float blue) {
 p1=pt1; p2=pt2; r=red; g=green; b=blue;
 }
 void Rectanglen::draw() {
     glColor3f(r, g, b); glBegin(GL_QUADS);
     glVertex2f(p1.x, p1.y); glVertex2f(p2.x, p1.y);
     glVertex2f(p2.x, p2.y); glVertex2f(p1.x, p2.y); glEnd();
     }
 Trianglen::Trianglen(Point pt1, Point pt2, Point pt3,
 float red, float green, float blue) {
 p1=pt1; p2=pt2; p3=pt3; r=red; g=green; b=blue;
 }
 void Trianglen::draw() {
     glColor3f(r, g, b); glBegin(GL_TRIANGLE_STRIP);
     glVertex2f(p1.x, p1.y); glVertex2f(p2.x, p2.y); glVertex2f(p3.x, p3.y);
     glEnd();
     }
Circle::Circle(Point pt, float red, float green, float blue, float m) {
    p1=pt;radius=m;r=red;g=green;b=blue;
}
void Circle::draw() {
    glColor3f(r,g,b);glBegin(GL_POLYGON);
    int i;
    for(i=0;i<100;i++){
        glVertex2f(p1.x+radius*cos(2*PI/100*i),p1.y+radius*sin(2*PI/100*i));
    }

}
Trapzium::Trapzium(Point pt1, Point pt2, Point pt3, Point pt4, float red, float green, float blue) {
    p1=pt1;p2=pt2;p3=pt3;p4=pt4;r=red;g=green;b=blue;
}
void Trapzium::draw() {
    glColor3f(r, g, b); glBegin(GL_QUADS);
    glVertex2f(p1.x, p1.y); glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y); glVertex2f(p4.x, p4.y); glEnd();
}
Line::Line(Point pt1, Point pt2, float red, float green, float blue) {
    p1=pt1; p2=pt2;  r=red; g=green; b=blue;
}
void Line::draw() {
    glColor3f(r,g,b);
    glBegin(GL_LINES);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
    glEnd();
}
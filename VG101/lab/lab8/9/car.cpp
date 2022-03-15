//
// Created by 69009 on 2017/12/14.
//


#include "car.h"
car::car(Point pt1) {
    Point p1,p2,p3,p4;
    p=pt1;
    p1={p.x,p.y};p2={p.x+0.5,p.y+0.25};
    sh[2]=new _rectangle(p1,p2);
    p1={p.x+0.15,p.y};
    sh[1]=new Circle(p1);
    p1={p.x+0.35,p.y};
    sh[0]=new Circle(p1);
    p1={p.x,p.y+0.25};p2={p.x+0.35,p.y+0.25};p3={p.x+0.3,p.y+0.4};p4={p.x+0.05,p.y+0.4};
    sh[3]=new Trapezium(p1,p2,p3,p4);
}
car::~car(){for(int i=0;i<4;i++)delete sh[i];}
void car::draw() {for(int i=0;i<4;i++)sh[i]->draw();}
void car::move(double*dx) {
    int static i=0;
    if(p.x<=0.25&&i==0){moveright(dx);}
    else if(p.x>=-0.75){i=1;moveleft(dx);}
    else i=0;
}
void car::moveleft(double*dx) {
    p.x-=0.01;*dx=p.x;
}
void car::moveright(double*dx) {
    p.x+=0.01;*dx=p.x;
}
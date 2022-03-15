//
// Created by 69009 on 2017/12/15.
//

#ifndef INC_1_FIGURES_H
#define INC_1_FIGURES_H

class Point { public: double x,y; };
class Shape {
     public: virtual void draw() = 0; virtual ~Shape();
     protected: float r, g, b;
     };
 class Rectanglen : public Shape {
     public: Rectanglen(Point pt1={-.5,-.5}, Point pt2={.5,.5},
     float r=0, float g=1, float b=0);
     void draw();
     private: Point p1,p2;
     };
 class Trianglen : public Shape {
     public: Trianglen(Point pt1={-.5,-.5}, Point pt2={.5,-.5},
     Point pt3={0,.5}, float r=0, float g=1, float b=0);
     void draw();
     private: Point p1,p2,p3;
     };
class Circle:public Shape{
public:Circle(Point pt={-0.6,0.4},float r=1,float g=0,float b=0,float m=0.2);
    void draw();
private:
    Point p1;
    float radius;
};
class Trapzium:public Shape{
public:Trapzium(Point pt1={0,0},Point pt2={0,0},Point pt3={0,0},Point pt4={0,0},float r=0,float g=0,float b=1);
    void draw();
private:
    Point p1,p2,p3,p4;
};
class Line: public Shape{
public:Line(Point pt1={0,0},Point pt2={0,0},float red=1,float green=0,float blue=0);
    void draw();
private:
    Point p1,p2;
};

#endif //INC_1_FIGURES_H

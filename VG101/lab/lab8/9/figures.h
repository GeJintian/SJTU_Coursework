//
// Created by 69009 on 2017/12/7.
//

#ifndef INC_9_FIGURES_H
#define INC_9_FIGURES_H


class Point { public: double x,y; };
class Shape {
public: virtual void draw() = 0; virtual ~Shape();
protected: float r, g, b;
};
class _rectangle : public Shape {
public: _rectangle(Point pt1={-1,-0.1}, Point pt2={-0.6,-0.4},
                   float r=0, float g=0, float b=1);

    void draw();void move(float dx,float dy);void zoom(float scale);
private: Point p1,p2;
};
class Trapezium: public Shape{
public:Trapezium(Point pt1={0,0},Point pt2={0.4,0},Point pt3={0.3,0.3},Point pt4={0.2,0.3},float r=1,float g=0,float b=0);
    void draw();void move(float dx,float dy);void zoom(float scale);
private:Point p1,p2,p3,p4;
};
class Circle:public Shape{
public:Circle(Point pt1={0,0},float r=0,float g=1,float b=0,float a=0.05);
    void draw();void move(float dx,float dy);void zoom(float scale);
private:Point p1;float radius;
};

#endif //INC_9_FIGURES_H

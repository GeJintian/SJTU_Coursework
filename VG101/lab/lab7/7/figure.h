//
// Created by 69009 on 2017/12/6.
//

#ifndef INC_7_FIGURE_H
#define INC_7_FIGURE_H


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
class _triangle : public Shape {
public: _triangle(Point pt1={-1,0}, Point pt2={-0.6,0},
                 Point pt3={-0.8,1}, float r=0.5, float g=0.5, float b=0);

    void draw();void move(float dx,float dy);void zoom(float scale);
private: Point p1,p2,p3;
};
class Parallelogram:public Shape{
public:Parallelogram(Point pt1={0,-0.1},Point pt2={0.3,-0.1},Point pt3={0.5,-0.3},float r=0.25,float g=0.75,float b=0);
    void draw();void move(float dx,float dy);void zoom(float scale);
private:Point p1, p2, p3;
};
class Trapezium: public Shape{
public:Trapezium(Point pt1={0,0},Point pt2={0.4,0},Point pt3={0.3,0.3},Point pt4={0.2,0.3},float r=1,float g=0,float b=0);
    void draw();void move(float dx,float dy);void zoom(float scale);
private:Point p1,p2,p3,p4;
};


#endif //INC_7_FIGURE_H

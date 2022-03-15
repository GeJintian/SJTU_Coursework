//
// Created by Surface on 2017/12/7.
//

#ifndef UNTITLED3_FIGURE_H
#define UNTITLED3_FIGURE_H
#include"parkinglot.h"


//color
class Color{
public:
    float r,g,b;
};

//vector
class Vec{
public:
    Vec(float _x=0.0,float _y=0.0);
    ~Vec();
    float getX();
    float getY();
    Vec operator+ (Vec v);
    Vec operator- (Vec v);
    Vec operator* (float k);
    Vec operator* (Vec v);
    Vec operator<< (float ang);
    Vec operator>> (float ang);
private:
    float x,y;
};

//figure
class Figure{
public:
    Figure(float a=0.0,float b=0.0);
    virtual ~Figure();
    Vec getAnchor();
    void setAnchor(float a,float b);
    virtual void Draw(){};
    virtual void Move(Vec dir){};
    virtual void Rotate(float ang,int c_){};
    virtual void Zoom(float k){};
protected:
    Vec anchor;
};

//colored shapes
class Shape : public Figure{
public:
    Shape(float red=0.0,float green=0.0,float blue=0.0,
          float a=0.0,float b=0.0);
    virtual ~Shape(){};
    virtual void Draw(){};
    virtual void Move(Vec v){};
    virtual void Rotate(float ang,int c_){};
    virtual void Zoom(float k){};
    void cColor();
protected:
    Color color;
};
//Triangle
class Triangle : public Shape{
public:
    Triangle();
    Triangle(Vec vec1,Vec vec2,Vec vec3,
             float red,float green,float blue,
             float a,float b);
    ~Triangle();
    void Draw();
    void Move(Vec v);
    void Rotate(float ang,int c_);
    void Zoom(float k);
private:
    Vec v1,v2,v3;
};
//Rectangle
class Rectang : public Shape{
public:
    Rectang();
    Rectang(Vec vec1,Vec vec2,
            float red,float green,float blue,
            float a,float b);
    ~Rectang();
    void Draw();
    void Move(Vec v);
    void Rotate(float ang,int c_);
    void Zoom(float k);
private:
    Vec v1,v2,v3,v4;
};
//Semicircle
class semiCircle : public Shape{
public:
    semiCircle();
    semiCircle(Vec vec1,Vec vec2,Vec vec3,Vec vec4,
               float red,float green,float blue,
               float a,float b);
    ~semiCircle();
    void Draw();
    void Move(Vec v);
    void Rotate(float ang,int c_);
    void Zoom(float k);
private:
    Vec v1,v2,v3,v4;
    float r;
};
//Polygon(4)
class Polyg : public Shape{
public:
    Polyg();
    Polyg(Vec vec1,Vec vec2,Vec vec3,Vec vec4,
          float red,float green,float blue,
          float a,float b);
    ~Polyg();
    void Draw();
    void Move(Vec v);
    void Rotate(float ang,int c_);
    void Zoom(float k);
private:
    Vec v1,v2,v3,v4;
};
//circle
class Circle : public Shape{
public:
    Circle();
    Circle(Vec vec1,float radius,
           float red,float green,float blue,
           float a,float b);
    ~Circle();
    void Draw();
    void Move(Vec v);
    void Rotate(float ang,int c_);
    void Zoom(float k);
private:
    Vec v;
    float r;
};
//Line
class Line : public Shape{
public:
    Line();
    Line(Vec vec1,Vec vec2,
         float red,float green,float blue,
         float a,float b);
    ~Line();
    void Draw();
    void Move(Vec v);
    void Rotate(float ang,int c_);
    void Zoom(float k);
private:
    Vec v1,v2;
};


//groups of objects
class Group : public Figure{
public:
    Group(float a=0.0,float b=0.0);
    virtual ~Group(){};
    virtual void Draw(){};
    virtual void Move(Vec dir){};
    virtual void Rotate(float ang,int c_){};
    virtual void Zoom(float k){};
    virtual void Action(){};
};
//UFO
class UFO : public Group{
public:
    UFO(float a=0.0,float b=0.0,float spin=0.0);
    ~UFO();
    void Draw();
    void Move(Vec dir);
    void Rotate(float ang,int c_);
    void Zoom(float k);
    void Action();
private:
    Shape* u[5];
};
//Car
class Car : public Group{
public:
    Car(float a=0.0,float b=0.0);
    ~Car();
    void Draw();
    void Move(Vec dir);
    void Rotate(float ang,int c_);
    void Zoom(float k);
    void Action();
private:
    Shape* c[4];
};
//Spacecraft
class Spacecraft : public Group{
public:
    Spacecraft(float a=0.0,float b=0.0,float rate=1.0);
    ~Spacecraft();
    void Draw();
    void Move(Vec dir);
    void Rotate(float ang,int c_);
    void Zoom(float k);
    void Action();
private:
    Shape* s[8];
};
//Teleport
class Teleport : public Group{
public:
    Teleport(float a=0.0,float b=0.0);
    ~Teleport();
    void Draw();
    void Move(Vec dir);
    void Rotate(float ang,int c_);
    void Zoom(float k);
    void Action();
private:
    Shape* t;
};

#endif //UNTITLED3_FIGURE_H

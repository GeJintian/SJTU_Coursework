//
// Created by 69009 on 2017/12/14.
//

#include "figures.h"
#include<GL/freeglut.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include"parkinglot.h"
static const float PI=3.1415926;
using namespace std;

//vector
Vec::Vec(float _x,float _y){
    x = _x;
    y = _y;
}

Vec::~Vec(){}

float Vec::getX(){
    return x;
}

float Vec::getY(){
    return y;
}

Vec Vec::operator+ (Vec v){
    Vec result(x + v.getX(),y + v.getY());
    return result;
}

Vec Vec::operator- (Vec v){
    Vec result(x - v.getX(),y - v.getY());
    return result;
}

Vec Vec::operator* (float k){
    Vec result(x * k,y * k);
    return result;
}

Vec Vec::operator* (Vec v){
    Vec result(x * v.getX(),y * v.getY());
    return result;
}

Vec Vec::operator<< (float ang){
    float x0,y0;
    x0 = x * cosf(ang/180*PI) - y * sinf(ang/180*PI);
    y0 = x * sinf(ang/180*PI) + y * cosf(ang/180*PI);
    Vec result(x0,y0);
    return result;
}

Vec Vec::operator>> (float ang){
    float x0,y0;
    x0 = x * cosf(ang/180*PI) + y * sinf(ang/180*PI);
    y0 = y * cosf(ang/180*PI) - x * sinf(ang/180*PI);
    Vec result(x0,y0);
    return result;
}

//figure
Figure::Figure(float a,float b) : anchor(a,b){}

Figure::~Figure(){}

Vec Figure::getAnchor(){
    return anchor;
}

void Figure::setAnchor(float a,float b){
    Vec v(a,b);
    anchor = v;
}

//Shapes
Shape::Shape(float red,float green,float blue,
             float a,float b) : Figure(a,b){
    color.r = red;
    color.g = green;
    color.b = blue;
}

void Shape::cColor(){
    srand(time(0));
    color.r = (float)rand()/RAND_MAX;
    color.g = (float)rand()/RAND_MAX;
    color.b = (float)rand()/RAND_MAX;
}

//Triangle
Triangle::Triangle() : Shape(0.0,0.0,0.0,0.0,0.0){
    Vec v(0.0,0.0);
    v1 = v;
    v2 = v;
    v3 = v;
}

Triangle::Triangle(Vec vec1,Vec vec2,Vec vec3,
                   float red,float green,float blue,
                   float a,float b) : Shape(red,green,blue,a,b){
    v1 = vec1;
    v2 = vec2;
    v3 = vec3;
}

Triangle::~Triangle(){}

void Triangle::Draw(){
    Vec temp = getAnchor();
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f((temp+v1).getX(),(temp+v1).getY());
    glVertex2f((temp+v2).getX(),(temp+v2).getY());
    glVertex2f((temp+v3).getX(),(temp+v3).getY());
    glEnd();
}

void Triangle::Move(Vec v){
    anchor = anchor + v;
}

void Triangle::Rotate(float ang,int c_){
    if(c_==1){
        v1 = v1 << ang;
        v2 = v2 << ang;
        v3 = v3 << ang;
    }
    else{
        v1 = v1 >> ang;
        v2 = v2 >> ang;
        v3 = v3 >> ang;
    }
}

void Triangle::Zoom(float k){
    v1 = v1 * k;
    v2 = v2 * k;
}

//rectangle
Rectang::Rectang() : Shape(0.0,0.0,0.0,0.0,0.0){
    Vec v(0.0,0.0);
    v1 = v;
    v2 = v;
    v3 = v;
    v4 = v;
}

Rectang::Rectang(Vec vec1,Vec vec2,
                 float red,float blue,float green,
                 float a,float b) : Shape(red,green,blue,a,b){
    v1 = vec1;
    v2 = vec2;
    Vec vec3(-(vec2.getX()),vec2.getY());
    Vec vec4(-(vec1.getX()),vec1.getY());
    v3 = vec3;
    v4 = vec4;
}

Rectang::~Rectang(){}

void Rectang::Draw(){
    Vec temp = getAnchor();
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_QUADS);
    glVertex2f((temp+v1).getX(),(temp+v1).getY());
    glVertex2f((temp+v2).getX(),(temp+v2).getY());
    glVertex2f((temp+v3).getX(),(temp+v3).getY());
    glVertex2f((temp+v4).getX(),(temp+v4).getY());
    glEnd();
}

void Rectang::Move(Vec v){
    anchor = anchor + v;
}

void Rectang::Rotate(float ang,int c_){
    if(c_==1){
        v1 = v1 << ang;
        v2 = v2 << ang;
        v3 = v3 << ang;
        v4 = v4 << ang;
    }
    else{
        v1 = v1 << ang;
        v2 = v2 << ang;
        v3 = v3 << ang;
        v4 = v4 << ang;
    }
}

void Rectang::Zoom(float k){
    v1 = v1 * k;
    v2 = v2 * k;
    v3 = v3 * k;
    v4 = v4 * k;
}

//semicircle
semiCircle::semiCircle() : Shape(0.0,0.0,0.0,0.0,0.0){
    Vec v(0.0,0.0);
    v1 = v;
    v2 = v;
    v3 = v;
    v4 = v;
    r  = 0.0;
}

semiCircle::semiCircle(Vec vec1,Vec vec2,Vec vec3,Vec vec4,
                       float red,float green,float blue,
                       float a,float b) : Shape(red,green,blue,a,b){
    v1 = vec1;
    v2 = vec2;
    v3 = vec3;
    v4 = vec4;
    r  = sqrtf(powf((v2.getX()-v4.getX()),2.0));
}

semiCircle::~semiCircle(){}

void semiCircle::Draw(){
    int i;
    Vec temp = getAnchor();
    Vec vy   = v3 - v1;
    Vec vx   = v2 - v1;
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_POLYGON);
    for(i=0;i<100;i++){
        float ang = (float)i/100*PI;
        glVertex2f(temp.getX()+vx.getX()*cosf(ang)+vy.getX()*sinf(ang),temp.getY()+vy.getY()*sinf(ang)+vx.getY()*cosf(ang));
    }
    glEnd();
}

void semiCircle::Move(Vec v){
    anchor = anchor + v;
}

void semiCircle::Rotate(float ang,int c_){
    if(c_==1){
        v1 = v1 << ang;
        v2 = v2 << ang;
        v3 = v3 << ang;
        v4 = v4 << ang;
    }
    else{
        v1 = v1 >> ang;
        v2 = v2 >> ang;
        v3 = v3 >> ang;
        v4 = v4 >> ang;
    }
}

void semiCircle::Zoom(float k){
    v1 = v1 * k;
    v2 = v2 * k;
    v3 = v3 * k;
    v4 = v4 * k;
    r  = r  * k;
}

//polygon
Polyg::Polyg() : Shape(0.0,0.0,0.0,0.0,0.0){
    Vec v(0.0,0.0);
    v1 = v;
    v2 = v;
    v3 = v;
    v4 = v;
}

Polyg::Polyg(Vec vec1,Vec vec2,Vec vec3,Vec vec4,
             float red,float green,float blue,
             float a,float b) : Shape(red,green,blue,a,b){
    v1 = vec1;
    v2 = vec2;
    v3 = vec3;
    v4 = vec4;
}

Polyg::~Polyg(){}

void Polyg::Draw(){
    Vec temp = getAnchor();
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_POLYGON);
    glVertex2f((temp+v1).getX(),(temp+v1).getY());
    glVertex2f((temp+v2).getX(),(temp+v2).getY());
    glVertex2f((temp+v3).getX(),(temp+v3).getY());
    glVertex2f((temp+v4).getX(),(temp+v4).getY());
    glEnd();
}

void Polyg::Move(Vec v){
    anchor = anchor + v;
}

void Polyg::Rotate(float ang,int c_){
    if(c_==1){
        v1 = v1 << ang;
        v2 = v2 << ang;
        v3 = v3 << ang;
        v4 = v4 << ang;
    }
    else{
        v1 = v1 >> ang;
        v2 = v2 >> ang;
        v3 = v3 >> ang;
        v4 = v4 >> ang;
    }
}

void Polyg::Zoom(float k){
    v1 = v1 * k;
    v2 = v2 * k;
    v3 = v3 * k;
    v4 = v4 * k;
}

//circle
Circle::Circle() : Shape(0.0,0.0,0.0,0.0,0.0){
    Vec tempv(0.0,0.0);
    v = tempv;
    r = 0.0;
}

Circle::Circle(Vec vec1,float radius,
               float red,float green,float blue,
               float a,float b) : Shape(red,green,blue,a,b){
    v = vec1;
    r = radius;
}

Circle::~Circle(){}

void Circle::Draw(){
    Vec temp = getAnchor();
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_POLYGON);
    int i;
    for(i=0;i<100;i++){
        glVertex2f(anchor.getX()+v.getX()-r*cos(2*PI/100*i),anchor.getY()+v.getY()+r*sin(2*PI/100*i));
    }
    glEnd();
}

void Circle::Move(Vec v){
    anchor = anchor + v;
}

void Circle::Rotate(float ang,int c_){
    if(c_==1){
        v = v << ang;
    }
    else{
        v = v >> ang;
    }
}

void Circle::Zoom(float k){
    r *= k;
    v  = v * k;
}

//line
Line::Line() : Shape(0.0,0.0,0.0,0.0,0.0){
    Vec v(0.0,0.0);
    v1 = v;
    v2 = v;
}

Line::Line(Vec vec1,Vec vec2,
           float red,float green,float blue,
           float a,float b) : Shape(red,green,blue,a,b){
    v1 = vec1;
    v2 = vec2;
}

Line::~Line(){}

void Line::Draw(){
    Vec temp = getAnchor();
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINES);
    glVertex2f((temp+v1).getX(),(temp+v1).getY());
    glVertex2f((temp+v2).getX(),(temp+v2).getY());
    glEnd();
}

void Line::Move(Vec v){
    anchor = anchor + v;
}

void Line::Rotate(float ang,int c_){
    if(c_==1){
        v1 = v1 << ang;
        v2 = v2 << ang;
    }
    else{
        v1 = v1 >> ang;
        v2 = v2 >> ang;
    }
}

void Line::Zoom(float k){
    v1 = v1 * k;
    v2 = v2 * k;
}

//groups
Group::Group(float a,float b) : Figure(a,b){}

//UFO
UFO::UFO(float a,float b,float spin) : Group(a,b){
    float ang = 180 * spin;
    Vec v1(-0.04,0.0);
    Vec v2(-0.045,-0.03);
    Vec v3(-0.005,-0.03);
    Vec v4(-0.01,0.0);
    u[0] = new Polyg(v1<<ang,v2<<ang,v3<<ang,v4<<ang,0.1,0.2,0.2,a,b);

    Vec v5(0.01,0.0);
    Vec v6(0.005,-0.03);
    Vec v7(0.045,-0.03);
    Vec v8(0.04,0.0);
    u[1] = new Polyg(v5<<ang,v6<<ang,v7<<ang,v8<<ang,0.1,0.2,0.2,a,b);

    Vec v9(0.0,0.0);
    Vec v10(-0.05,0.0);
    Vec v11(0.0,0.05);
    Vec v12(0.05,0.0);
    u[2] = new semiCircle(v9<<ang,v10<<ang,v11<<ang,v12<<ang,0.2,0.5,0.5,a,b);//used to be anchor for first parameter

    Vec v13(0.03,0.04);
    Vec v14(0.042,0.056);
    u[3] = new Line(v13<<ang,v14<<ang,0.0,0.0,0.0,a,b);

    Vec v15(-0.03,0.04);
    Vec v16(-0.042,0.056);
    u[4] = new Line(v15<<ang,v16<<ang,0.0,0.0,0.0,a,b);
}

UFO::~UFO(){
    int i;
    for(i=0;i<5;i++){
        delete u[i];
    }
}

void UFO::Draw(){
    int i;
    for(i=0;i<5;i++){
        u[i] -> Draw();
    }
}

void UFO::Move(Vec dir){
    int i;
    for(i=0;i<5;i++){
        u[i] -> Move(dir);
    }
}

void UFO::Rotate(float ang,int c_){
    int i;
    for(i=0;i<5;i++){
        u[i] -> Rotate(ang,c_);
    }
}

void UFO::Zoom(float k){
    int i;
    for(i=0;i<5;i++){
        u[i] -> Zoom(k);
    }
}

void UFO::Action(){}

//Car
Car::Car(float a,float b) : Group(a,b){
    Vec v1(-0.16,0.0);
    Vec v2(-0.16,-0.04);
    Vec v3(0.12,-0.04);
    Vec v4(0.1,0.0);
    c[0] = new Polyg(v1,v2,v3,v4,0.4,0.4,0.5,a,b);

    Vec v5(-0.12,0.05);
    Vec v6(-0.14,0.0);
    Vec v7(0.02,0.0);
    Vec v8(0.0,0.05);
    c[1] = new Polyg(v5,v6,v7,v8,0.6,0.3,0.3,a,b);

    Vec v9(-0.12,-0.04);
    c[2] = new Circle(v9,0.02,0.0,0.0,0.0,a,b);

    Vec v10(0.02,-0.04);
    c[3] = new Circle(v10,0.02,0.0,0.0,0.0,a,b);
}

Car::~Car(){}

void Car::Draw(){
    int i;
    for(i=0;i<4;i++){
        c[i] -> Draw();
    }
}

void Car::Move(Vec dir){
    int i;
    for(i=0;i<4;i++){
        c[i] -> Move(dir);
    }
}

void Car::Rotate(float ang,int c_){
    int i;
    for(i=0;i<4;i++){
        c[i] -> Rotate(ang,c_);
    }
}

void Car::Zoom(float k){
    int i;
    for(i=0;i<4;i++){
        c[i] -> Zoom(k);
    }
}

void Car::Action(){}

//Spacecraft
Spacecraft::Spacecraft(float a,float b,float rate) : Group(a,b){
    Vec v1(-0.025,0.035);
    Vec v2(-0.025,-0.035);
    s[0] = new Rectang(v1*rate,v2*rate,0.3,0.8,0.6,a,b);

    Vec v3(-0.045,-0.035);
    Vec v4(-0.025,0.0);
    s[1] = new Triangle(v3*rate,v2*rate,v4*rate,0.5,0.4,0.7,a,b);

    Vec v5(0.025,0.0);
    Vec v6(0.025,-0.035);
    Vec v7(0.045,-0.035);
    s[2] = new Triangle(v5*rate,v6*rate,v7*rate,0.5,0.4,0.7,a,b);

    Vec v8(0.0,0.085);
    Vec v9(-0.025,0.035);
    Vec v10(0.025,0.035);
    s[3] = new Triangle(v8*rate,v9*rate,v10*rate,0.5,0.4,0.3,a,b);

    Vec v11(-0.01,-0.035);
    Vec v12(-0.015,-0.05);
    Vec v13(0.015,-0.05);
    Vec v14(0.01,-0.035);
    s[4] = new Polyg(v11*rate,v12*rate,v13*rate,v14*rate,0.6,0.2,0.2,a,b);

    Vec v15(-0.005,0.015);
    Vec v16(-0.005,0.0);
    s[5] = new Rectang(v15*rate,v16*rate,0.4,0.2,0.2,a,b);

    Vec v17(-0.015,0.03);
    Vec v18(-0.015,0.02);
    s[6] = new Rectang(v17*rate,v18*rate,0.4,0.2,0.2,a,b);

    Vec v19(0.005,0.03);
    Vec v20(0.005,0.02);
    s[7] = new Rectang(v19*rate,v20*rate,0.4,0.2,0.2,a,b);
}

Spacecraft::~Spacecraft(){}

void Spacecraft::Draw(){
    int i;
    for(i=0;i<8;i++){
        s[i] -> Draw();
    }
}

void Spacecraft::Move(Vec dir){
    int i;
    for(i=0;i<8;i++){
        s[i] -> Move(dir);
    }
}

void Spacecraft::Rotate(float ang,int c_){
    int i;
    for(i=0;i<8;i++){
        s[i] -> Rotate(ang,c_);
    }
}

void Spacecraft::Zoom(float k){
    int i;
    for(i=0;i<8;i++){
        s[i] -> Zoom(k);
    }
}

void Spacecraft::Action(){}

//Teleport
Teleport::Teleport(float a,float b) : Group(a,b){
    srand(time(0));
    Vec v1(-0.075,0.1);
    Vec v2(-0.075,-0.1);
    int red,green,blue;
    red   = (float)rand()/RAND_MAX;
    green = (float)rand()/RAND_MAX;
    blue  = (float)rand()/RAND_MAX;
    t = new Rectang(v1,v2,red,green,blue,a,b);
}

Teleport::~Teleport(){
    delete t;
}

void Teleport::Draw(){
    t->Draw();
}

void Teleport::Move(Vec dir){
    t->Move(dir);
}

void Teleport::Rotate(float ang,int c_){
    t->Rotate(ang,c_);
}

void Teleport::Zoom(float k){
    t->Zoom(k);
}

void Teleport::Action(){
    t->cColor();
}//
// Created by Surface on 2017/12/7.
//


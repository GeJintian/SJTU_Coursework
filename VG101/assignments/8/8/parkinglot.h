//
// Created by 69009 on 2017/12/14.
//

#ifndef INC_8_PARKINGLOT_H
#define INC_8_PARKINGLOT_H


#include"figures.h"

class Vec;
class Group;
class Car;
class Line;

class Slot{
public:
    Slot(float a=0.0,float b=0.0,int ind=0);
    ~Slot();
    void Park();
    int tellState();
    Vec* getAddr();
private:
    int state;
    Vec* addr;
    int index;
};

class Parkinglot{
public:
    Parkinglot(int* arr,int u_=1,int s_=1,int t_=1,float rate=1.0,float angle=0.0,float a=0.0,float b=0.0,float c=0.0,float d=0.0);
    ~Parkinglot();
    void Act(float* spin,float* zoom,float* x,float* y,float* c,int sl);
    void Drawlot();
    int findSlot();
private:
    Slot* s[10];
    Group* v[10];
    Car* car;
    Line* line;
    int u,s1,t;
};


#endif //INC_8_PARKINGLOT_H

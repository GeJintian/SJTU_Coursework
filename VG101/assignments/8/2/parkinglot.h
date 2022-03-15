//
// Created by Surface on 2017/12/7.
//

#ifndef UNTITLED3_PARKINGLOT_H
#define UNTITLED3_PARKINGLOT_H
#include"figure.h"

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

#endif //UNTITLED3_PARKINGLOT_H

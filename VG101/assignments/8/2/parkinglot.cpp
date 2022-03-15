#include<GL/freeglut.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include"figure.h"
#include"parkinglot.h"
using namespace std;
static const float PI=3.1415926;
//slot
Slot::Slot(float a,float b,int ind){
    index = ind;
    state = 0;
    addr  = new Vec(a,b);
}

Slot::~Slot(){
    delete addr;
}

void Slot::Park(){
    if(state==1){
        cout << "No place available\n";
    }
    else{
        state = 1;
    }
}

int Slot::tellState(){
    return state;
}

Vec* Slot::getAddr(){
    return addr;
}

//parking lot
Parkinglot::Parkinglot(int* arr,int u_,int s_,int t_,float rate,float angle,float a,float b,float c,float d) {
    u = u_;
    s1 = s_;
    t = t_;
    float x = -0.55;
    float y = -0.35;
    int i;
    //slots
    for (i = 0; i < 5; i++) {
        s[i] = new Slot(x, y, i);
        x += 0.3;
    }
    x = 0.65;
    y = 0.85;
    for (i = 5; i < 10; i++) {
        s[i] = new Slot(x, y, i);
        x -= 0.3;
    }
    for(i=0;i<u;i++){
        v[i] = new UFO(s[*(arr+i)]->getAddr()->getX(), s[*(arr+i)]->getAddr()->getY(), angle);
        s[i]->Park();
    }
    for(i=u;i<s1+u;i++){
        v[i] = new Spacecraft(s[*(arr+i)]->getAddr()->getX(), s[*(arr+i)]->getAddr()->getY(), rate);
        s[i]->Park();
    }
    for(i=s1+u;i<s1+u+t;i++){
        v[i] = new Teleport(s[*(arr+i)]->getAddr()->getX(), s[*(arr+i)]->getAddr()->getY());
        s[i]->Park();
    }
    car = new Car(a, b);
    line= new Line({-1.0,-0.5},{-0.7,-0.5},0.0,0.0,0.0,c,d);
    u = u_;
    s1 = s_;
    t = t_;
}

Parkinglot::~Parkinglot(){
    int i;
    for(i=0;i<10;i++){
        delete s[i];
    }
    for(i=0;i<(u+s1+t);i++){
        delete v[i];
    }
    delete car;
    delete line;
}

void Parkinglot::Act(float* spin,float* zoom,float* x,float* y,float* c,int sl){
    int i;
    float m = *spin;
    float n = *zoom;
    //UFO rotate
    int static b = 0;
    if(m>=0.5 && b==0){
        m *= 0.99;
    }
    else if(n<=2){
        b  = 1;
        m *= 1.009;
    }
    else b=0;
    //spacecraft zoom in and out
    int static e = 0;
    if(n>=0.5 && e==0){
        n *= 0.99;
    }
    else if(n<=2){
        e  = 1;
        n *= 1.009;
    }
    else e=0;
    //change values
    *spin = m;
    *zoom = n;
    //teleport change color
    for(i=0;i<u+s1+t;i++){
        v[i]->Action();
    }
    //car move
    static int   step = 0;
    static float turn = 2.0;
    float tempx=*x;
    float tempy=*y;
    float tempz=*c;
    float adx   = s[sl]->getAddr()->getX();
    //when car in parking in the lower part
    if(sl<=4 && sl>=1){
        if(step==0){
            car->Rotate(turn,1);
            tempx=tempx+0.1*sinf(turn/180*PI)-0.1*sinf((turn-2)/180*PI);
            tempy=tempy+0.1*(1-cosf(turn/180*PI))-0.1*(1-cosf((turn-2)/180*PI));
            turn += 2.0;
            tempz-=0.005;
            if(turn>=90.0){
                step++;
            }
        }
        else if(step==1 && tempy<=0.1){
            car->Rotate(90.0,1);
            tempy += 0.01;
            if(tempy>=-0.1) step++;
        }
        else if(step==2){
            car->Rotate(turn,1);
            tempy=tempy+0.2*cosf((turn-2)/180*PI)-0.2*cosf(turn/180*PI);
            tempx=tempx+0.2*(1-sinf((turn-2)/180*PI))-0.2*(1-sinf(turn/180*PI));
            turn -= 2.0;
            tempz+=0.005;
            if(turn<=0.0){
                step++;
            }
        }
        else if(step==3 && tempx<=(adx+0.3)){
            tempx += 0.01;
            if(tempx>=adx+0.3) step++;
        }
        else if(step==4) {
            car->Rotate(turn, 1);
            tempy = tempy - 0.3 * cosf(turn / 180 * PI) + 0.3 * cosf((turn + 2) / 180 * PI);
            tempx = tempx - 0.3 * (1 - sinf(turn / 180 * PI)) + 0.3 * (1 - sinf((turn + 2) / 180 * PI));
            if (turn >= 90.0) {
                turn = 90.0;
                step++;
            } else turn += 2.0;
        }
        else if(step==5){
            tempy-=0.01;
            car->Rotate(90.0,1);
            if(tempy<=-0.3) step++;
        }
        else if(step==6){
            car->Rotate(90.0,1);
        }
    }
        //when car is parking in the upper part
    else if(sl>4){
        if(step==0){
            tempz-=0.005;
            car->Rotate(turn,1);
            tempx=tempx+0.1*sinf(turn/180*PI)-0.1*sinf((turn-2)/180*PI);
            tempy=tempy+0.1*(1-cosf(turn/180*PI))-0.1*(1-cosf((turn-2)/180*PI));
            turn += 2.0;
            if(turn>=90.0){
                step++;
            }
        }
        else if(step==1 && tempy<=0.1){
            car->Rotate(90.0,1);
            tempy += 0.01;
            if(tempy>=-0.1) step++;
        }
        else if(step==2){
            car->Rotate(turn,1);
            tempy=tempy+0.2*cosf((turn-2)/180*PI)-0.2*cosf(turn/180*PI);
            tempx=tempx+0.2*(1-sinf((turn-2)/180*PI))-0.2*(1-sinf(turn/180*PI));
            turn -= 2.0;
            tempz+=0.005;
            if(turn<=2.0){
                step++;
            }
        }
        else if(step==3 && tempx<=0.8){
            tempx += 0.01;
            if(tempx>=0.6) step++;
        }
        else if(step==4){
            car->Rotate(turn,1);
            tempx=tempx+0.2*sinf(turn/180*PI)-0.2*sinf((turn-2)/180*PI);
            tempy=tempy+0.2*(1-cosf(turn/180*PI))-0.2*(1-cosf((turn-2)/180*PI));
            turn += 2.0;
            if(turn>=90.0){
                step++;
                turn = 90.0;
            }
        }
        else if(step==5 && tempy<=0.55){
            car->Rotate(90.0,1);
            tempy += 0.01;
            if(tempy>=0.35) step++;
        }
        else if(step==6){
            car->Rotate(turn,1);
            tempx=tempx+0.2*sinf(turn/180*PI)-0.2*sinf((turn-2)/180*PI);
            tempy=tempy+0.2*(1-cosf(turn/180*PI))-0.2*(1-cosf((turn-2)/180*PI));
            turn += 2.0;
            if(turn>=180.0){
                step++;
                turn = 180.0;
            }
        }
        else if(step==7 && tempx>=(adx-0.25)){
            car->Rotate(180.0,1);
            tempx -= 0.01;
            if(tempx<=adx-0.25) step++;
        }
        else if(step==8){
            car->Rotate(turn,0);
            tempx=tempx+0.25*sinf((turn-2)/180*PI)-0.25*sinf(turn/180*PI);
            tempy=tempy+0.25*(1+cosf((turn-2)/180*PI))-0.25*(1+cosf(turn/180*PI));
            turn -= 2.0;
            if(turn<=90.0){
                step++;
            }
        }
        else if(step==9) car->Rotate(90.0,0);
    }
    *x = tempx;
    *y = tempy;
    *c=tempz;
}

void Parkinglot::Drawlot(){
    //lines
    float x = -0.7;
    int i;
    glColor3f(0.0,0.0,0.0);
    //vertical
    for(i=0;i<6;i++){
        //lower lines
        glBegin(GL_LINES);
        glVertex2f(x,-0.5);
        glVertex2f(x,-0.2);
        glEnd();
        //upper lines
        glBegin(GL_LINES);
        glVertex2f(x,0.7);
        glVertex2f(x,1.0);
        glEnd();
        //loop
        x += 0.3;
    }
    //horizontal
    glBegin(GL_LINES);
    glVertex2f(-0.7,-0.5);
    glVertex2f(1.0,-0.5);
    glEnd();
    //barrier
    glColor3f(0.5,0.8,0.8);
    glBegin(GL_QUADS);
    glVertex2f(-0.6,0.35);
    glVertex2f(-0.6,0.25);
    glVertex2f(0.6,0.25);
    glVertex2f(0.6,0.35);
    glEnd();
    //draw the vehicles
    for(i=0;i<u+s1+t;i++){
        v[i]->Draw();
    }
    //draw the car
    car->Draw();
    line->Draw();
}

int Parkinglot::findSlot(){
    int i;
    for(i=0;i<10;i++){
        if(s[i]->tellState()==0) break;
    }
    return i;
}//
// Created by Surface on 2017/12/7.
//


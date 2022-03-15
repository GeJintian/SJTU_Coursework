//
// Created by 69009 on 2020/11/18.
//

#include "Triangluation.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Map.h"
using namespace std;

Circle get_circle(Map_t * Map, int classification, double angle, double dis, GodState_t &CurrentState){
    Circle cir;
    double position[2] = {0};
    //Map->get_position(position, classification, angle, dis, CurrentState);
    if(classification == 4){
        position[0] = -2;
        position[1] = 1;
    }//YELLOW
    else if(classification == 1){
        position[0] = -2;
        position[1] = -1;
    }//GREEN
    else if(classification == 0){
        position[0] = -4;
        position[1] = -1;
    }//BLUE
    else{
        position[0] = -4;
        position[1] = 1;
    }//RED
    cir.x = position[0];
    cir.y = position[1];
    cir.r = dis;
    cir.angle = angle;
    return cir;
}

void process_circle(Map_t * Map, Circle * cir_list, double * LandMarks, int NumLandMark, GodState_t &CurrentState) {
    for (int i = 0; i < NumLandMark; i++) {
        cir_list[i] = get_circle(Map, (int)LandMarks[3*i+2], LandMarks[3*i],LandMarks[3*i+1], CurrentState);
        //cout<<"Circle"<<i<<": ("<<cir_list[i].x<<" , "<<cir_list[i].y<<"), "<<cir_list[i].r<<endl;
    }
}

void get_position2(Map_t * Map, double * position, double x, double y, Circle * cir_list, int NumLandMark){
    Circle c1 = cir_list[0];
    Circle c2 = cir_list[1];
    if(c1.x==c2.x && c1.y == c2.y) return;

    double dist_cir2cir = sqrt((c1.x-c2.x)*(c1.x-c2.x)+(c1.y-c2.y)*(c1.y-c2.y));
    double dist2 = (c1.r*c1.r-c2.r*c2.r+dist_cir2cir*dist_cir2cir)/(2*dist_cir2cir);

    double E_x = c1.x + (dist2*(c2.x-c1.x))/dist_cir2cir;
    double E_y = c1.y + (dist2*(c2.y-c1.y))/dist_cir2cir;
    double k;
    if(c1.y == c2.y){
        k = 100000;
    }
    else{
        k = -((c1.x-c2.x)/(c1.y-c2.y));
    }
    double CE = c1.r*c1.r - dist2*dist2;
    double C_x = E_x -sqrt(CE/(1+k*k));
    double C_y = E_y +k*(C_x-E_x);
    //double k1 = (C_y-c1.y)/(C_x-c1.x);
    //double k2 = (C_y-c2.y)/(C_x-c2.x);
    double D_x = E_x + sqrt(CE/(1+k*k));
    double D_y = E_y+k*(D_x-E_x);
    //cout<<"("<<C_x<<" , "<<C_y<<")"<<endl;
    //cout<<"("<<D_x<<" , "<<D_y<<")"<<endl;

    double error1 = sqrt((C_x-x)*(C_x-x)+(C_y-y)*(C_y-y));
    double error2 = sqrt((D_x-x)*(D_x-x)+(D_y-y)*(D_y-y));

    double final_x, final_y;
    if(error1 > error2){
        final_x = D_x;
        final_y = D_y;
    }
    else{
        final_x = C_x;
        final_y = C_y;
    }
    cout<<"Final result is ("<<final_x<<", "<<final_y<<")    ";
    position[0] = final_x;
    position[1] = final_y;


    double theta;
    double vector_x = c1.x-final_x;
    double vector_y = c1.y - final_y;
    theta = acos(vector_x/sqrt(vector_x*vector_x+vector_y*vector_y));
    theta = theta*180/M_PI;
    if(vector_y<0) theta = 360-theta;
    if(c1.angle > 180) c1.angle = c1.angle - 360;
    theta = theta + c1.angle;
    //cout<<"angle is "<<theta<<endl;
    position[2] = theta;

    /*
    //Compute function of line
    double c = c1.x;
    double d = c1.y;
    double r = c1.r;
    double k = (c1.x-c2.x)/(c2.y-c1.y);
    double b = ((c2.y*c2.y-c1.y*c1.y)-(c1.x*c1.x-c2.x*c2.x))/(2*(c2.y-c1.y));

    double delta = (k*k+1)*r*r-c*c*k*k-2*c*k*(b-d)-b*b+2*b*d-d*d;
    double x1 = -(sqrt(delta)+(b-d)*k-c)/(k*k+1);
    double x2 = (sqrt(delta)+(d-b)*k+c)/(k*k+1);
    double y1 = k*x1+b;
    double y2 = k*x2+b;

    cout<<"("<<x1<<" , "<<y1<<")"<<endl;
    cout<<"("<<x2<<" , "<<y2<<")"<<endl;
     */
}

void get_position3(Map_t * Map, double * position, Circle * cir_list, int NumLandMark){
    Circle c1 = cir_list[0];
    Circle c2 = cir_list[1];
    Circle c3 = cir_list[2];
    if(c1.x==c2.x && c1.y == c2.y) return;
    //cout<<"Cirlce 1 is ("<<c1.x<<", "<<c1.y<<") with distance "<<c1.r<<endl;
    //cout<<"Cirlce 2 is ("<<c2.x<<", "<<c2.y<<") with distance "<<c2.r<<endl;
    double dist_cir2cir = sqrt((c1.x-c2.x)*(c1.x-c2.x)+(c1.y-c2.y)*(c1.y-c2.y));
    double dist2 = (c1.r*c1.r-c2.r*c2.r+dist_cir2cir*dist_cir2cir)/(2*dist_cir2cir);

    double E_x = c1.x + (dist2*(c2.x-c1.x))/dist_cir2cir;
    double E_y = c1.y + (dist2*(c2.y-c1.y))/dist_cir2cir;
    double k;
    if(c1.y == c2.y){
        k = 100000;
    }
    else{
        k = -((c1.x-c2.x)/(c1.y-c2.y));
    }
    double CE = c1.r*c1.r - dist2*dist2;
    double C_x = E_x -sqrt(CE/(1+k*k));
    double C_y = E_y +k*(C_x-E_x);
    //double k1 = (C_y-c1.y)/(C_x-c1.x);
    //double k2 = (C_y-c2.y)/(C_x-c2.x);
    double D_x = E_x + sqrt(CE/(1+k*k));
    double D_y = E_y+k*(D_x-E_x);
    //cout<<"("<<C_x<<" , "<<C_y<<")"<<endl;
    //cout<<"("<<D_x<<" , "<<D_y<<")"<<endl;
    double error1 = abs(sqrt((C_x-c3.x)*(C_x-c3.x)+(C_y-c3.y)*(C_y-c3.y))-c3.r);
    double error2 = abs(sqrt((D_x-c3.x)*(D_x-c3.x)+(D_y-c3.y)*(D_y-c3.y))-c3.r);

    double final_x, final_y;
    if(error1 > error2){
        final_x = D_x;
        final_y = D_y;
    }
    else{
        final_x = C_x;
        final_y = C_y;
    }
    //cout<<"Final result is ("<<final_x<<", "<<final_y<<")    ";
    position[0] = final_x;
    position[1] = final_y;
    double theta;
    double vector_x = c1.x-final_x;
    double vector_y = c1.y - final_y;
    theta = acos(vector_x/sqrt(vector_x*vector_x+vector_y*vector_y));
    theta = theta*180/M_PI;
    if(vector_y<0) theta = 360-theta;
    if(c1.angle > 180) c1.angle = c1.angle - 360;
    theta = theta + c1.angle;
    //cout<<"angle is "<<theta<<endl;
    position[2] = theta;


    /*
    double c = c1.x;
    double d = c1.y;
    double r = c1.r;
    double k = (c1.x-c2.x)/(c2.y-c1.y);
    double b = ((c2.y*c2.y-c1.y*c1.y)-(c1.x*c1.x-c2.x*c2.x))/(2*(c2.y-c1.y));

    double delta = (k*k+1)*r*r-c*c*k*k-2*c*k*(b-d)-b*b+2*b*d-d*d;
    double x1 = -(sqrt(delta)+(b-d)*k-c)/(k*k+1);
    double x2 = (sqrt(delta)+(d-b)*k+c)/(k*k+1);
    double y1 = k*x1+b;
    double y2 = k*x2+b;

    cout<<"("<<x1<<" , "<<y1<<")"<<endl;
    cout<<"("<<x2<<" , "<<y2<<")"<<endl;

    double error1 = abs(sqrt((x1-c3.x)*(x1-c3.x)-(y1-c3.y)*(y1-c3.y))-c3.r);
    double error2 = abs(sqrt((x2-c3.x)*(x2-c3.x)-(y2-c3.y)*(y2-c3.y))-c3.r);

    double final_x, final_y;
    if(error1 > error2){
        final_x = x2;
        final_y = y2;
    }
    else{
        final_x = x1;
        final_y = y1;
    }
    cout<<"Final result is ("<<final_x<<" , "<<final_y<<")"<<endl;
     */
}

void StaticFusion(double * position, double * LandMark, int LandMarkNum, Map_t *Map, int MapNum, GodState_t &CurrentState){
    Circle cir_list[LandMarkNum];
    double x = CurrentState.Y;
    double y = CurrentState.X;
    process_circle(Map, cir_list, LandMark, LandMarkNum, CurrentState);
    if(LandMarkNum < 2) return;
    else if(LandMarkNum == 2) get_position2(Map, position, x, y, cir_list,LandMarkNum);
    else get_position3(Map, position, cir_list,LandMarkNum);
}
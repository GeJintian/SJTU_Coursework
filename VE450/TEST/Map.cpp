//
// Created by 69009 on 2020/11/18.
//

#include "Map.h"
#include "main.h"
#include <iostream>
#include <cmath>
using namespace std;
void Map_t::get_position(double * position, double type, double angle, double dis, GodState_t &GodState){
    double agv_x = GodState.X;
    double agv_y = GodState.Y;
    double agv_ang = GodState.Xai;
    double agv_dis = sqrt(agv_x*agv_x+agv_y*agv_y);
    int sign = 0;
    if(angle < 180) sign = -1;
    else sign = 1;
    double * which_color;
    switch ((int)type){
        case 0:
            which_color = BLUE;
            break;
        case 1:
            which_color = GREEN;
            break;
        case 2:
            which_color = RED;
            break;
        case 4:
            which_color = YELLOW;
            break;
        default:
            which_color = GREEN;//Should not occur;
            cout<<"ERROR!"<<endl;
            break;
    }
    double compare= 10000;
    int index = 0;
    for(int i = 0; i < 4; i++){//Filter
        double land_x = which_color[4*i];
        double land_y = which_color[4*i+1];
        double land_dis = which_color[4*i+2];
        double land_ang = which_color[4*i+3];
        double error = 0;
        if(agv_dis + dis <= land_dis){
            error = abs(agv_ang - land_ang);
            if(error < compare){
                compare = error;
                index = i;
            }
            continue;
        }
        double theta = acos((land_dis*land_dis + agv_dis*agv_dis - dis*dis)/(2*land_dis*agv_dis))*180/M_PI;
        error = abs(agv_ang + sign*theta - land_ang);
        if(error < compare){
            compare = error;
            index = i;
        }
    }
    position[0] = which_color[4*index];
    position[1] = which_color[4*index+1];
}
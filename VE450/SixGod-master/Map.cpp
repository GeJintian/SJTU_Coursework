//
// Created by 69009 on 2020/11/16.
//

#include "Map.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
static fstream* MMopen(){
    auto fst0=new fstream ;
    fst0->open("./Thread0Log.txt",ios::app);
    *fst0<<"SBSB"<<endl<<endl;
    return fst0;
}
void Map_t::get_position(double * position, double type, double angle, double dis, GodState_t &GodState){
    static fstream * fst0=MMopen();
    double agv_x = GodState.X;
    double agv_y = GodState.Y;
    double agv_ang = GodState.Xai;
    double agv_dis = sqrt(agv_x*agv_x+agv_y*agv_y);
    int sign = 0;
    if(angle < 180) sign = 1;
    else sign = -1;
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
            which_color = nullptr;//Should not occur;
         //   cout<<"Un-identified Obstacle, Trying to fit in the map"<<endl;
            break;
    }

    double compare = 1;//最大允许误差阈值
    int index = -1;
    double land_x;
    double land_y;
    double ob_x ;
    double ob_y ;
    int better_color;
    ob_x = GodState.X + dis * cos((GodState.Xai - angle) / 180 * M_PI);
    ob_y = GodState.Y + dis * sin((GodState.Xai - angle) / 180 * M_PI);
    if (which_color!= nullptr) {
        for (int i = 0; i < 4; i++) {//Filter
            land_x = which_color[4 * i];
            land_y = which_color[4 * i + 1];
            // cout<<ob_x<<" "<<ob_y;
            double error = (ob_x - land_x) * (ob_x - land_x) + (ob_y - land_y) * (ob_y - land_y);
            if (error < compare) {
                compare = error;
                index = i;
            }
        }
        if (index == -1){
            //cout<<"!!! Identified LM can not fit in the Map! Landmark: "<<ob_x<<" "<<ob_y<<" "<<type<<endl;
            throw (int) -1;//
        }
        //cout<<"IDD Successfully fit in the Map:"<<dis<<" "<<angle<<" "<<ob_x<<" "<<ob_y<<" Clasify: "<<type<<"With "<<which_color[4*index]<<" "<<which_color[4*index+1]<<" E "<<compare<<endl;

    }else{
        compare=0.5; //TODO:Decide Compare
        for (int j=0;j<4;j++) {
            which_color= LANDMARKGROUP[j];
            for (int i = 0; i < 4; i++) {//Filter
                land_x = which_color[4 * i];
                land_y = which_color[4 * i + 1];
                // cout<<ob_x<<" "<<ob_y;
                double error = (ob_x - land_x) * (ob_x - land_x) + (ob_y - land_y) * (ob_y - land_y);
                if (error < compare) {
                    compare = error;
                    index = i;
                    better_color=j;
                }
            }
        }
        if (index == -1){

          // cout<<"Can not fit in the Map! Landmark: "<<dis<<"\t"<<angle<<"\t"<<ob_x<<"\t"<<ob_y<<endl;
            throw (int) -1;//
        }
        which_color=LANDMARKGROUP[better_color];
#ifdef THREAD0OUT
        cout<<"t|LM_OB_X|Y|LM_MAP_X|Y:"<<GodState.t<<ob_x<<" "<<ob_y<<" "<<which_color[4*index]<<" "<<which_color[4*index+1]<<compare<<"RAW_R|degree:"<<dis<<" "<<angle<<endl;
        *fst0<<GodState.t<<" "<<ob_x<<" "<<ob_y<<" "<<which_color[4*index]<<" "<<which_color[4*index+1]<<" "<<compare<<" "<<dis<<" "<<angle<<endl;

#endif
    }
    position[0] = which_color[4*index];
    position[1] = which_color[4*index+1];
}
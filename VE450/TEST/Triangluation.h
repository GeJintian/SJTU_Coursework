//
// Created by 69009 on 2020/11/18.
//

#ifndef TEST_TRIANGLUATION_H
#define TEST_TRIANGLUATION_H
#include "main.h"
#include "Map.h"
struct Circle{
    double x=0;//x coordinate of circle
    double y=0;//y coordinate of circle
    double r=0;//distance from AGV
    double angle = 0;//angle between agv and circle
};

Circle get_circle(int classification, double x, double y, double r);
//In this function, we will use information to return a point in the map

void process_circle(Circle * cir_list, double * LandMarks, int NumLandMark, double former_x, double former_y);
//In this function, we will read information from LandMarks and find corresponding points in map.

void get_position2(double * position, double x, double y, Circle * cir_list, int NumLandMark);
//If only two landmarks, call this function

void get_position3(double * position, Circle * cir_list, int NumLandMark);
//If at least three landmarks, call this function
void StaticFusion(double * position, double * LandMark, int LandMarkNum, Map_t *Map, int MapNum, GodState_t &CurrentState);
//LandMark should contains
#endif //TEST_TRIANGLUATION_H

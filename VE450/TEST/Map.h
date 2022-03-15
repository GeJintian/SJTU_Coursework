//
// Created by 69009 on 2020/11/18.
//

#ifndef TEST_MAP_H
#define TEST_MAP_H
#include "main.h"
class Map_t{
private:
    double RED[16] = {4,1,4.1231,14.036,-4,1,4.1231,165.964,-3,-3,4.24264,225,3,-3,4.24264,315};//Four points, two coordinates, one dis and one angle for one point. x first, y next, dis third, angle last.
    double BLUE[16] = {0,2,2,90,-4,-1,4.1231,194.036,0,-4,4,270,4,-1,4.1231,345.964};//(0,2),(-4,-1),(0,-4),(4,-1)
    double YELLOW[16] = {2,1,2.236,26.565,0,4,4,90,-2,1,2.236,153.435,0,-2,2,270};//(2,1),(0,4),(-2,1),(0,-2)
    double GREEN[16] = {3,3,4.24264,45,-3,3,4.24264,135,-2,-1,2.236,206.565,2,-1,2.236,333.435};//(3,3),(-3,3),(-2,-1),(2,-1)
public:
    void get_position(double * position, double type, double angle, double dis, GodState_t &GodState);
    //Input: type of obstacle, angle information, distance information, last state, a two dimension container
    //Output: coordinate of obstacle in position
};
#endif //TEST_MAP_H

#include <iostream>
#include "Triangluation.h"
#include "main.h"
#include "Map.h"
using namespace std;
int main() {
    GodState_t CurrentState;
    CurrentState.X = -3;
    CurrentState.Y = -3;
    CurrentState.Xai = 110;
    double position[3]={0};
    double LandMark[12] = {18.045,4.019, 4, 29.1083,2.13533,1,335.764,2.256,0,349.03,4.045,2};
    int LandMarkNum = 4;
    Map_t map;
    StaticFusion(position, LandMark, LandMarkNum, &map, 0, CurrentState);
    return 0;
}
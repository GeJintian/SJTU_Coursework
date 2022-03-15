#include <iostream>
// 必须的头文件
#include <pthread.h>

#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "main.h"
#include "Triangulation.h"
#include "fstream"

//#include<windows.h>

#include <ctime>
using namespace std;

#include <unistd.h>
#define NUM_THREADS 1


int main()
{
    /*
    GodState_t CurrentState;
    CurrentState.X=0;
    CurrentState.Y=-3;
    CurrentState.Xai=0;
    Map_t mMap;
    double LandMark[24]={6.477,68.09,-1,29.1083,2.13533,1,336.764,2.256,0,349.03,4.045,2};
    int LandMarkNum=1;
    double mposition[2]={0,0};
    mMap.get_position(mposition,-1,270,1,CurrentState);
    Circle cir_list[4];
    cout<<mposition[0]<<" "<<mposition[1];
     */
    fstream Log0;

    Log0.open("./tmp.txt",ios_base::in|ios::out|ios::ate);
    if(Log0.is_open()) {
        Log0 << "Test" << endl;
        Log0 << "Test" << endl;
        cout<<"Test";
    }
    Log0.close();
}
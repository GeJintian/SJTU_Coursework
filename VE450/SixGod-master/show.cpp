#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include<windows.h>
#include <ctime>
#include <cmath>
#include "spi.h"
#include <sys/time.h>
using namespace std;

#define NUM_THREADS 1

#define PointPerCycle 400 //每周期点云点数量
static const char* device="/dev/spidev0.1";
class GodState_t{
public:
    int t;
    double X;
    double Y;
    double Xai;
};
class HistoryLinkedList_t{
public:
    HistoryLinkedList_t* next;
    int t;
    int v_PWM;
    int delta_PWM;
    double ax;
    double ay;
    double omegaz;

};
GodState_t GodState;
double ControlTra[20*2]={0};
HistoryLinkedList_t* History;
HistoryLinkedList_t* Last;
void* thread0(void* arg);
void* thread1(void* arg);
//以下 异常返回0，否则其他
int ReadMap(double* Map){};
int GetLidar(double* LidarCloud){};
int GetPicture(void* RawPicture){};
int LandMarkFusion(double* LidarCloud,void* RawPicture, double* LandMark){};//返回值是LandMark数量
int LMIdentify(double* LandMark,int LandMarkNum){};//返回值是LandMark数量
int StaticFusion(double* LandMark,int LandMarkNum, double* Map,int MapNum,GodState_t& CurrentState){};
int KalmanFilter(HistoryLinkedList_t &Data,GodState_t& GodState);
int GodSleep();
int SPIupdate(HistoryLinkedList_t &History, int fd);
int Control(GodState_t &mGodState, HistoryLinkedList_t &mHistoryLinkedList);

int main(){
    History=new HistoryLinkedList_t;
    History->next=new HistoryLinkedList_t;
    History->t=0;
    Last=History;
    thread1(nullptr);
    return 0;
}
void* thread0(void* arg)
{
    //Initialize
    //qxy
    double LidarCloud[PointPerCycle*2]={0};//Theta0,R0,Theta1,R1,....
    double LandMark[PointPerCycle*3]={0};//Theta0,R0,N0,Theta1,R1,N1,....
    double Map[PointPerCycle*3]={0};
    int LandMarkNum,MapNum;
    int RawPicture[1];//TODO:图片结构，尚未定义
    GodState_t CurrentState={0};
    MapNum=ReadMap(Map);
    //Loop
    //gjt
    while(true){
        if(!GetLidar(LidarCloud))//此函数不断运行直至采集到一组lidar数据（~100ms)
            break;//防止死循环报错
        CurrentState=GodState;
        GetPicture((void*) RawPicture);
        LandMarkNum=LandMarkFusion(LidarCloud,RawPicture,LandMark);
        LMIdentify(LandMark,LandMarkNum);//返回值是LandMark数量
        StaticFusion(LandMark,LandMarkNum,Map,MapNum,CurrentState);
        while(GodState.t!=CurrentState.t){
            KalmanFilter(*History,CurrentState);
            HistoryLinkedList_t* temp=History;
            History->next=History;
            delete temp;
        }
        GodState=CurrentState;
    }
    return nullptr;
}

void* thread1(void* arg)
{
    //initialize
    int fd;
    fd=spi_initialize(device);

    //Loop
    while(true){
        Last=Last->next;
        Last->next=new HistoryLinkedList_t;
        SPIupdate(*Last, fd);
        KalmanFilter(*Last,GodState);
        Control(GodState,*Last->next);
        if(!GodSleep())break;//等待直到下一个10ms开始
    }
    //Finish
    return nullptr;
}
int KalmanFilter(HistoryLinkedList_t &Data,GodState_t& GodState){
    GodState.t++;
    //constant:
    double lf=1;
    double lr=1;        //%IMU距离前后轮的距离f-前轮，r-后轮 unit:m, 待测定
    double Kd=1;
    double Kv=1 ;           //%待测定
    double deltaf=Kd*Data.delta_PWM;  //%前轮角
    double Vr=Kv*Data.v_PWM;          //%后轮速度
    double dt=0.01;//%unit: ms

    double beta=atan(lr*tan(deltaf)/(lf+lr));
    double V=Vr/(cos(beta));
    double Vf=Vr/(cos(deltaf));

    double dXai=Vr*tan(deltaf)/(lf+lr) ;
    double dX=V*cos(GodState.Xai+beta);
    double dY=V*sin(GodState.Xai+beta);

    GodState.Xai=GodState.Xai+dXai*dt;
    GodState.X=GodState.X+dX*dt;
    GodState.Y=GodState.Y+dY*dt;
};

struct timeval t1;
int GodSleep(){

    static int a=gettimeofday(&t1,NULL);
    static int i=t1.tv_sec%10000*1000+t1.tv_usec/1000;
    static int k=0;
    i+=10;
    //printf("%d\n",i);
    //if(i>10000)
    //exit(-1);

    gettimeofday(&t1,NULL);

    //cout<<" i:"<<i<<"   ";
    while(t1.tv_sec%10000*1000+t1.tv_usec/1000<i){

        gettimeofday(&t1,NULL);
        //usleep(10);
    }
    k++;
    //cout<<" t:"<<t1.tv_sec%10000*1000+t1.tv_usec/1000<<"   ";
    cout<<" k:"<<k<<"|||";

    return 1;
}


int SPIupdate(HistoryLinkedList_t &History, int fd){

    spi_transfer(fd,History.delta_PWM, History.v_PWM);
    cout<<" Delta,V:"<<History.delta_PWM<<"|"<<History.v_PWM;
};

int Control(GodState_t &mGodState, HistoryLinkedList_t &mHistoryLinkedList){
        mHistoryLinkedList.v_PWM=1000;
        mHistoryLinkedList.delta_PWM=1380;//1500+(int)500*cos(2*3.1415926/300*mGodState.t);
        mHistoryLinkedList.t=mGodState.t+1;
}//
// Created by xiabi on 2020/10/18.
//


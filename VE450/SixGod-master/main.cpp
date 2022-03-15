#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <sys/time.h>
#include "lidar.h"
#include "Map.h"
#include "camera.h"
#include <opencv2/opencv.hpp>
#include "uart.h"
#include "main.h"
#include "Triangulation.h"
#include <exception>
using namespace std;
using namespace cv;

GodState_t *GodState;
HistoryLinkedList_t* History;
HistoryLinkedList_t* Last;
SerialPort* uart1;

int main(){
    //TODO:Delete unnecessary initialization
    History=new HistoryLinkedList_t;
    History->next=new HistoryLinkedList_t;
    History->t=0;
    Last=History;
    GodState=new GodState_t;
    GodState->t=0;
    cout<<"INPUTXYXAI\r\n";
    cin>>GodState->X;
    cin>>GodState->Y;
    cin>>GodState->Xai;
    GodState->P[0][0]=1;
    GodState->P[0][1]=0;
    GodState->P[1][0]=0;
    GodState->P[0][1]=0;
    GodState->bias=0;
    GodState->K[0]=0;
    GodState->K[1]=0;

    //Serial Communication For UART
    char UART_ADD[13]="/dev/ttyUSB0";//TODO:try to solve the mix problem of USB0 and USB1
    uart1=new SerialPort(UART_ADD);
    if(!uart1->isOpen()){
        cerr<<"UART Not Open at"<<UART_ADD<<"\r\n";
    }

    //Lidar
    StartLidar("/dev/ttyUSB1");//TODO: add warning
try{

#ifdef THREAD0TEST
    thread0(nullptr);
#endif
#ifdef THREAD1TEST
    thread1(nullptr);
#endif
#ifdef ALLTEST
    thread Mthread0(thread0, nullptr);
    thread Mthread1(thread1, nullptr);
    Mthread0.join();
    Mthread1.join();

#endif
}
catch (...){

}
//cout<<"Stoped\r\n";
    uart1->close();
    StopLidar();
    return 0;
}
void* thread0(void* arg)
{
    //Initialize

#ifndef CAMERALESS
    VideoCapture cap = camera_start();
#endif
#ifdef CAMERALESS
    VideoCapture cap;
#endif

    Net net = getCNN();
    double LidarCloud[PointPerCycle*2]={0};//Theta0,R0,Theta1,R1,....
    double LandMark[PointPerCycle*3]={0};//Theta0,R0,N0,Theta1,R1,N1,....
    double identify_result[PointPerCycle*3] = {0};
    double Map[PointPerCycle*3]={0};
    double estimate_position[3] = {0};//x,y,theta
    int LandMarkNum,MapNum,LidarCloudNum;
    int identify_number;
    GodState_t CurrentState={0};
    Map_t map;
    //Loop
    int Thread0_Loop_Count=0;
    while(Thread0_Loop_Count>-1){
        static int Godt=0;
       // cout<<GodState->t-Godt<<endl;
      // cout<<"\r\n"<<Thread0_Loop_Count;
        Godt=GodState->t;
        Thread0_Loop_Count++;
        //cout<<"\r\n\r\nT0COUNT1:"<<Thread0_Loop_Count<<"\r\n\r\n";
        //cout<<"! am Here !"<<endl;
        //usleep(50000);

        CurrentState=*GodState;
        if((LidarCloudNum=GetLidar(LidarCloud))==-1)//此函数不断运行直至采集到一组lidar数据（~100ms)//This Function is already multit-hread.
            break;//防止死循环报错

 //       for (int pos = 0; pos < (int)LidarCloudNum ; ++pos) {
//         cout<<LidarCloud[pos*2]<<" ";
 //           cout<<LidarCloud[pos*2+1]<<endl;
   //     }
        //TODO: Normalize the output of thread0
        CurrentState=*GodState;
#ifndef CAMERALESS
Mat frame = GetPicture(cap);
#endif
#ifdef CAMERALESS
        Mat frame;
#endif
        LandMarkNum=LandMarkFusion(LidarCloud,LandMark,LidarCloudNum);
        //cout<<"LMN:"<<LandMarkNum<<"\r\n";
        //for (int pos = 0; pos < (int)LandMarkNum ; ++pos) {
       //cout<<LandMark[pos*3]<<"\t";
            //cout<<LandMark[pos*3+1]<<"\t";
            //cout<<LandMark[pos*3+2]<<"\r\n";
        //}
        //TODO: add cloud computation
#ifndef CAMERALESS
        identify_number = IMG_identify(identify_result, net, frame, LandMark, LandMarkNum,(int)time(0));//返回值是LandMark数量
#endif
#ifdef CAMERALESS
          identify_number = IMG_identifyCL(identify_result, net, frame, LandMark, LandMarkNum,(int)time(0));//返回值是LandMark数量
#endif
        int k=0;
        int p=1;
        //cout<<endl<<endl;
        //for (int pos = 0; pos < (int)identify_number ; ++pos) {
           // cout<<identify_result[pos*3]<<"\t";
         //   cout<<identify_result[pos*3+1]<<"\t";
       //     cout<<identify_result[pos*3+2]<<"\r\n";
      //  }
        //cout<<endl<<endl;
        try {
            StaticFusion(estimate_position, identify_result, identify_number, &map, MapNum, CurrentState);
          //  cout<<"Current State:"<<CurrentState.X<<" "<<CurrentState.Y<<" "<<CurrentState.Xai<<endl;
/*
            while(GodState->t!=CurrentState.t){
                //cout<<endl<<"Godt,Ct:"<<GodState->t<<"|"<<CurrentState.t<<endl;
                My_KalmanFilter(*History,CurrentState);
                HistoryLinkedList_t* temp=History;
                History->next=History;
                //delete temp;
            }
            */
#ifdef THREAD0FEEDBACK
            if(abs(GodState->X-CurrentState.X)<0.4&&abs(GodState->Y-CurrentState.Y)<0.4&&abs(GodState->Xai-CurrentState.Xai)<30){
            //    cout<<"Now feedback (GX GY GXai CX CY CXai):"<<GodState->X<<" "<<GodState->Y<<" "<<GodState->Xai<<" "<<CurrentState.X<<" "<<CurrentState.Y<<" "<<CurrentState.Xai<<endl;
                GodState->X=CurrentState.X;
                GodState->Y=CurrentState.Y;
                GodState->Xai=CurrentState.Xai;
            }else{
          //      cout<<"Reject to feedback (GX GY GXai CX CY CXai):"<<GodState->X<<" "<<GodState->Y<<" "<<GodState->Xai<<" "<<CurrentState.X<<" "<<CurrentState.Y<<" "<<CurrentState.Xai<<endl;

            }
#endif
        }
        catch (...){
            //cout<<"Not Enough LM\r\n";
        }
        //TODO:add output of thread0 back to thread1

     //   cout<<"Input X,y,xai:\r\n";
      //  cin>>GodState->X>>GodState->Y>>GodState->Xai;
    }
    camera_end(cap);
    return nullptr;
}

void* thread1(void* arg)
{
    //initialize
    fstream fst1;
    fst1.open("./Thread1LOG.txt", ios::app);
    time_t cT=time(0);
    fst1<<ctime(&cT)<<endl<<endl;
    //Loop
    while(true){
        Last=Last->next;
        Last->next=new HistoryLinkedList_t;
        GodUpdate(*Last);
        My_KalmanFilter(*Last,*GodState);
        Control(*GodState,*Last->next);
#ifdef THREAD1OUT
       // if (GodState->t%10==0)
        cout<<"t|Xai|X|Y: "<<GodState->t<<" "<<GodState->Xai<<" "<<GodState->X<<" "<<GodState->Y<<"\r\n";
        fst1<<GodState->t<<" "<<GodState->Xai<<" "<<GodState->X<<" "<<GodState->Y<<"\r\n";
#endif
        if(!GodSleep())break;//等待直到下一个10ms开始
    }
    //Finish
    return nullptr;
}
int My_KalmanFilter(HistoryLinkedList_t &Data,GodState_t &My_GodState){//TODO: verification, unit should be changed into SI
    My_GodState.t++;
    My_GodState.X*=100;
    My_GodState.Y*=100;
    My_GodState.Xai=My_GodState.Xai/180*M_PI;
    //constant:
    double lf=33;
    double lr=23;        //%IMU距离前后轮的距离f-前轮，r-后轮 unit:m, 待测定
    double Kd=0.0008977;
    double Id=-1.295;
    double Kv=0.04485 ;//%待测定
    double Iv=-42.91;
    double deltaf=Kd*Data.delta_PWM+Id;  //%前轮角
    double Vr=Kv*Data.v_PWM+Iv;          //%后轮速度
    if (Data.v_PWM<1050)Vr=0;
    double dt=0.01;//%unit: ms

    double beta=atan(lr*tan(deltaf)/(lf+lr));
    double V=Vr/(cos(beta));
    double Vf=Vr/(cos(deltaf));

    double dXai=Vr*tan(deltaf)/(lf+lr) ;
    double dX=V*cos(My_GodState.Xai+beta);
    double dY=V*sin(My_GodState.Xai+beta);

    My_GodState.Xai=My_GodState.Xai+dXai*dt;
    My_GodState.X=My_GodState.X+dX*dt;
    My_GodState.Y=My_GodState.Y+dY*dt;

    My_GodState.X/=100;
    My_GodState.Y/=100;
    My_GodState.Xai=My_GodState.Xai*180/M_PI;
    while(My_GodState.Xai>180)
        My_GodState.Xai-=360;
    while(My_GodState.Xai<-180)
        My_GodState.Xai+=360;


 //   cout<<"\r\n Xai|X|Y: "<<My_GodState.Xai<<" "<<My_GodState.X<<" "<<My_GodState.Y<<"|";
/*
    //purely physical model;
    //Kalman filter to update Xai
    double Q_angle = 0.001;
    double Q_gyroBias = 0.003;
    double R_measure = 0.03;
    double Xai_math=My_GodState.Xai;
    double Xai_diff;
    double omega_measured=Data.omegaz;
    double P00_temp = 0;
    double P01_temp = 0;
    double S=0;
    double omega;
    omega=omega_measured-GodState->bias;
    Xai_tem += dt * omega;
    GodState->P[0][0] += dt * (dt * GodState->P[1][1] - GodState->P[0][1] - GodState->P[1][0] + Q_angle);
    GodState->P[0][1] -= dt * GodState->P[1][1];
    GodState->P[1][0] -= dt * GodState->P[1][1];
    GodState->P[1][1] += Q_gyroBias * dt;
    Xai_diff = Xai_math - Xai_tem;
    S = GodState->P[0][0] + R_measure;
    GodState->K[0] = GodState->P[0][0] / S;
    GodState->K[1] = GodState->P[1][0] / S;
    GodState->Xai=Xai_tem+GodState->K[0]*Xai_diff;
    GodState->bias += GodState->K[1] * Xai_diff;
    P00_temp = GodState->P[0][0];
    P01_temp = GodState->P[0][1];
    GodState->P[0][0] -= GodState->K[0] * P00_temp;
    GodState->P[0][1] -= GodState->K[0] * P01_temp;
    GodState->P[1][0] -= GodState->K[1] * P00_temp;
    GodState->P[1][1] -= GodState->K[1] * P01_temp;
    */
};

int GodSleep(){
    struct timeval t1;
    static int a=gettimeofday(&t1, nullptr);
    static int i=t1.tv_sec%10000*1000+t1.tv_usec/1000;
    static int k=0;
    i+=10;
    gettimeofday(&t1,nullptr);
    while(t1.tv_sec%10000*1000+t1.tv_usec/1000<i){
        gettimeofday(&t1,nullptr);
    }
    k++;
#ifdef THREAD1OUT
//    cout<<"\r\nClock:\t"<<k<<"|";
#endif
    return 1;
}


int GodUpdate(HistoryLinkedList_t &History){
    int16_t RX[4]={77,77,77,77};
    int16_t TX[4]={4396,History.delta_PWM,History.v_PWM,6324};
    uart1->write(TX,8);
    uart1->read(RX,8);
    History.ax=RX[0];
    History.ay=RX[1];
    History.omegaz=RX[2];
#ifdef THREAD1OUT
   // cout<<"\rDelta,V:"<<History.delta_PWM<<"|"<<History.v_PWM;
   // cout<<"(RAW)ax,ay,wz:"<<(int)RX[0]<<"|"<<(int)RX[1]<<"|"<<(int)RX[2];
#endif

};

int Control(const GodState_t &mGodState, HistoryLinkedList_t &mHistoryLinkedList){
    if (mGodState.t <= 10) {
        mHistoryLinkedList.v_PWM=1000;
        mHistoryLinkedList.delta_PWM=1200;//1500+(int)500*cos(2*3.1415926/300*mGodState.t);
        mHistoryLinkedList.t=mGodState.t+1;

    }else if(mGodState.t <= 8000){

            double AA=mGodState.X*mGodState.X+mGodState.Y*mGodState.Y;
            AA=sqrt(AA);
            mHistoryLinkedList.v_PWM=1500;
        auto t=(short)floor(1700+1500*(AA-3));//1500+(int)500*cos(2*3.1415926/300*mGodState.t);
        if(t<1000)t=1000;
        if(t>2000)t=2000;
            mHistoryLinkedList.delta_PWM=t;
            mHistoryLinkedList.t=mGodState.t+1;
    }
    else {
        mHistoryLinkedList.v_PWM = 1000;
        mHistoryLinkedList.delta_PWM = 1380;
        mHistoryLinkedList.t = mGodState.t + 1;
    }
}

int ReadMap(double * map){}


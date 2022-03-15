//
// Created by xiabi on 2020/10/20.
//

#include <unistd.h>
#include "include/rplidar.h"
#include "lidar.h"
#include <math.h>
#include <iostream>
using namespace rp::standalone::rplidar;

RPlidarDriver * drv;


int GetLidar(double* LidarCloud){
    rplidar_response_measurement_node_hq_t nodes[8192];
    size_t   count = 8192;

    drv->grabScanDataHq(nodes, count,10000);
    drv->ascendScanData(nodes, count);
    for (int pos = 0; pos < (int)count ; ++pos) {

        LidarCloud[pos*2]=nodes[pos].angle_z_q14* 90. / (1 << 14);
        LidarCloud[pos*2+1]=nodes[pos].dist_mm_q2 / (1 << 2);
    }
    //std::cout<<"Count:"<<count<<std::endl;
    return (int) count;
}

int LandMarkFusion(double* LidarCloud, double* LandMark,int LidarCloudNum){
    int count=0;
    double history_d=0;//distance
    double history_a=0;//angle
    double sum_d=0;
    double sum_a=0;
    int counti=0;
    for(int i=0;i<LidarCloudNum;i++){
        if(LidarCloud[i*2+1]==0)continue;
        //std::cout<<LidarCloud[i*2]<<" "<<LidarCloud[i*2+1]<<std::endl;
        double interval_a=fabs(LidarCloud[i*2]-history_a);
        double interval_d=fabs(LidarCloud[i*2+1]-history_d);
        history_a=LidarCloud[i*2+0];
        history_d=LidarCloud[i*2+1];
        if(interval_a<5&&interval_d<40){
            counti++;
            sum_d+=LidarCloud[i*2+1];
            sum_a+=LidarCloud[i*2];
        }else{
            if (counti==0)continue;
            if (counti>0) {
                LandMark[count * 3 + 0] = sum_a / (double) counti;
                LandMark[count * 3 + 1] = sum_d / (double) counti;
                LandMark[count * 3 + 2] = (double) counti;
                //std::cout<<LandMark[count * 3 + 0]<<" "<<LandMark[count * 3 + 1]<<" "<<LandMark[count * 3 + 2]<<std::endl;

                count++;

            }
            counti=1;
            sum_a=LidarCloud[i*2+0];
            sum_d=LidarCloud[i*2+1];
        }
    }
    if (counti>0) {
        LandMark[count * 3 + 0] = sum_a / (double) counti;
        LandMark[count * 3 + 1] = sum_d / (double) counti;
        LandMark[count * 3 + 2] = (double) counti;
       // std::cout<<LandMark[count * 3 + 0]<<" "<<LandMark[count * 3 + 1]<<" "<<LandMark[count * 3 + 2]<<std::endl;

        count++;

    }
    return count;


}//返回值是LandMark数量

int StartLidar(const char * device_address){
    drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
    drv->connect(device_address, 115200);
    drv->startMotor();

    drv->startScan(0,1);
}
int StopLidar(){
    drv->stop();
    drv->stopMotor();
    RPlidarDriver::DisposeDriver(drv);
}
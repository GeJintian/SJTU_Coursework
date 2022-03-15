#include <iostream>
//#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include<windows.h>
#include <ctime>
#include <cmath>
#include <sys/time.h>
#include "lidar.h"
#include "camera.h"
#include <opencv2/opencv.hpp>
#include "uart.h"

using namespace std;
using namespace cv;


SerialPort* uart1;

int main(){

    //Serial Communication For UART
    char UART_ADD[19]="/dev/ttyUSB0";
    uart1=new SerialPort(UART_ADD);
    if(!uart1->isOpen()){
        cerr<<"UART Not Open at"<<UART_ADD<<"\r\n";
    }
    else{
        for(int i=0;i<10;i++) {
            int16_t TX[4]={4396,1380,1000,6324};
            uart1->write(TX,8);
            usleep(1000);
            cout<<"Stoping...\r";
        }
    }

    //Lidar
    StartLidar("/dev/ttyUSB1");
    uart1->close();
    StopLidar();
    cout<<"Stopped.";
    return 0;
}
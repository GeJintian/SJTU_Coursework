//
// Created by 69009 on 2020/10/20.
//

#include "camera.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <thread>
using namespace std;
using namespace cv;
using namespace cv::dnn;


static string category[5] = {"Blue", "Green", "Red", "Rubbish", "Yellow"};

Mat Picture_segmentation(Mat frame, int start_point, int end_point){
    Mat E = frame(Range::all(),Range(start_point, end_point));
    return E;
}

Mat GetPicture(VideoCapture cap){
    Mat frame;
    cap>>frame;

    return frame;
}

VideoCapture camera_start(){
    VideoCapture cap("/dev/video0");//Change the name of your device here
    if (!cap.isOpened()) cout<<"Camera is not opened!"<<endl;
    return cap;
}

void camera_end(VideoCapture cap){
    cap.release();
}

void IMG_save(Mat frame, double * LandMark, int LandMarkNum, int count){
    string s = "/home/odroid/camera/picture2/" + to_string(count) + ".jpg";
    imwrite(s,frame);
    s = "/home/odroid/camera/picture/" + to_string(count) + "_"+ to_string(time(0));
    int start_point, end_point;
    double pos;
    double dis;
    double ang;
    for(int i = 0; i < LandMarkNum; i++){
        pos = LandMark[3*i];
        dis = LandMark[3*i+1];
        if(pos > 180) pos = pos - 360;
        if(abs(pos) > 30) continue;
        pos = pos / 180.0 * M_PI;
        ang = asin(sin(pos)*dis/sqrt(dis*dis+380*380-2*dis*380*cos(pos)))*180/M_PI;

        if(abs(ang) > 30) continue;
        start_point = (0.306 * ang +14.233)/26.8*640-30;

        end_point = (0.306 * ang +14.233)/26.8*640+30;
        if (end_point>639)end_point=639;
        if (start_point>638)start_point=638;

        if (start_point<0)start_point=0;
        if (end_point<1)end_point=1;
        //cout<<ang<<" "<<start_point<<" "<<end_point<<"EEE"<<endl;
        Mat E = Picture_segmentation(frame, start_point, end_point);
        string name = s + to_string(i) + ".jpg";
        imwrite(name, E);
    }
}

Net getCNN(){
    String weights = "./frozen/3conv_complex/frozen_graph.pb";
    Net net = readNetFromTensorflow(weights);//TODO: change CNN
    if(net.empty())cout<<"Can not load net"<<endl;
    return net;
}

int classification(const Mat & picture, Net net, int count1, int count2){
    Mat inputBlob = blobFromImage(picture, 1, Size(60,480), Scalar(), true, false);
    net.setInput(inputBlob);
    Mat pred = net.forward();
    Point maxLoc;
    minMaxLoc(pred, NULL, NULL, NULL, &maxLoc);
    int i = maxLoc.x;
    //imshow("Image", picture);
    string s = "/tmp/picture/" + to_string(count1) +to_string(count2) + category[i] + "CC.jpg";
    static int ii=0;
    //cout<<++ii<<"\r\n";
    imwrite(s,picture);
    //cout<<"Classification is :"<<category[i]<<endl;
    return i;
}
static void* iithread(const Mat &E,Net net,int count,int mni,int *classify){

    *(classify+mni) = classification(E, net, count, mni);
}
int IMG_identify(double * identify_result, Net net,  Mat frame, double * LandMark, int LandMarkNum, int count){

    Mat E;
    int classify;
    int start_point, end_point;
    double pos;
    double dis;
    double ang;
    int number = 0;
    int ThreadCount=0;
    int IdentifiedCount=0;
    for(int i=0; i < LandMarkNum; i++) {
        pos = LandMark[3 * i];
        dis = LandMark[3 * i + 1];
        if (pos > 180) pos = pos - 360;

        pos = pos / 180.0 * M_PI;
        ang = asin(sin(pos) * dis / sqrt(dis * dis + 380 * 380 - 2 * dis * 380 * cos(pos))) * 180 / M_PI;

        if ( abs(LandMark[3 * i])>0) {

            identify_result[3*number] = LandMark[3*i];
            identify_result[3*number+1] = LandMark[3*i+1]/1000;
            identify_result[3*number+2] = -1;

            number ++;
            continue;
        }

   //     cout<<LandMark[3*i]<<" ";
     //   cout<<LandMark[3*i+1]<<" ";
       // cout<<LandMark[3*i+2]<<" ";
       // cout<<"BFIDD"<<endl;
        start_point = (0.306 * ang + 14.233) / 26.8 * 640 - 30;

        end_point = (0.306 * ang + 14.233) / 26.8 * 640 + 30;
        if (end_point > 639)end_point = 639;
        if (start_point > 638)start_point = 638;

        if (start_point < 0)start_point = 0;
        if (end_point < 1)end_point = 1;


        E = Picture_segmentation(frame, start_point, end_point);
        classify = classification(E, net, count, i);
        if(classify != 3){
            identify_result[3*number] = LandMark[3*i];
            identify_result[3*number+1] = LandMark[3*i+1]/1000;
            identify_result[3*number+2] = classify;
        //    cout<<identify_result[3*number]<<" ";
          //  cout<<identify_result[3*number+1]<<" ";
            //cout<<identify_result[3*number+2]<<" ";
          //  cout<<"IDD"<<endl;


            number ++;
        }

    }

    for(int i=0;i<number-1;i++){
        for(int j=i;j<number-1;j++){
            if(identify_result[3*j+2]<identify_result[3*(j+1)+2] ){
                double temp_a=identify_result[3*j];
                double temp_b=identify_result[3*j+1];
                double temp_c=identify_result[3*j+2];
                identify_result[3*j]   =identify_result[3*(j+1)];
                identify_result[3*j+1]  =identify_result[3*(j+1)+1];
                identify_result[3*j+2]  =identify_result[3*(j+1)+2];
                identify_result[3*(j+1)]  =temp_a;
                identify_result[3*(j+1)+1]  =temp_b;
                identify_result[3*(j+1)+2]  =temp_c;

            }
        }
    }
    return number;
}


int IMG_identifyCL(double * identify_result, Net net,  Mat frame, double * LandMark, int LandMarkNum, int count){

    Mat E;
    int classify;
    int start_point, end_point;
    double pos;
    double dis;
    double ang;
    int number = 0;
    int ThreadCount=0;
    int IdentifiedCount=0;
    for(int i=0; i < LandMarkNum; i++) {
        pos = LandMark[3 * i];
        dis = LandMark[3 * i + 1];
        if (pos > 180) pos = pos - 360;

        pos = pos / 180.0 * M_PI;
        ang = asin(sin(pos) * dis / sqrt(dis * dis + 380 * 380 - 2 * dis * 380 * cos(pos))) * 180 / M_PI;

        if ( true) {

            identify_result[3*number] = LandMark[3*i];
            identify_result[3*number+1] = LandMark[3*i+1]/1000;
            identify_result[3*number+2] = -1;

            number ++;
            continue;
        }

        //     cout<<LandMark[3*i]<<" ";
        //   cout<<LandMark[3*i+1]<<" ";
        // cout<<LandMark[3*i+2]<<" ";
        // cout<<"BFIDD"<<endl;
        start_point = (0.306 * ang + 14.233) / 26.8 * 640 - 30;

        end_point = (0.306 * ang + 14.233) / 26.8 * 640 + 30;
        if (end_point > 639)end_point = 639;
        if (start_point > 638)start_point = 638;

        if (start_point < 0)start_point = 0;
        if (end_point < 1)end_point = 1;


        E = Picture_segmentation(frame, start_point, end_point);
        classify = classification(E, net, count, i);
        if(classify != 3){
            identify_result[3*number] = LandMark[3*i];
            identify_result[3*number+1] = LandMark[3*i+1]/1000;
            identify_result[3*number+2] = classify;
            //    cout<<identify_result[3*number]<<" ";
            //  cout<<identify_result[3*number+1]<<" ";
            //cout<<identify_result[3*number+2]<<" ";
            //  cout<<"IDD"<<endl;


            number ++;
        }

    }

    for(int i=number;i>0;i--){
        for(int j=0;j<i;j++){
            if(abs(identify_result[3*j+1])>abs(identify_result[3*(j+1)+1]) ){
                double temp_a=identify_result[3*j];
                double temp_b=identify_result[3*j+1];
                double temp_c=identify_result[3*j+2];
                identify_result[3*j]   =identify_result[3*(j+1)];
                identify_result[3*j+1]  =identify_result[3*(j+1)+1];
                identify_result[3*j+2]  =identify_result[3*(j+1)+2];
                identify_result[3*(j+1)]  =temp_a;
                identify_result[3*(j+1)+1]  =temp_b;
                identify_result[3*(j+1)+2]  =temp_c;

            }
        }
    }
    return number;
}
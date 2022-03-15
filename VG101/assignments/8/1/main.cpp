#include <iostream>
#include <ctime>
#include <iomanip>
#include "Parkinglot.h"
using namespace std;
int loop1(int*park,int ltimein){
    int timein,timeout;
    timein=rand()%(181-ltimein)+ltimein;timeout=rand()%270+timein;
    int n,i;
    int k=0;
    n=rand()%2+1;
    if(n==1){
        van veh;
        veh.intimein(timein);
        veh.intimeout(timeout);
        for(i=0;i<5;i++){
            if(*(park+i)<veh.outtimein()){*(park+i)=0;k=1;}
        }
        if(k==0){
veh.noticket();
        }
        else {
        for(i=0;i<5;i++){
            if(*(park+i)==0){*(park+i)=veh.outtimeout();break;}}
        veh.slot(i);
            veh.ticket();
        return veh.outtimein();
    }}
    else {
        car veh;
        veh.intimein(timein);
        veh.intimeout(timeout);
        for(i=0;i<5;i++){
            if(*(park+i)<veh.outtimein()){*(park+i)=0;k=1;}
        }
        if(k==0){
            veh.noticket();
        }
        else {
            for(i=0;i<5;i++){
                if(*(park+i)==0){*(park+i)=veh.outtimeout();break;}
            }
            veh.slot(i);
            veh.ticket();
        }
        return veh.outtimein();
    }
}
int loop2(int*park,int ltimein){
    int timein,timeout;
    timein=rand()%(181-ltimein)+ltimein;timeout=rand()%270+timein;
    int n,i;
    int k=0;
    n=rand()%2+1;
    if(n==1){
        motorbike veh;
        veh.intimein(timein);
        veh.intimeout(timeout);
        for(i=0;i<10;i++){
            if(*(park+i)<veh.outtimein()){*(park+i)=0;k=1;}
        }
        if(k==0){
            veh.noticket();
        }
        else {
            for(i=0;i<10;i++){
                if(*(park+i)==0){*(park+i)=veh.outtimeout();break;}
            }
            veh.slot(i);
            veh.ticket();
        }
        return veh.outtimein();
    }
    else {
        bicycle veh;
        veh.intimein(timein);
        veh.intimeout(timeout);
        for(i=0;i<10;i++){
            if(*(park+i)<veh.outtimein()){*(park+i)=0;k=1;}
        }
        if(k==0){
            veh.noticket();
        }
        else {
            for(i=0;i<10;i++){
                if(*(park+i)==0){*(park+i)=veh.outtimeout();break;}
            }
            veh.slot(i);
            veh.ticket();
        }
        return veh.outtimein();
    }
}
int main(){
    srand(time(NULL));
    int park1[10]={0,0,0,0,0,0,0,0,0,0};
    int park2[5]={0,0,0,0,0};
    int j,n;j=0;

while(j<180){
    n=rand()%2+1;
        if(n==1){
            j=loop1(park2,j);
        }
        else{j=loop2(park1,j);}
    }
    return 0;
}

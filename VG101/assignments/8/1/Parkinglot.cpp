//
// Created by 69009 on 2017/12/7.
//

#include "Parkinglot.h"
#include <iostream>
#include <iomanip>

van::van(char*t, int p,int m) {type=t;price=p;f=m;}
void van::intimein(int a) {timein=a;}
void van::intimeout(int a) {timeout=a;}
int van::outtimein() {return timein;}
int van::outtimeout() {return timeout;}
void van::slot(int x) {i=x;}
car::car(char*t, int p,int m) {type=t;price=p;f=m;}
void car::intimein(int a) {timein=a;}
void car::intimeout(int a) {timeout=a;}
int car::outtimein() {return timein;}
int car::outtimeout() {return timeout;}
void car::slot(int x) {i=x;}
motorbike::motorbike(char*t, int p,int m) {type=t;price=p;f=m;}
void motorbike::intimein(int a) {timein=a;}
void motorbike::intimeout(int a) {timeout=a;}
int motorbike::outtimein() {return timein;}
int motorbike::outtimeout() {return timeout;}
void motorbike::slot(int x) {i=x;}
bicycle::bicycle(char*t, int p,int m) {type=t;price=p;f=m;}
void bicycle::slot(int x) {i=x;}
void bicycle::intimein(int a) {timein=a;}
void bicycle::intimeout(int a) {timeout=a;}
int bicycle::outtimein() {return timein;}
int bicycle::outtimeout() {return timeout;}
void vehicle::ticket() {
    std::cout.fill('0');
    std::cout<<"************ Arrival ticket ************"<<std::endl;
    std::cout<<"Arrival: ";
    if(timein<60){std::cout<<"8:"<<std::setw(2)<<timein<<std::endl;}
    else if(timein>=60&&timein<120){std::cout<<"9:"<<std::setw(2)<<timein-60<<std::endl;}
    else if(timein>=120&&timein<180){std::cout<<"10:"<<std::setw(2)<<timein-120<<std::endl;}
    else{std::cout<<"11:"<<std::setw(2)<<timein-180<<std::endl;}
    std::cout<<"Type: "<<type<<std::endl;
    std::cout<<"Please go to "<<i+1<<" slot,"<<f<<"f"<<std::endl;
    std::cout<<"************ Departure ticket ************"<<std::endl;
    std::cout<<"Spent time: "<<timeout-timein<<" minutes"<<std::endl;
    std::cout<<"Type: "<<type<<std::endl;
    std::cout<<"Price: "<<price*(timeout-timein)<<std::endl;
    std::cout<<std::endl;
}
void vehicle::noticket() {
        std::cout.fill('0');
    std::cout<<"************ Arrival ticket ************"<<std::endl;
    std::cout<<"Arrival: ";
    if(timein<60){std::cout<<"8:"<<std::setw(2)<<timein<<std::endl;}
    else if(timein>=60&&timein<120){std::cout<<"9:"<<std::setw(2)<<timein-60<<std::endl;}
    else if(timein>=120&&timein<180){std::cout<<"10:"<<std::setw(2)<<timein-120<<std::endl;}
    else{std::cout<<"11:00"<<std::endl;}
    std::cout<<"Type: "<<type<<std::endl;
    std::cout<<"No slot left"<<std::endl;
    std::cout<<"************ Departure ticket ************"<<std::endl;
    std::cout<<"Spent time: "<<timeout-timein<<" minutes"<<std::endl;
    std::cout<<"Type: "<<type<<std::endl;
    std::cout<<"Price: "<<price*(timeout-timein)<<std::endl;
    std::cout<<std::endl;
}

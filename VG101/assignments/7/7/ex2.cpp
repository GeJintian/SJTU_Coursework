//
// Created by 69009 on 2017/11/29.
//
#include <iostream>
#include <iomanip>

using namespace std;
void ex2(){
    int n;
    cout<<"If want to convert US dollars to Chinese RMB,please enter 1,otherwise enter 2 : ";
    cin>>n;
    float amount;int precision;
    cout<<"Enter the amount and the precision: ";
    cin>>amount>>precision;
    if(n==1){
        cout<<setprecision(precision)<<amount*6.2035;
    }
    else{
        cout<<setprecision(precision)<<amount/6.2035;
    }
}

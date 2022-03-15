//
// Created by 69009 on 2017/11/9.
//

#include "variance.h"
double variance(double*a,double mean){
    double varian;
    varian=((a[0]-mean)*(a[0]-mean)+(a[1]-mean)*(a[1]-mean)+(a[2]-mean)*(a[2]-mean)+(a[3]-mean)*(a[3]-mean)+(a[4]-mean)*(a[4]-mean)+(a[5]-mean)*(a[5]-mean)+(a[6]-mean)*(a[6]-mean)+(a[7]-mean)*(a[7]-mean)+(a[8]-mean)*(a[8]-mean)+(a[9]-mean)*(a[9]-mean))/10;
    return varian;
}
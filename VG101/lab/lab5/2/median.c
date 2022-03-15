//
// Created by 69009 on 2017/11/9.
//

#include "median.h"
double median(double*a){
    int m,n;
    double media,t;
    for(m=0;m<9;m++) {
        for (n = 0; n < 9 - m; n++) {
            if (a[n] > a[n + 1]) {
                t = a[n];
                a[n] = a[n + 1];
                a[n + 1] =t;
            }
        }
    }
    media=(a[4]+a[5])/2;
    return media;
}
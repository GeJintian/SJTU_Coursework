#include<stdio.h>
#define pi 3.1415926
int main(void)
{
    float G=6.674E-11;
    float T,d,c,V,M,D;
    printf("please enter the period: ");
    scanf("%f",&T);
    printf("please enter the distance: ");
    scanf("%f",&d);
    printf("please enter the cir: ");
    scanf("%f",&c);
    V=4*pi/3*(c/(2*pi))*(c/(2*pi))*(c/(2*pi));
    M=4*pi*pi*d*d*d/(G*T*T);
    D=M/V;
    printf("the density is %f\n",D);
    return 0;
}
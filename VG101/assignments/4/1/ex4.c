#include <stdio.h>
#include <math.h>
//
// Created by 69009 on 2017/11/2.
//
void ex4(){
    double a,b,c,x1,x2;
    printf("please input the coefficients: ");
    scanf("%lf %lf %lf",&a,&b,&c);
    x1=(-b+sqrt(b*b-4*a*c))/(2*a);
    x2=(-b-sqrt(b*b-4*a*c))/(2*a);
    printf("%lf\n",x1);
    printf("%lf\n",x2);
}

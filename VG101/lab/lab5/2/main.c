#include <stdio.h>
#include "mean.h"
#include "median.h"
#include "variance.h"
#include "deviation.h"
int main() {
    double a[10];
    double mea,varian;
    printf("Enter ten marks: ");
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9]);
    mea=mean(a);
    printf("The mean is:%lf\n",mea);
    printf("The median is:%lf\n",median(a));
    varian=variance(a,mea);
    printf("The variance is:%lf\n",varian);
    printf("The standard deviation is:%lf\n",deviation(varian));
    return 0;
}
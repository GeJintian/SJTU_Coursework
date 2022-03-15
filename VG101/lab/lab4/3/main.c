#include <stdio.h>
#include <math.h>
#include <float.h>

double tra(double x);
int main() {
    double v0=30;
    double radian=3.1415926/180*30;
    double a,b,c,t;
    a=75;b=85;
    c=(a+b)/2;
    while(b-a>=FLT_EPSILON) {
        if (tra(c) < 0) {
            if (tra(a) > 0) {
                b = c;
                c = (a + b) / 2;
            }
            if (tra(b) > 0) {
                a = c;
                c = (a + b) / 2;
            }
        }
        else if (tra(c) > 0) {
            if (tra(a) < 0) {
                b = c;
                c = (a + b) / 2;
            }
            if (tra(b) < 0) {
                a = c;
                c = (a + b) / 2;
            }
        }
        if (tra(c) == 0)
            break;
    }
    printf("The x is:%lf\n",c);
    t=c/(v0*cos(radian));
    printf("The time is:%lf",t);
}
double tra(double x){
    double y;
    double v0=30;
    double radian=3.1415926/180*30;
    y=1.5+tan(radian)*x-(9.81/(2*v0*v0*cos(radian)*cos(radian)))*x*x;
    return y;
}
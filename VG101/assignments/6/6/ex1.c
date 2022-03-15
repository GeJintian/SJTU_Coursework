//
// Created by 69009 on 2017/11/17.
//
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define pi 3.1415926
double convptoc(double**pol);
double **convctop(double**car);
typedef struct _Polar{
    double p[2];
}polar;
typedef struct _Cartesian{
    double p[2];
}cart;
int main(){
    cart n1;
    n1.p[1]=3;n1.p[2]=0.8;
    cart n2;
    n2.p[1]=0;n2.p[2]=log(4);
    cart n3;
    n3.p[1]=45.245;n3.p[2]=0.235;
    cart n4;
    n4.p[1]=3*cos(pi/17);n4.p[2]=3*sin(pi/17);
    cart n5;
    n5.p[1]=4*cos(pi/9);n5.p[2]=4*sin(pi/9);
    cart n6;
    n6.p[1]=cos(pi/12);n6.p[2]=sin(pi/12);
    double car[6][2]={{n1.p[1],n1.p[2]},{n2.p[1],n2.p[2]},{n3.p[1],n3.p[2]},{n4.p[1],n4.p[2]},{n5.p[1],n5.p[2]},{n6.p[1],n6.p[2]}};
    double**pol=convctop(car);
    int i;
    for(i=0;i<6;i++){
        printf("(%lf,%lf)",car[i][1],car[i][2]);printf(" ");printf("(%lf,%lf)\n",pol[i][1],pol[i][2]);
    }
}
double **convctop(double**car){
    int a,b;
    a=sizeof(car);
    double**pol=malloc(a*sizeof(double*));
    pol[a]=malloc(2*sizeof(double*));
    int i;
    for(i=0;i<a;i++){
        pol[i][1]=sqrt(car[i][1]*car[i][1]+car[i][2]*car[i][2]);
        pol[i][2]=acos(car[i][1]/pol[i][1]);
    }
    return pol;
}
double convptoc(double**car){
    int a,b;
    a=sizeof(car);
    double**pola=malloc(a*sizeof(double*));
    pola[a]=malloc(2*sizeof(double*));
    int i;
    for(i=0;i<a;i++){
        pola[i][1]=car[i][1]*cos(car[i][2]);
        pola[i][2]=car[i][1]*sin(car[i][2]);
    }
    return **pola;

}

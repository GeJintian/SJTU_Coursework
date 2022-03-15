#include <stdio.h>

//
// Created by 69009 on 2017/11/2.
//

typedef struct Complex{
    int real;
    int image;
}Complex;
Complex sum(int ar,int ai,int br,int bi){
    int cr,ci;
    cr=ar+br;ci=ai+bi;
    Complex su;
    su.real=cr;
    su.image=ci;
    return su;
}
Complex product(int ar,int ai, int br, int bi){
    int dr,di;
    dr=ar*br-ai*bi;di=ar*bi+br*ai;
    Complex pro;
    pro.real=dr;
    pro.image=di;
    return pro;
}
void ex1(){
    int ar,ai,br,bi;
    printf("Please enter the real part and image part of two numbers: ");
    scanf("%d %d %d %d",&ar,&ai,&br,&bi);
    struct Complex pro;struct Complex su;
    pro=product(ar,ai,br,bi);su=sum(ar,ai,br,bi);
    printf("The product is %d+%di\n",pro.real,pro.image);
    printf("The sum is %d+%di\n",su.real,su.image);
}


#include <stdio.h>

//
// Created by 69009 on 2017/11/2.
//
void ex2(){
    int a,b,i,gcd;
    printf("Please enter two numbers: ");
    scanf("%d %d",&a,&b);
    for(i=1;i<=a;i++){
        if(a%i==0&&b%i==0)
            gcd=i;}
        printf("The GCD is %d\n",gcd);
    return;

}

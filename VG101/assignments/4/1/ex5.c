//
// Created by 69009 on 2017/11/3.
//
#include <stdio.h>
#define SWAP(a,b){a=a+b;\
    b=a-b;\
    a=a-b;}
void ex5(){
    int a,b;
    printf("Please enter two number:");
    scanf("%d %d",&a,&b);
    SWAP(a,b);
    printf("The number after swap is %d and %d\n",a,b);
}

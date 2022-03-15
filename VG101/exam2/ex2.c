//
// Created by 69009 on 2017/11/23.
//

#include <stdio.h>

void ex2(){
    int n;
    printf("Please enter an integer: ");
    scanf("%d",&n);
    int i;
    for(i=0;i<32;i++){
        if(n<<1==n*2){printf("0");}
        else{printf("1");}

    }
    printf("\n");
    n=n<<2;
    for(i=0;i<32;i++){
        if(n<<1==n*2){printf("0");}
        else{printf("1");}

    }
    printf("\n");
}
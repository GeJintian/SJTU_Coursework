#include <malloc.h>
#include <stdio.h>
#include <time.h>

//
// Created by 69009 on 2017/11/17.
//
void ex2(){
    int n,random;
    printf("Enter the number n:");
    scanf("%d",&n);
    int*array=malloc(n*sizeof(int));
    int i,z;
    printf("Enter the numbers in the array: ");
    for(i=0;i<n;i++){
        scanf("%d",&array[i]);
    }
    int j,k;
    for(j=0;j<(n-1);j++){
        if(array[j]<array[j+1])k=array[j+1];
        else {k=array[j];}
    }
    srand(time(NULL));
    random=rand()%k;
    int m;
    printf("The numbers larger than a random number are: ");
    for(m=0;m<n;m++){
        if(random<*(array+m))printf("%d ",array[m]);
    }
    printf("\n");
}

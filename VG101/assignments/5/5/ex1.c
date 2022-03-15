#include <stdio.h>
#include <malloc.h>

//
// Created by 69009 on 2017/11/10.
//
int isprime(int i);
void ex1(){
    int n,i,j,k;
    j=0;
    int array[10000];
    printf("Enter the number:");
    scanf("%d",&n);

        for (i = 1; i < n; i++) {
            if (isprime(i) == 1) {
                array[j] = i;
                j = j + 1;
            }
        }

    printf("The array is:");
    for(k=0;k<j;k++){
        printf("%d ",array[k]);
    }
}
int isprime(int i){
    int j,n;
    n=1;
    for(j=2;j<i;j++){
        if(i%j==0)
            n=n+1;
    }
    return n;
}
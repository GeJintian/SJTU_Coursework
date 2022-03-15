//
// Created by 69009 on 2017/11/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(a,b){a^=b;b^=a;a^=b;}
unsigned long int mult(unsigned long a,unsigned long int b);
void ex6(){
    unsigned long int a,b;                                                                   //set two numbers
    srand(time(NULL));                                                                        //cancel the basis of rand(),which makes the rand() different each time.
#ifndef TEST                                                                                  //if not define TEST, go through the common program
    a=rand();b=rand();                                                                        //get two random numbers
    printf("%ld*%ld=%ld %ld\n",a,b,mult(a,b),RAND_MAX);                                    //print the result
#endif
#ifdef TEST                                                                                    //if define TEST, go through a test
    int i;                                                                                    //declare a integer i
    for(i=0;i<1000000;i++){                                                                   //go through a loop of i
    a=rand();b=rand();                                                                        //get two random numbers
    if(mult(a,b)!=a*b){                                                                       //judge whether the function mult work properly
    fprintf(stderr."Error(%d):a=%ld,b=%ld,a*b=%ld,k(a,b)=%ld\n",i,a,b,a*b,mult(a,b));    //printf the result
    exit(-1);}    //proivde a method to judge whether this test work properly
    }
#endif
}
unsigned long int mult(unsigned long int a,unsigned long int b){
    int i,n,N;                                                                              //declare three integers
    unsigned long int x0,y0,z0,z1=1;                                                      //declare three unsigned long integers
    if(a<b) SWAP(a,b);                                                                     //makes a always greater than b
    if(b==0) return 0;                                                                     //provide a method to get out of this loop
    for(n=-1,i=1;i<=b;i<<=1,n++);                                                          //get into a loop to find the length of b in the binary system
    for(N=n;i<=a;i<<=1,N++);                                                               //get into a loop to find the length of a in the binary system
    y0=b&((1<<n)-1);                                                                        //use '&' to adjustment y0 in binary system
    x0=a&((1<<N)-1);                                                                        //use '&' to adjustment x0 in binary system
    z0=mult(x0,y0);                                                                         //use interation to calculate mult,this time, use x0 instead of a and y0 instead of b
    i=N+n;                                                                                  //calculate the sum of n and N, in order to get the final result
    return((z1<<i)+(x0<<n)+(y0<<N)+z0);                                                     //get the result of mult,where z0 is the result of a interation
}
//this function is to replace: for(n=-1,i=1;i<=b;i<<=1,n++)
/*void count(int b，int*ip,int*np){
      int n,i;
      n=0;
      while(b!=1){
      b>>=1;
      n=n+1;
                  }

     i=1<<n+1;
     *ip=i;*np=n;
 }*/
//To use this function, please replace as: count(b,&i,&n);
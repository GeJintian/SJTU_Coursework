#include <stdio.h>
#include <ctype.h>
//
// Created by 69009 on 2017/11/12.
//
int count(char*a,char*b);
void ex4(){
    int sum;
    char a[150];
    char b[10];
    printf("Enter the sentence:");
    gets(a);
    fflush(stdin);
    printf("Enter the word:");
    gets(b);
    sum=count(a,b);
    printf("The word '%s' occurs %d times.\n",b,sum);
}
int count(char*a, char*b){
    int sum=0;
    char*tempa=a;
    char*tempb=b;
    while(*a!='\0'){
        if(*a==*b){
            tempa=a;
            for(;*a!=0&&*b!=0;a++,b++){
                if(*b!=*a)
                    break;
                if(*(b+1)=='\0'&&(*(a+1)==0||*(a+1)=='\0'||ispunct(*(a+1))!=0))
                    sum++;
            }
            a=tempa;
            b=tempb;
        }
        a++;
    }
    return sum;
}

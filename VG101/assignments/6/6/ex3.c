#include <stdio.h>
#include <ctype.h>
//
// Created by 69009 on 2017/11/17.
//
int count(char*a,char*b);
void ex3(){
    char sentence[100];
    char word[10];
    int a;
    FILE*fp1;
    fp1=fopen("../data/sentence.txt","r");
    FILE*fp2;
    fp2=fopen("../data/word.txt","r");
    if(fp1==NULL){
        printf("Can not open.");
    }
    if(fp2==NULL){
        printf("Can not open.");
    }
    fgets(sentence,101,fp1);
    fscanf(fp2,"%s",word);
    fclose(fp1);
    fclose(fp2);
    a=count(sentence,word);
    FILE*fp3;
    fp3=fopen("../data/count.txt","w");
    fprintf(fp3,"%d",a);
    fclose(fp3);
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
                if(*(b+1)=='\0')
                    sum++;
            }
            a=tempa;
            b=tempb;
        }
        a++;
    }
    return sum;
}

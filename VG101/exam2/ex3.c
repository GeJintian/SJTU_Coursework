#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Created by 69009 on 2017/11/23.
//
void random();
void randb();
int test(int a[]);
int read();
int find(int a[]);
void ex3(){
    int n;
    printf("Enter the integer:");
    scanf("%d",&n);
    srand(time(NULL));
    int*b=malloc(n*sizeof(int));
    int i;
    for(i=0;i<n;i++){
        b[i]=rand();
    }
    int k;
    k=rand()%n;
    int*a=malloc(n*sizeof(int));
 i=0;
    if(k==0){
        a[i]=rand();
    }
    else{
        for(i=0;i<=k;i++){
            a[i]=rand();
            while(a[i]<a[i-1]){
                a[i]=rand();
            }}
    }
    for(i=k+1;i<n;i++){
        a[i]=rand()%(a[i-1]+1);
    }
    if(test(b)==0){
        printf("%d",find(b));
    }
    if(test(a==0)){
        printf("%d",find(a));
    }

}
void random(){
    int n;
    printf("Enter the integer:");
    scanf("%d",&n);
    srand(time(NULL));
    int i;
    for(i=0;i<n;i++){
        printf("%d ",rand());
    }
}
void randb(){
    printf("Enter the integer:");
    int n;
    scanf("%d",&n);
    srand(time(NULL));
    int k;
    k=rand()%n;
    int*a=malloc(n*sizeof(int));
    int i=0;
    if(k==0){
        a[i]=rand();
    }
    else{
    for(i=0;i<=k;i++){
        a[i]=rand();
        while(a[i]<a[i-1]){
            a[i]=rand();
        }}
    }
    for(i=k+1;i<n;i++){
        a[i]=rand()%(a[i-1]+1);
        }
    }

int test(int a[]){
    int b;
    b=sizeof(a);
    int i=0;
    while(i<b-1){
        if(a[i]>a[i+1])break;
        i++;
    }
    if(i==b-2){return 0;}
    else{
        while(i<b-1){
            if(a[i]<a[i+1]){return 1;}
            else{return 0;}
        }
    }
}
int read(){
    printf("Enter 1 if reading and 2 if writing.\n");
    int n;
    scanf("%d",&n);
    FILE*fp1;
    if(n==1){
    fp1=fopen("../data/sequence","r");}
    if(n==2){
        fp1=fopen("../data/sequence","w");
    }
    if(fp1==NULL){
        return 1;
    }
    else{
        char a[100];
        int b=1;
        int i;
        fgets(a,101,fp1);
        char*temp=a;
        while(*temp!='\0'){
            if(*temp==0){
                b=b+1;
            }
            temp++;
        }
        rewind(fp1);
        int* sequence=malloc(b*sizeof(int));
        for(i=0;i<b;i++){
            fscanf(fp1,"%d",sequence[i]);
        }
        fclose(fp1);
        return 0;}


}
int find(int a[]){
    int b;
    b=sizeof(a);
    int i;int k=a[0];int c=0;
    for(i=1;i<b;i++){
        if(k<a[i]){k=a[i];c=i;}
    }
    return c;
}


#include <stdio.h>
#include <malloc.h>

//
// Created by 69009 on 2017/11/17.
//
void ex4(){
    FILE*fp1;
    fp1=fopen("../data/matrices.txt","r");
    char a[100];
    int n=1;
    fgets(a,101,fp1);
    char*temp=a;
    while(*temp!='\0'){
        if(*temp==0){
            n=n+1;
        }
        temp++;
    }
    rewind(fp1);
    int**A=malloc(n*sizeof(int*));
    A[n]=malloc(n*sizeof(int));
    int**B=malloc(n*sizeof(int*));
    B[n]=malloc(n*sizeof(int));
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fscanf(fp1,"%d",&A[i][j]);
        }
    }
    i=j=0;
    for(;i<n;i++){
        for(;j<n;j++){
            fscanf(fp1,"%d",&B[i][j]);
        }
    }
    fclose(fp1);
    int**S=malloc(n*sizeof(int*));
    S[n]=malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            S[i][j]=A[i][j]+B[i][j];
        }
    }
    int**P=malloc(n*sizeof(int*));
    P[n]=malloc(n*sizeof(int));
    int m,s;
    s=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(m=0;m<n;m++){
                s=s+A[i][m]+B[m][j];
            }
            P[i][j]=s;
        }
    }
    int**AT=malloc(n*sizeof(int*));
    AT[n]=malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            AT[i][j]=AT[j][i];
        }
    }
    int**BT=malloc(n*sizeof(int*));
    BT[n]=malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            BT[i][j]=BT[j][i];
        }
    }
    int**PT=malloc(n*sizeof(int*));
    PT[n]=malloc(n*sizeof(int));
    s=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(m=0;m<n;m++){
                s=s+AT[i][m]+BT[m][j];
            }
            PT[i][j]=s;
        }
    }
    FILE*fp2;
    fp2=fopen("../data/result.txt","r");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fprintf(fp2,"%d ",S[i][j]);
        }
        fprintf(fp2,"\n");
    }
    fprintf(fp2,"\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fprintf(fp2,"%d ",P[i][j]);
        }
        fprintf(fp2,"\n");
    }
    fprintf(fp2,"\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fprintf(fp2,"%d ",PT[i][j]);
        }
        fprintf(fp2,"\n");
    }
    fclose(fp2);
}

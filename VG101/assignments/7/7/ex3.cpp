#include <cstdio>

//
// Created by 69009 on 2017/11/29.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void ex3(){
    ifstream fp3("../data/matrices.txt");
    string a;
    int n=1;
    getline(fp3,a);
    int f=0;
    while(a[f]!='\0'){
        if(a[f]==' '){
            n=n+1;
        }
        f++;
    }
    fp3.close();
    ifstream fp1("../data/matrices.txt");
    int A[n][n];
    int B[n][n];
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fp1>>A[i][j];
        }
    }
    i=j=0;
    for(;i<n;i++){
        for(;j<n;j++){
            fp1>>B[i][j];
        }
    }
    fp1.close();
    int S[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            S[i][j]=A[i][j]+B[i][j];
        }
    }
    int P[n][n];
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
    int AT[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            AT[i][j]=AT[j][i];
        }
    }
    int BT[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            BT[i][j]=BT[j][i];
        }
    }
    int PT[n][n];
    s=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(m=0;m<n;m++){
                s=s+AT[i][m]+BT[m][j];
            }
            PT[i][j]=s;
        }
    }
    ofstream fp2("../data/result.txt");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fp2<<S[i][j]<<" ";
        }
        fp2<<endl;
    }
    fp2<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fp2<<P[i][j]<<" ";
        }
        fp2<<endl;
    }
    fp2<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fp2<<PT[i][j]<<" ";
        }
        fp2<<endl;
    }
    fp2.close();
}

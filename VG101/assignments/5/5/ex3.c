

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void deck(int i);
int random(int j,int*array);
void ex3(){
    int i,k;
    for(i=1;i<=52;i++)deck(i);
    printf("Please press 'ENTER'");
    getchar();
    int j,samenumber, num, Arr[52];
    int search;
    srand( time(NULL));
    samenumber = 0;
    while(samenumber < 52){

        num = rand()%52 + 1;


        search = 0;
        for(i=0; i<samenumber; ++i){
            if(Arr[i]==num) {
                search = 1;
                break;
            }
        }

        if(search==0) {
            Arr[samenumber]=num;
            ++samenumber;
        }
    }
    for(k=0;k<52;k++){
        deck(Arr[k]);
    }
    printf("Please press 'ENTER'");
    getchar();
    int m,n,temp,l;
    for(m=0;m<52;m++){
        for(n=0;n<52;n++){
          if(Arr[m]<Arr[n]){
              temp=Arr[m];
              Arr[m]=Arr[n];
              Arr[n]=temp;
          }
        }
    }
    for(l=0;l<52;l++){
        deck(Arr[l]);
    }
    }


void deck(int i){
    if (i<=12 && i>=0) {
        if (i==9) {
            printf("Spades Jack\n");
        }
        else if (i==10) {
            printf("Spades Queen\n");
        }
        else if (i==11) {
            printf("Spades King\n");
        }
        else if (i==12) {
            printf("Spades Ace\n");
        }
        else {
            printf("Spades %d\n",i+2);
        }
    }
    else if (i<=25 && i>=13) {
        if (i==22) {
            printf("Hearts Jack\n");
        }
        else if (i==23) {
            printf("Hearts Queen\n");
        }
        else if (i==24) {
            printf("Hearts King\n");
        }
        else if (i==25) {
            printf("Hearts Ace\n");
        }
        else {
            printf("Hearts %d\n",i-11);
        }
    }
    if (i<=38 && i>=26) {
        if (i==35) {
            printf("Diamonds Jack\n");
        }
        else if (i==36) {
            printf("Diamonds Queen\n");
        }
        else if (i==37) {
            printf("Diamonds King\n");
        }
        else if (i==38) {
            printf("Diamonds Ace\n");
        }
        else {
            printf("Diamonds %d\n",i-24);
        }
    }
    if (i<=51 && i>=39) {
        if (i==48) {
            printf("Clubs Jack\n");
        }
        else if (i==49) {
            printf("Clubs Queen\n");
        }
        else if (i==50) {
            printf("Clubs King\n");
        }
        else if (i==51) {
            printf("Clubs Ace\n");
        }
        else {
            printf("Clubs %d\n",i-37);
        }
    }

}



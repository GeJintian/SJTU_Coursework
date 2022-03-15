#include <stdio.h>
#include <mem.h>

//
// Created by 69009 on 2017/11/12.
//
void ex2(){
    int month,i;
    char date[40];
    int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    printf("Enter the month: ");
    scanf("%d",&month);
    getchar();
    printf("Enter the day:");
    scanf("%s",date);
    if(strcmp(date,"Monday")==0) {
        for (i = 1; i <= mon[month-1]; i++) {
            if (i % 7 == 1)
                printf("%d Monday\n", i);
            if (i % 7 == 2)
                printf("%d Tuesday\n", i);
            if (i % 7 == 3)
                printf("%d Wednesday\n", i);
            if (i % 7 == 4)
                printf("%d Tursday\n", i);
            if (i % 7 == 5)
                printf("%d Friday\n", i);
            if (i % 7 == 6)
                printf("%d Saturday\n", i);
            if(i % 7 == 0)
            printf("%d Sunday\n", i);
        }
    }
    if(strcmp(date,"Tuesday")==0){
            for(i=1;i<=mon[month-1];i++){
                if(i%7==1)
                    printf("%d Tuesday\n",i);
                else if(i%7==2)
                    printf("%d Wednesday\n",i);
                else if(i%7==3)
                    printf("%d Thursday\n",i);
                else if(i%7==4)
                    printf("%d Friday\n",i);
                else if(i%7==5)
                    printf("%d Saturday\n",i);
                else if(i%7==6)
                    printf("%d Sunday\n",i);
                else if(i%7==0)
                    printf("%d Monday\n",i);
            }
    }
    if(strcmp(date,"Wednesday")==0) {
        for (i = 1; i <= mon[month-1]; i++) {
            if (i % 7 == 1)
                printf("%d Wednesday\n", i);
            else if (i % 7 == 2)
                printf("%d Thursday\n", i);
            else if (i % 7 == 3)
                printf("%d Friday\n", i);
            else if (i % 7 == 4)
                printf("%d Saturday\n", i);
            else if (i % 7 == 5)
                printf("%d Sunday\n", i);
            else if (i % 7 == 6)
                printf("%d Monday\n", i);
            else if (i % 7 == 0)
                printf("%d Tuesday\n", i);
        }
    }
    if(strcmp(date,"Thursday")==0) {
        for (i = 1; i <= mon[month-1]; i++) {
            if (i % 7 == 1)
                printf("%d Thursday\n", i);
            else if (i % 7 == 2)
                printf("%d Friday\n", i);
            else if (i % 7 == 3)
                printf("%d Saturday\n", i);
            else if (i % 7 == 4)
                printf("%d Sunday\n", i);
            else if (i % 7 == 5)
                printf("%d Monday\n", i);
            else if (i % 7 == 6)
                printf("%d Tuesday\n", i);
            else if (i % 7 == 0)
                printf("%d Wednesday\n", i);
        }
    }
    if(strcmp(date,"Friday")==0) {
        for (i = 1; i <= mon[month-1]; i++) {
            if (i % 7 == 1)
                printf("%d Friday\n", i);
            else if (i % 7 == 2)
                printf("%d Saturday\n", i);
            else if (i % 7 == 3)
                printf("%d Sunday\n", i);
            else if (i % 7 == 4)
                printf("%d Monday\n", i);
            else if (i % 7 == 5)
                printf("%d Tuesday\n", i);
            else if (i % 7 == 6)
                printf("%d Wednesday\n", i);
            else if (i % 7 == 0)
                printf("%d Thursday\n", i);
        }
    }
    if(strcmp(date,"Saturday")==0) {
        for (i = 1; i <= mon[month-1]; i++) {
            if (i % 7 == 1)
                printf("%d Saturday\n", i);
            else if (i % 7 == 2)
                printf("%d Sunday\n", i);
            else if (i % 7 == 3)
                printf("%d Monday\n", i);
            else if (i % 7 == 4)
                printf("%d Tuesday\n", i);
            else if (i % 7 == 5)
                printf("%d Wednesday\n", i);
            else if (i % 7 == 6)
                printf("%d Thursday\n", i);
            else if (i % 7 == 0)
                printf("%d Friday\n", i);
        }
    }
    if(strcmp(date,"Sunday")==0) {
        for (i = 1; i <= mon[month-1]; i++) {
            if (i % 7 == 1)
                printf("%d Sunday\n", i);
            else if (i % 7 == 2)
                printf("%d Monday\n", i);
            else if (i % 7 == 3)
                printf("%d Tuesday\n", i);
            else if (i % 7 == 4)
                printf("%d Wednesday\n", i);
            else if (i % 7 == 5)
                printf("%d Thursday\n", i);
            else if (i % 7 == 6)
                printf("%d Friday\n", i);
            else if (i % 7 == 0)
                printf("%d Saturday\n", i);
        }
    }

}

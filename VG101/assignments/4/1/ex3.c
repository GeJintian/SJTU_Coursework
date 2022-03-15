#include <stdio.h>

//
// Created by 69009 on 2017/11/2.
//
void question1();
void question2();
void ex3(){
    int choice;
    printf("There are two funcions:\nquestion1 can tell whether the letter input is a vowel or a consonant\nquestion2 can print the common data type whose size are equal to what you input\n");
    printf("If you want to run question1, please enter 1; if you want to run question2, please enter 2 :");
    scanf("%d",&choice);
    if(choice==1)
        question1();
    else if(choice==2)
        question2();
}
void question1(){
    char b;
    printf("please enter a letter:");
    getchar();
    scanf("%c",&b);
    if(b=='a'||b=='e'||b=='i'||b=='o'||b=='u')
        printf("This letter is a vowel.\n");
    else
        printf("This letter is a consonant.\n");
}
void question2(){
    int number;
    char letter;
    printf("Please enter a number and a letter, the letter should be b or B, which represent bit and byte: ");
    scanf("%d %c",&number,&letter);
    if(letter=='B'){
        if(number==1)
            printf("char\n");
        if(number==2)
            printf("short\n");
        if(number==4){
            printf("int\n");
            printf("long\n");
            printf("float\n");
        }
        if(number==8)
            printf("double\n");
    }
    if(letter=='b'){
        if(number==8)
            printf("char\n");
        if(number==16)
            printf("short\n");
        if(number==32){
            printf("int\n");
            printf("long\n");
            printf("float\n");
        }
        if(number==64)
            printf("double\n");
    }
}
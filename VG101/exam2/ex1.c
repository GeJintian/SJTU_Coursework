#include <stdio.h>
#include <stdlib.h>

//
// Created by 69009 on 2017/11/23.
//
typedef struct node{ char*name; struct node *next; } node_t;
void ex1(){
    printf("enter the m andn:");
    int m,n;
    scanf("%d %d",&m,&n);
    node_t *head;
    head=(node_t*)calloc(1,sizeof(node_t));
    if(head==NULL){ fprintf(stderr,"Failed to assign memory!\n"); exit(-1); }
    head->next=NULL; head->name="Ram";
    int i;
    for(i=0;i<m;i++){

    }
}
int count(node_t **head) {
    node_t *tmp=NULL;
    node_t *pHead=*head;
    int i;i=1;
    while(pHead->next!=NULL) {
        tmp=pHead;
        pHead=pHead->next;
        i=i+1;
    }
return i;
}

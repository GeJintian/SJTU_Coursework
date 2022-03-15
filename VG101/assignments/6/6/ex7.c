//
// Created by 69009 on 2017/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void ex7() {
    node_t *a=Initialize('1'); node_t *b=NULL; PrintList(a);
    InsertFirstList(&a, 'V'); InsertFirstList(&a, 'M');
    PrintList(a); InsertLastList(&a, 'C'); PrintList(a);
    SplitList(&a, &b, 2); PrintList(a); PrintList(b);
    DeleteFirstList(&a); PrintList(a); InsertLastList(&a, 'G');
    DeleteLastList(&b); PrintList(b); InsertLastList(&b,'0');
    PrintList(b); InsertLastList(&b, '1'); PrintList(b);
    MergeList(&a,&b); PrintList(a);
    char target='G';
    printf("Count '%c': %d\n",target, SearchList(&a,target));
    target='1';
    printf("Count '%c': %d\n",target, SearchList(&a,target));
    FreeList(&a);
}

node_t *Initialize(char ch) {
    node_t *head;
    head=(node_t*)calloc(1,sizeof(node_t));
    if(head==NULL){ fprintf(stderr,"Failed to assign memory!\n"); exit(-1); }
    head->next=NULL; head->ch=ch;
    return head;
}

void PrintList(node_t *head) {
    node_t *temp=head;
    printf("***Print Linked List***\n");
    while(temp!=NULL) { printf("%c ",temp->ch); temp=temp->next; }
    printf("\n****Print Finished****\n\n");
}

void FreeList(node_t **head) {
    node_t *tmp=NULL; node_t *pHead=*head;
    while(pHead->next!=NULL) { tmp=pHead; pHead=pHead->next; free(tmp); }
    free(pHead);
}

void InsertFirstList(node_t **head,char insert_char) {
    node_t *head1;
    head1=(node_t*)calloc(1,sizeof(node_t));
    if(head1==NULL){
        fprintf(stderr,"Failed to assign memory!\n");
        exit(-1);
    }
    head1->next=*head;
    head1->ch=insert_char;
    *head=head1;


}

void InsertLastList(node_t **head,char insert_char) {
    node_t *head1;
    head1=(node_t*)calloc(1,sizeof(node_t));
    if(head1==NULL){
        fprintf(stderr,"Failed to assign memory!\n");
        exit(-1);
    }
    head1->next=NULL;
    head1->ch=insert_char;
    node_t *temp=*head;
    node_t *temp_pre=NULL;
    while(temp!=NULL) {
        temp_pre=temp;
        temp=temp->next;
    }
    temp_pre->next=head1;


}

void DeleteFirstList(node_t **head) {
    node_t *tmp=(*head);
    *(head)=(*head)->next;
    free(tmp);
}

void DeleteLastList(node_t **head) {
    node_t *tmp=NULL;
    node_t *pHead=*head;
    while(pHead->next!=NULL) {
        tmp=pHead;
        pHead=pHead->next;
    }
    free(pHead);
    tmp->next=NULL;

}

void SplitList(node_t **head, node_t **tail, int pos) {
    node_t* temp=*head;
    for(int i=0;i<pos-1;i++) {
        temp=temp->next;
    }
    *tail=temp->next;
    temp->next=NULL;
}


void MergeList(node_t **head1, node_t **head2) {
    node_t* temp1=*head1;
    while(temp1->next!=NULL) {
        temp1=temp1->next;
    }
    temp1->next=*head2;
}
int SizeList(node_t *head) {
    node_t* tmp=head;
    int sum=0;
    while(tmp!=NULL) {
        tmp=tmp->next;
        sum++;
    }
    return sum;
}

int SearchList(node_t **head, char target) {
    node_t* tmp=*head;
    int sum=0;
    while(tmp!=NULL) {
        if (tmp->ch==target) {
            sum++;
        }
        tmp=tmp->next;
    }
    return sum;
}

bool IsEmptyList(node_t *head) {
    node_t* tmp=head;

    while(tmp!=NULL) {
        if (tmp->ch!=0) {
            return false;
        }
        tmp=tmp->next;
    }
    return true;}

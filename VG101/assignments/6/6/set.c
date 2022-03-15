//
// Created by 69009 on 2017/11/21.
//

#include <stdlib.h>
#include <stdio.h>
#include "set.h"
#include "multiset.h"
void set(){
printf("The functions are in this file.");
}
void newSet(uset*set,int type){
    set->elem=malloc(INITSETSIZE*type);
    set->card=0;
    set->type=type;
}
void deletSet(uset*set){
free(set->elem);
}
/*void addElem(void*elem,uset*set){
    void*temp=set->elem;
    int a=sizeof(set->elem);
    int i=0;
    while(1){
        if(*(temp+i)==elem)break;
        i=i+1;
        if(i==a)break;
    }
    if(i==a){
        if(a*set->type==set->card){

        }
    }

}
void remElem(void*elem,uset*set){}*/
//
// Created by 69009 on 2017/11/21.
//

#ifndef INC_6_MULTISET_H
#define INC_6_MULTISET_H
#define INITSETSIZE 64
#define CHAR 1
#define INT sizeof(int)
#define DOUBLE sizeof(double)
typedef struct universalSet{void*elem;int card;int type;}uset;
void newSet(uset *set, int type);
void deletSet(uset *set);
void addElem(void *elem, uset *set);
void remElem(void *elem, uset *set);
#endif //INC_6_MULTISET_H

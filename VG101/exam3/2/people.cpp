//
// Created by 69009 on 2017/12/15.
//

#include <cstdlib>
#include <ctime>
#include "people.h"
void objects::inputstrength(int a) {
    strength=a;
}
int objects::getatta() {
    return attack;
}
int objects::getsta() {
    return stamina;
}
int objects::getstrength() {
    return strength;
}
void objects::inputattack(int a) {
    attack=a;
}
void objects::inputsta(int a) {
    stamina=a;
}
int human::getparent() {
    return parent;
}
void human::inputparent(int a) {
    parent=a;
}
void objects::fight() {
    srand(time(NULL));
    int i=rand()%10+1;
    if (i<=attack){
        n=0;
    }
    else{n=1;}
}
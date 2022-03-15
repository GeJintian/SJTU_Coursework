//
// Created by 69009 on 2017/12/15.
//

#include "machine.h"
machine::machine() {
sh[0]=new Trapzium({0.1,-0.7},{0.6,-0.7},{0.4,-0.2},{0.1,-0.2});
sh[1]=new Rectanglen({-0.1,-0.7},{-0.5,-0.3});
sh[2]=new Rectanglen({-0.5,-0.3},{-0.4,0});
sh[3]=new Line({-0.5,0},{-0.6,0});
sh[4]=new Line({-0.6,0},{-0.6,0.2});
sh[5]=new Circle();
sh[6]=new Rectanglen({-1,-1},{1,1},1,1,1);
}
void machine::draw() {
    if(n=1){
        sh[5]->draw();}
    else{for(int j=0;j<5;j++){sh[j]->draw();}}
    }


void machine::turn() {
    int static i=1;
    if(i%3!=0){i++;n=1;}
    else{i++;n=0;}
}


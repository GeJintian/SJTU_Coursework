//
// Created by 69009 on 2017/12/14.
//

#ifndef INC_9_CAR_H
#define INC_9_CAR_H

#include "figures.h"

class car {
public:
    car(Point pt1={-0.75,-0.75});
    ~car();
    void draw();
    void move(double*dx);
private:
    Point p;Shape *sh[4];
    void moveleft(double*dx);
    void moveright(double*dx);
};


#endif //INC_9_CAR_H

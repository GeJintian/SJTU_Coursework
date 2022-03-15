//
// Created by 69009 on 2017/12/15.
//

#ifndef INC_1_MACHINE_H
#define INC_1_MACHINE_H

#include "figures.h"

class machine {
public:
    machine();
    void draw();
    void turn();
private:
    Shape*sh[6];int n;

};


#endif //INC_1_MACHINE_H

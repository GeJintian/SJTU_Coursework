//
// Created by 69009 on 2017/11/29.
//

#include "rectangle.h"
void rectangle::slides(float c, float d) {
    a=c;b=d;
}
void rectangle::zoom(float scale) {
    a*=scale;
    b*=scale;
}
float rectangle::aera() {
    return a*b;
}
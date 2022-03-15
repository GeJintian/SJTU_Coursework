//
// Created by 69009 on 2017/11/29.
//

#include <cmath>
#include "triangle.h"
void triangle::perimeter(float d, float e, float f) {
    a=d;
    b=e;
    c=f;
    s=1/2*(d+e+f);
}
double triangle::area() {
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
void triangle::zoom(float scale) {
    a*=scale;
    b*=scale;
    c*=scale;
}
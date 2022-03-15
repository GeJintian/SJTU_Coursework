//
// Created by 69009 on 2017/11/29.
//

#include <cstdlib>
#include <cmath>
#include "parallelogram.h"
void parallelogram::sizes(float c, float d, float e) {
    a=c;b=d;
    h=c*fabs(sin(e));
}
void parallelogram::zoom(float scale) {
    a*=scale;b*=scale;
}
float parallelogram::area() {
    return h*b;
}
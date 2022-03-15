//
// Created by 69009 on 2017/11/29.
//

#include <cmath>
#include "trapezium.h"
void trapezium::sizes(float c, float d,float e, float angle) {
    a=c;b=d;h=e*sin(angle);
}
void trapezium::zoom(float scale) {
    a*=scale;
}
float trapezium::area() {
    return (a+b)*h/2;
}
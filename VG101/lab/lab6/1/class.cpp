//
// Created by 69009 on 2017/11/29.
//

#include "class.h"

void Grade::gradeprct(int grade) {
    gradep=grade;
}
void Grade::gradelrt(char grade) {
    gradel=grade;
}
int Grade::prct() {
    return 100-(gradel-'A')*10-5;
}
char Grade::lrt() {
    return GRADES[gradep / 10];
}
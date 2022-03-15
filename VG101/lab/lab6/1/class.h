//
// Created by 69009 on 2017/11/29.
//

#ifndef INC_1_CLASS_H
#define INC_1_CLASS_H


class Grade {
public:
    void gradeprct(int grade);
    void gradelrt(char grade);
    int prct();
    char lrt();
private:
    static const char GRADES[]={'F','F','F','F','F','F','D','C','B','A','A'};
    char gradel;
    int gradep;
};


#endif //INC_1_CLASS_H

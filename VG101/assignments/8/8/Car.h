//
// Created by 69009 on 2017/12/14.
//

#ifndef INC_8_CAR_H
#define INC_8_CAR_H

class vehicle {
public:
    void ticket();void noticket();
protected:
    int timein,timeout,price,i,f;
    char*type;
};
class van:public vehicle{
public:
    van(char*t="van",int p=4,int m=1);
    void intimein(int a);
    void intimeout(int a);
    int outtimein();
    int outtimeout();
    void slot(int x);
};
class car:public vehicle{
public:
    car(char*t="car",int p=3,int m=1);
    void intimein(int a);
    void intimeout(int a);
    int outtimein();
    int outtimeout();
    void slot(int x);
};
class motorbike:public vehicle{
public:
    motorbike(char*t="motorbike",int p=2,int m=2);
    void intimein(int a);
    void intimeout(int a);
    int outtimein();
    int outtimeout();
    void slot(int x);
};
class bicycle:public vehicle{
public:
    bicycle(char*t="bicycle",int p=1,int m=2);
    void intimein(int a);
    void intimeout(int a);
    int outtimein();
    int outtimeout();
    void slot(int x);
};


#endif //INC_8_CAR_H

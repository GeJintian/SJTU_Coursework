//
// Created by 69009 on 2017/12/15.
//

#ifndef INC_2_PEOPLE_H
#define INC_2_PEOPLE_H


class objects {
public:
    void inputsta(int a);
    void inputattack(int a);
    void inputstrength(int a);
    int getsta();
    int getatta();
    int getstrength();
protected:
    int stamina,attack,strength,n;
    void fight();
};
class users:public objects{
public:
    void inputparent(int a);
    int getparent();
private:
    int parent;
};
class human:public objects{
public:

    void inputparent(int a);
    int getparent();
private:
    int parent;
};
class animal:public objects{};


#endif //INC_2_PEOPLE_H

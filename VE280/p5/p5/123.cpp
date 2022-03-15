//
// Created by 69009 on 2019/7/22.
//

#include <iostream>
#include <string>
#include "dlist_impl.h"
#include "dlist.h"
using namespace std;
void adder(Dlist<int> &ls);
void print(Dlist<int> &ls);

static bool is_number(std::string &s){
    char *p;
    const char *compare = s.c_str();
    std::strtol(s.c_str(),&p,10);
    return (p!=compare);
}
void choose(Dlist<int> &ls, bool &q, std::string &s){
    if(is_number(s)){
        int *op =new int((int)strtol(s.c_str(),nullptr,10));
        ls.insertFront(op);
    }
    else{
        if(s.size() != 1){
            cout<<"illegal input\n";
        }
        char c = s[0];
        //cout<<c<<endl;
        if(c == 'p') print(ls);
        }
}
void print(Dlist<int> &ls){
    int n = 1;
    if(ls.isEmpty())throw n;//No operand
    int *first;
    first = ls.removeFront();
    std::cout<<*first<<std::endl;
    ls.insertFront(first);
}
int main(){
    Dlist<int> ls;
    int *first = new int(1);
    int *second = new int(2);
    int *third = new int(3);
    cout<<ls.isEmpty()<<endl;
    ls.insertFront(third);
    cout<<ls.isEmpty()<<endl;
    ls.insertFront(second);
    cout<<ls.isEmpty()<<endl;
    ls.insertFront(first);
    cout<<ls.isEmpty()<<endl;
    ls.removeBack();
    cout<<ls.isEmpty()<<endl;
    ls.removeBack();
    cout<<ls.isEmpty()<<endl;
    ls.removeBack();
    cout<<ls.isEmpty()<<endl;

}

void adder(Dlist<int> &ls){
    int n = 1;
    if(ls.isEmpty())throw n;//No operand
    int *first;
    int *second;
    first = ls.removeFront();
    if(ls.isEmpty()){//Only one operand
        ls.insertFront(first);
        throw n;
    }
    second = ls.removeFront();
    int *result = new int((*first) + (*second));
    ls.insertFront(result);
    delete first;
    delete second;
}
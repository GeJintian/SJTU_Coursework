//
// Created by 69009 on 2019/7/20.
//
#include <iostream>
#include <string>
#include "dlist.h"

void adder(Dlist<int> &ls);
void substructor(Dlist<int> &ls);
void multiplier(Dlist<int> &ls);
void divider(Dlist<int> &ls);
void negate(Dlist<int> &ls);
void duplicate(Dlist<int> &ls);
void reverse(Dlist<int> &ls);
void print(Dlist<int> &ls);
void clear(Dlist<int> &ls);
void print_all(Dlist<int> &ls);
void quit(Dlist<int> &ls, bool &q);
void choose(Dlist<int> &ls, bool &q, std::string &s);
void calculator();

int main(){
    calculator();
    return 0;
}

void calculator(){
    //catch int: Not enough operands
    //catch char: Divide by zero
    //catch double: bad input
    Dlist<int> ls;
    std::string s;
    bool q = false;
    while(!q){
        std::cin>>s;
        try{
            choose(ls, q, s);
        }
        catch(double v){
            std::cout<<"Bad input\n";
        }
        catch(int v){
            std::cout<<"Not enough operands\n";
        }
        catch(char v){
            std::cout<<"Divide by zero\n";
        }
    }
}

void adder(Dlist<int> &ls){
    int n = 1;
    if(ls.isEmpty())throw n;//No operand
    int *first;
    first = ls.removeFront();
    if(ls.isEmpty()){//Only one operand
        ls.insertFront(first);
        throw n;
    }
    int *second;
    second = ls.removeFront();
    int *result = new int((*first) + (*second));
    ls.insertFront(result);
    delete first;
    delete second;
}

void substructor(Dlist<int> &ls){
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
    int *result = new int((*second) - (*first));
    ls.insertFront(result);
    delete first;
    delete second;
}

void multiplier(Dlist<int> &ls){
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
    int *result = new int((*second) * (*first));
    ls.insertFront(result);
    delete first;
    delete second;
}

void divider(Dlist<int> &ls){
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
    if(*first == 0){
        char c = '1';
        throw c;
    }
    int *result = new int((*second) / (*first));
    ls.insertFront(result);
    delete first;
    delete second;
}

void negate(Dlist<int> &ls){
    int n = 1;
    if(ls.isEmpty())throw n;//No operand
    int *first;
    first = ls.removeFront();
    int *result = new int(-1 * (*first));
    ls.insertFront(result);
    delete first;
}

void duplicate(Dlist<int> &ls){
    int n = 1;
    if(ls.isEmpty())throw n;//No operand
    int *first;
    first = ls.removeFront();
    int *first_copy = new int(*first);
    int *second_copy = new int(*first);
    ls.insertFront(first_copy);
    ls.insertFront(second_copy);
    delete first;
}

void reverse(Dlist<int> &ls){
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
    ls.insertFront(first);
    ls.insertFront(second);
}

void print(Dlist<int> &ls){
    int n = 1;
    if(ls.isEmpty())throw n;//No operand
    int *first;
    first = ls.removeFront();
    std::cout<<*first<<std::endl;
    ls.insertFront(first);
}

void clear(Dlist<int> &ls){
    ls.~Dlist();
}

static void print_all_helper(Dlist<int> &ls){
    if(ls.isEmpty()) return;
    int *first = ls.removeFront();
    std::cout<<" "<<*first;
    print_all_helper(ls);
    ls.insertFront(first);
}
void print_all(Dlist<int> &ls){
    if(ls.isEmpty()) std::cout<<std::endl;
    else{
        int *first = ls.removeFront();
        std::cout<<*first;
        print_all_helper(ls);
        std::cout<<std::endl;
        ls.insertFront(first);
    }
}

void quit(Dlist<int> &ls, bool &q){
    clear(ls);
    q = true;
}

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
            double d = 1;
            throw d;
        }
        char c = s[0];
        switch(c){
            case '+':
                adder(ls);break;
            case '-':
                substructor(ls);break;
            case '*':
                multiplier(ls);break;
            case '/':
                divider(ls);break;
            case 'n':
                negate(ls);break;
            case 'd':
                duplicate(ls);break;
            case 'r':
                reverse(ls);break;
            case 'p':
                print(ls);break;
            case 'c':
                clear(ls);break;
            case 'a':
                print_all(ls);break;
            case 'q':
                quit(ls,q);break;
            default:
                double d = 1;
                throw d;
        }
    }
}
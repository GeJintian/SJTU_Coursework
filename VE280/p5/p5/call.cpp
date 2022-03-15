//
// Created by 69009 on 2019/7/22.
//
#include <iostream>
#include <string>
#include "dlist.h"
using namespace std;

const string order_name[] = {"platinum", "gold", "silver", "regular"};
enum order_t{Platinum, Gold, Silver, Regular};
struct consumer_t{
    string o_name;
    int timestamp;
    string name;
    order_t order;
    int duration;
};

void call(Dlist<consumer_t> &ls, int n);
void answer_call(Dlist<consumer_t> &ls, const int &t, int &until_time, bool &clear,
                 Dlist<consumer_t> &platinum, Dlist<consumer_t> &gold,
                 Dlist<consumer_t> &silver,Dlist<consumer_t> &regular);
void print_call(Dlist<consumer_t> &ls, const int &t,
                Dlist<consumer_t> &platinum, Dlist<consumer_t> &gold,
                Dlist<consumer_t> &silver,Dlist<consumer_t> &regular);

int main(){
    Dlist<consumer_t> ls;
    int n;//n lines followed
    cin>>n;
    //Construct a list
    for(int i = 0; i < n; i++){
        consumer_t *op = new consumer_t;
        cin>>op->timestamp>>op->name>>op->o_name>>op->duration;
        for(int j = 0; j < 4; j++){
            if(op->o_name == order_name[j]){
                op->order = (order_t)j;
                break;
            }
        }
        ls.insertBack(op);
    }
    call(ls,n);
    return 0;
}

void call(Dlist<consumer_t> &ls, int n){
    int time = 0;//initialize time
    string consumer_name;//represent the present consumer whom the agent is answering to
    int until_time = time;//until this time the agent is free again
    bool clear = false;
    Dlist<consumer_t> platinum;
    Dlist<consumer_t> gold;
    Dlist<consumer_t> silver;
    Dlist<consumer_t> regular;
    while(!clear){
        cout<<"Starting tick #"<<time<<endl;
        print_call(ls, time, platinum, gold, silver, regular);
        answer_call(ls,time,until_time,clear,platinum,gold,silver,regular);
        time ++;
    }
    platinum.~Dlist();
    gold.~Dlist();
    silver.~Dlist();
    regular.~Dlist();
    ls.~Dlist();
}

static void print_call_helper(Dlist<consumer_t> &ls, const int &t,
                              Dlist<consumer_t> &platinum, Dlist<consumer_t> &gold,
                              Dlist<consumer_t> &silver,Dlist<consumer_t> &regular){
    if(ls.isEmpty()) return;
    else{
        consumer_t *first = ls.removeFront();
        if(first->timestamp == t) {
            cout << "Call from " << first->name << " a " << first->o_name << " member\n";
            switch(first->order){
                case Platinum:
                    platinum.insertBack(first);
                    break;
                case Gold:
                    gold.insertBack(first);
                    break;
                case Silver:
                    silver.insertBack(first);
                    break;
                case Regular:
                    regular.insertBack(first);
                    break;
                default:
                    cout<<"no order_t";
                    break;
            }
        }
        print_call_helper(ls,t,platinum,gold,silver,regular);
        if(first->timestamp != t)ls.insertFront(first);
    }
}
void print_call(Dlist<consumer_t> &ls, const int &t,
                Dlist<consumer_t> &platinum, Dlist<consumer_t> &gold,
                Dlist<consumer_t> &silver,Dlist<consumer_t> &regular){
    print_call_helper(ls, t,platinum,gold,silver,regular);
}

void answer_call(Dlist<consumer_t> &ls, const int &t, int &until_time, bool &clear,
                 Dlist<consumer_t> &platinum, Dlist<consumer_t> &gold,
                 Dlist<consumer_t> &silver,Dlist<consumer_t> &regular){
    if(until_time == t){
        if (platinum.isEmpty() && gold.isEmpty() && silver.isEmpty() && regular.isEmpty() && ls.isEmpty()) {
            clear = true;
            return;
        }
    }
    if(t == until_time) {
        if(!platinum.isEmpty()){
            consumer_t *first = platinum.removeFront();
            cout<<"Answering call from "<<first->name<<endl;
            until_time += first->duration;
            delete first;
        }
        else if(!gold.isEmpty()){
            consumer_t *first = gold.removeFront();
            cout<<"Answering call from "<<first->name<<endl;
            until_time += first->duration;
            delete first;
        }
        else if(!silver.isEmpty()){
            consumer_t *first = silver.removeFront();
            cout<<"Answering call from "<<first->name<<endl;
            until_time += first->duration;
            delete first;
        }
        else if(!regular.isEmpty()){
            consumer_t *first = regular.removeFront();
            cout<<"Answering call from "<<first->name<<endl;
            until_time += first->duration;
            delete first;
        }
        else until_time ++;
    }

}
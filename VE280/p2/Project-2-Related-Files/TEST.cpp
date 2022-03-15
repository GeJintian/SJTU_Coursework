//
// Created by 69009 on 2019/6/2.
//
#include <iostream>
#include "recursive.h"
#include "p2.h"
using namespace std;

bool odd(int a)
{
    if(a%2 == 1) return true;
    else return false;
}
int main(){
    /*int a;
    cin>>a;
    tree_t start = tree_make(2,
                             tree_make(1, tree_make(), tree_make()),
                             tree_make(4, tree_make(), tree_make(3, tree_make(), tree_make())));
    tree_t end = tree_make(2,
                           tree_make(1, tree_make(
                                   5,tree_make(),tree_make()
                                   ), tree_make(

                                           )),
                           tree_make(1,
                                     tree_make(),
                                     tree_make(3, tree_make(), tree_make())));*/
    /*int i;
    list_t listA, listA_answer;
    list_t listB, listB_answer;

    listA = list_make();
    listB = list_make();
    listA_answer = list_make();
    listB_answer = list_make();

    //listA = list_make(1, listA);
    for(i = 5; i>0; i--)
    {
        listA = list_make(i, listA);
        listA_answer = list_make(6-i, listA_answer);
        listB = list_make(i+10, listB);
        listB_answer = list_make(i+10, listB_answer);
    }

    for(i = 5; i>0; i--)
    {
        listB_answer = list_make(i, listB_answer);
    }*/
    tree_t test2 = tree_make(4,
                             tree_make(5, tree_make(), tree_make(6, tree_make(), tree_make())),
                             tree_make(1,
                                       tree_make(3, tree_make(), tree_make()),
                                       tree_make(6,tree_make(3, tree_make(), tree_make()), tree_make())));




    //list_print(traversal(end));
    //cout<<depth(start);
    cout<<tree_hasMonotonicPath(test2);
    cout << endl;




}

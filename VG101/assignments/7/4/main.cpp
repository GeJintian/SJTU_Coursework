#include <iostream>
using namespace std;
int calculate(int a){
    if(a%2==0){
        a=a/2;
    }
    else{a=3*a+1;}
    return a;
}
void function1(){
    cout<<"Enter the first number a: ";
    int a;
    cin>>a;
    int i=0;
    while(a!=1){
        a=calculate(a);i++;
    }
    cout<<"N="<<i;
}
void function2(){
    cout<<"Enter the max value M:";
    int M;
    cin>>M;
    if(M%2==0){cout<<M-1;}
    else{cout<<M;}
}
int main() {
    cout<<"If you want to run function 1, enter 2;otherwise enter 2 : ";
    int n;
    cin>>n;
    if(n==1){
function1();
    }
    else{function2();}
}

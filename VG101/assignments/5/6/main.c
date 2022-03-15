#include <stdio.h>

void main(){
    int i,n,b;
    i=2,n=-1;
    b=5;
    while(i^b!=0){
        i<<=1,n++;
    }
    printf("%d %d\n",i,n);
    for(n=-1,i=2;i<=b;i<<=1,n++);
    printf("%d %d\n",i,n);
}

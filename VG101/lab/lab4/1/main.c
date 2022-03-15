#include <stdio.h>
#include <stdlib.h>

void condition(int n);
int main(){
    int r,n;
    printf("Enter the bound: ");
    scanf("%d",&r);
    n=rand()%r;
    condition(n);
}
void condition(int n){
    int guess;
    printf("Enter the number which you guess: ");
    scanf("%d",&guess);
    if(guess<n){
        printf("small\n");
        condition(n);
    }
    if(guess>n){
        printf("large\n");
        condition(n);
    }
    if(guess==n){
        printf("win");
    }
}
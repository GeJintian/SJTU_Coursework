#include <stdio.h>
#include <mem.h>

void replace(char*sentence);
void delete(char*sentence);
int main(){
    char sentence[100];
    int a;
    printf("Input a string: ");
    gets(sentence);
    printf("* Choose 1 to replace a character or 2 to delete a character: ");
    scanf("%d",&a);getchar();
    if(a==1){
        replace(sentence);
    }
    if(a==2){
        delete(sentence);
    }
}
void replace(char*sentence){
    char b;
    char c;
    int i=0;
    printf("Replace character: ");
    scanf("%c",&b);
    getchar();
    printf("with: ");
    scanf("%c",&c);
    while(sentence[i]!='\0'){
        if(sentence[i]==b) {
            sentence[i] = c;
        }
        i=i+1;
    }
    printf("New string: %s\n",sentence);
}
void delete(char*sentence){
    char b;
    printf("Delete the character:");
    scanf("%c",&b);
    int i,k;
    i=0;
    while(sentence[i]!='\0'){
        if(sentence[i]==b){
            for(k=i;sentence[k]!='\0';k++){
                memmove(sentence+k,sentence+k+1,1);
            }
        }
        else{i=i+1;}
    }
printf("The new string: %s",sentence);
}
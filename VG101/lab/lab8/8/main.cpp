#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stack>

using namespace std;
void funvector(){
    string str;
    cout<<"Please enter a string: ";
    getline(cin,str);
    vector <char> vectchar;
    int i,j;
    j=str.length();
    for(i=0;i<j;i++){vectchar.push_back(str[i]);}
    vector<char>::iterator iter;
    for( iter = vectchar.end()-1; iter != vectchar.begin()-1; iter-- )
    {
        cout << *iter ;
    }
}
void funarray(){
    char str[100];
    cout<<"Please enter a string: ";
    gets(str);
    char*temp=str;
    int i;
    for(i=0;*(temp+i)!='\0';i++);
    i=i-1;
    for(;i>=0;i--){
        cout<<str[i];
    }
}
void funstack(){
    string str;
    cout<<"Please enter the number: ";
    getline(cin,str);
    stack<char>stachar;
    int i;
    for(i=0;i<str.length();i++){
        stachar.push(str[i]);
    }
    for(;i>0;i--){
        cout<<stachar.top();
        stachar.pop();
    }
}
int main(){
    int n;
    cout<<"If you want to use array, please input 1,if vecotr,please input 2,if stack,please 3 : ";
    cin>>n;
    cin.get();
    if(n==1){funarray();}
    if(n==2){funvector();}
    if(n==3){funstack();}
}
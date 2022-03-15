#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>

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
    for( iter = vectchar.begin(); iter != vectchar.end(); iter++ )
    {
        cout << *iter ;
    }
}
void funarray(){
    char str[100];
    cout<<"Please enter a string: ";
    gets(str);
    char*temp=str;
    int i,j;
    for(i=0;*(temp+i)!='\0';i++);
    for(j=0;j<i;j++){
        cout<<str[j];
    }
}
void funqueue(){
    string str;
    cout<<"Please enter a string: ";
    getline(cin,str);
    queue<char>quechar;
    int i;
    for(i=0;i<str.length();i++){
        quechar.push(str[i]);
    }
    for(;i>0;i--){
        cout<<quechar.front();
        quechar.pop();
    }
}
int main(){
    int n;
    cout<<"If you want to use array, please input 1,if vecotr,please input 2,if queue,please 3 : ";
    cin>>n;
    cin.get();
    if(n==1){funarray();}
    if(n==2){funvector();}
    if(n==3){funqueue();}
}
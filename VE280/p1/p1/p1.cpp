#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
int Digit(int a);
int Triangle_Test(int a);
int Palindrome_Test(int a);
int Odious_Test(int a);
int Extravagant_Test(int a);

int main()
{
 int a;
 int b;
 cout<<"Please enter the integer and the test number: ";
 cin>>a>>b;
 //Check whether the input is legal
 while(a<1 || a>10000000 || b<1 || b>4)
 {
  cout<<"Please enter the integer and the test number: ";
  cin>>a>>b;
 }
 //Verify the type that we are supposed to check
 if(b == 1)
 {
  cout<<Triangle_Test(a);
 }
 else if(b == 2)
 {
  cout<<Palindrome_Test(a);
 }
 else if(b == 3)
 {
  cout<<Odious_Test(a);
 }
 else
 {
  cout<<Extravagant_Test(a);
 }
 return 0;
}


int Triangle_Test(int a)
//REQUIRES: a > 1;
//EFFECTS: check whether a is a triangle number. Return 1 if true, 0 otherwise
{
 double b1;
 b1 = (-1+sqrt(1+8*a))/2;
 int b11,b12;
 b11 = floor(b1);
 b12 = ceil(b1);
 float c11;
 float c12;
 c11 = b11*(b11+1)/2;
 c12 = b12*(b12+1)/2;
 if(c11 == a || c12 == a)
  {
   return 1;
  }
 else
  {
   return 0;
  }
}


int Palindrome_Test(int a)
//REQUIRES: a > 1;
//EFFECTS: Check whether a is a palidrome number. Return 1 if true, 0 otherwise.
{
 int length;
 length = Digit(a);

//Divide a into a array
 int b[length];
 int i=0;
 while(a/10!=0)
 {
  b[i] = a/pow(10,length-i-1);
  a = a%((int)pow(10,length-i-1));
  i++;
 }
 b[i] = a;

//Read the array from head and from tail and check whether they are the same
 int symmetric_number;
 symmetric_number = floor(length/2);
 int head[symmetric_number];
 int tail[symmetric_number];
 for(int i = 0;i<symmetric_number;i++)
 {
  head[i] = b[i];
 }
 for(int j = 0;j<symmetric_number;j++)
 {
  tail[j] = b[length-j-1];
 }
 int count = 0;
 for(int i = 0;i<symmetric_number;i++)
 {
  if(head[i]==tail[i])
  {
   count++;
  }
 }
 if(count == symmetric_number)
 {
  return 1;
 }
 else
 {
  return 0;
 }
}



int Odious_Test(int a)
//REQUIRES: a > 1;
//EFFECTS: Check whether a is a Odious number. Return 1 if true, 0 otherwise.
{
 int i=0;
 int d;
 int count=0;
 while(a!=0)
 {
  d = a%2;
  a/=2;
  count = count + d;
  i++;
 }
 if(count%2!=0)
 {
  return 1;
 }
 else
 {
  return 0;
 }
}


int Extravagant_Test(int a)
//REQUIRES: a > 1;
//EFFECTS: Check whether a is a extravagant number. Return 1 if true, 0 otherwise.
{
 int leno;
 leno = Digit(a);

 int i = 2;
 int j = 0;
 int temp = a;
 int count2 = 1;
 int count1 = 0;
 while(temp!=1)
 {
  if(temp%i == 0/*a factor*/)
  {
   temp = temp/i;
   if(i==j/*not a new factor*/)
   {
    count2++;
   }
   else/*a new factor*/
   {
    j = i;
    if(count2 == 1){count1 = count1 + Digit(i);}
    else{count1 = count1 + Digit(i) + Digit(count2);}
    count2 = 1;
   }
  }
  else/*not a factor*/
  {
   i++;
  }
 }
/*last one factor*/
if(count2 != 1)
{count1 = count1 + Digit(count2);}

 if(count1>leno)
 {
  return 1;
 }
 else
 {
  return 0;
 }
}


int Digit(int a)
//REQUIRES: a > 1;
//EFFECTS: return the digits of a
{
 int length=0;
 while(a!=0)
 {
  a/=10;
  length++;
 }
 return length;
}







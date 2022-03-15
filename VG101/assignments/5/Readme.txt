Ex1.
    It use a subfunction to judge whether the number is a prime by a loop mod all the number less than it. The main function use loop to
test all the numbers less than the input number.
Ex2.
    It create a array contain all the numbers of days of a month in a year.Then, when input a month, it will find the corresponding number
which indicate the number of the days in that month. Then, use the strcmp to determine which day is the first day and go through a loop.
Ex3.
    It uses a loop to get 1 to 52. Then, print the corresponding deck.Then, get 52 random number and  store them in an array.Then,compare them
with the all the number stored in before. If the number is the same to any number in the array, get another random number.Do so until the 
number in the array are all different and random. Then print their corresponding deck.Then, use loop to sort them and print their corresponding
deck again.
Ex4.
    It uses the pointer. The subfunction begin with a declaration of two pointer ,pointing to a and b.Then, begin a loop of a. When meet a 
backspace, compare the following string with b. If the string are the same and end with a backspace or a punctuation or nothing,the string
b occurs one time. Then calculate the sum.
Ex6.
Ex6
1.
    Karatsuba Algorithm
The basic step of Karatsuba's algorithm is a formula that allows one to compute the product of two large numbers
 x and y using three multiplications of smaller numbers, each with about half as many digits as  x,y, plus some additions and digit shifts.

[cited from Wikipedia]

Input integer x,y
Output x*y

For two given large numbers x,y , x,y is stored in two n-digits strings in base 10.
For a 
positive integer m<n, x,y can be divided into 2 parts, which is represented as:
x=x1*10^m+x0
y=y1*10^m+y0
Where x0<10^m y0<10^m
x*y=(x1*10^m+x0)
*(y1*10^m+y0)=x1*y1*10^2m+(x1*y0+x0*y1)*10^m+x0*y0
Let z2=x1*y1 , z1=(x1+x0)*(y1+y0)-x1*y1-x0*y0=x1*y0+x0*y1, z0=x0*y0

Then x*y=z2*10^2m+z1*10^m+z0

Then the problem is simplified to compute x1*y1,(x1+x0)*(y1+y0) and x0*y0.

Then use x1,y1 as input , 
(x1+x0),(y1+y0) as input, x0,y0 as input , and use Karatsuba method to compute their multiplication, which is an recursion.
Ex6.3
     This program use interaction to improve efficiency.When calculate z0, it go through itself again and again.Also, it use << instead of 
multiplication, which will improve efficiency.
Ex6.5
void count(int b£¬int*ip,int*np){
      int n,i;
      n=0;
      while(b!=1){
      b>>=1;
      n=n+1;
                  }
      
     i=1<<n+1;
     *ip=i;*np=n;
 }
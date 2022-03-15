Ex6
1.Karatsuba Algorithm
The basic step of Karatsuba's algorithm is a formula that allows one to compute the product of two large numbers x and y using three multiplications of smaller numbers, each with about half as many digits as  x,y, plus some additions and digit shifts.
[cited from Wikipedia]

Input integer x,y
Output x*y

For two given large numbers x,y , x,y is stored in two n-digits strings in base 10.
For a positive integer m<n, x,y can be divided into 2 parts, which is represented as:
x=x1*10^m+x0
y=y1*10^m+y0
Where x0<10^m y0<10^m
x*y=(x1*10^m+x0)*(y1*10^m+y0)=x1*y1*10^2m+(x1*y0+x0*y1)*10^m+x0*y0
Let z2=x1*y1 , z1=(x1+x0)*(y1+y0)-x1*y1-x0*y0=x1*y0+x0*y1, z0=x0*y0
Then x*y=z2*10^2m+z1*10^m+z0

Then the problem is simplified to compute x1*y1,(x1+x0)*(y1+y0) and x0*y0.

Then use x1,y1 as input , (x1+x0),(y1+y0) as input, x0,y0 as input , and use Karatsuba method to compute their multiplication, which is an recursion.
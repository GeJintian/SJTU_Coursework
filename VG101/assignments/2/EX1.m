
a=input('Type in the year:');
while fix(a)~=a||a<=0
    a=input('Type in another year:');
end
b=mod(a,4);
if b==0
    disp('It is a leap year')
else
    disp('It is not a leap year')
end
clear all, clc;
n=input('please input the list of numbers: ','s');
a=strfind(n,' ');
b=length(a);
if b==0
    disp(n)
else
    i=1;
    x=str2num(n(1:a(1)-1));
    while i<=b-1
        y=str2num(n(a(i)+1:a(i+1)-1));
        if x<y
            x=y;
        end
        i=i+1;
    end
    y=str2num(n(a(b):end));
    if x<y
        x=y;
    end
    disp(x)
end

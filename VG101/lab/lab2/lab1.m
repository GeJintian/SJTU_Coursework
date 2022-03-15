function m=lab1(f,a,b)
c=(a+b)/2;
if f(a)==0,disp(a)
elseif f(b)==0,disp(b)
else
    while f(c)~=0 && abs(c-a)>=0.001 && abs(c-b)>=0.001
    if f(a)*f(c)<0
        b=c;c=(a+c)/2;
    else
        a=c;c=(b+c)/2;
    end
    end
    disp(c)
end
end
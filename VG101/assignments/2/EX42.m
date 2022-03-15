function EX42(f,m,n)
a=m(1);b=m(2);
if sign(f(a))~=sign(f(b)) && f(a)~=0 && f(b)~=0
    c=(a*f(b)-b*f(a))/(f(b)-f(a));
    while f(c)~=0 && abs(a-b)>1/10^n
        a=b;b=c;c=(a*f(b)-b*f(a))/(f(b)-f(a));
    end
    fprintf('%.10f\n',c);
elseif f(a)==0
    disp(a);
elseif f(b)==0
    disp(b);
end
end
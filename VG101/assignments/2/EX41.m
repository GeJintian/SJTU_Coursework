function EX41(f,m,n)
a=m(1);b=m(2);
if sign(f(a))~=sign(f(b)) && f(a)~=0 && f(b)~=0
    re(f,a,b,n)
elseif f(a)==0
    disp(a);
elseif f(b)==0
    disp(b);
end
end
function re(f,a,b,n)
c=(a*f(b)-b*f(a))/(f(b)-f(a));
if f(c)==0 || abs(a-b)<=1/10^n
    fprintf('%.10f\n',c);
else
    a=b;
    b=c;
    re(f,a,b,n)
end
end

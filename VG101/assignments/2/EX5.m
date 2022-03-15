function EX5(n)
a=num2str(n);
b=length(a);
c=0;
for i=1:b
    c=c+(str2num(a(i)))^b;
end
if c==n
    disp(c);
else
    n=n+1;EX5(n)
end
end



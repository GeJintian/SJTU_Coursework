a=uint64(0);
for i=1:64
    a=a+2^(i-1);
end
a=num2str(a);
fprintf('%s',a)

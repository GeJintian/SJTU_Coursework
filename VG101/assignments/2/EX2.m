a=input('Input a number:');
b=a+1
while isprime(b)==0 || mod(b,4)~=1
    b=b+1;
end
fprintf('the next prime is:%d\n',b)
for i=1:b
    for j=i:b
        if j^2+i^2==b^2
            fprintf('the squares are:%dand%d\n',i^2,j^2)
        end
    end
end
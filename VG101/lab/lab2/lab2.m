function lab2(n)
fd=fopen('file.txt','w');
a=rot90(pascal(n));
b=zeros(n,2*n-1);
for c=1:n
    d=diag(a,c-n);
    for e=(n+1-c):2:(n+c-1)
        A(c,e)=d((c+e-n+1)/2);
    end
end
A=num2str(A);
for g=1:n
    for h=1:length(A(1,:))
        if h~=1
            if A(g,h)=='0' && A(g,h-1)==' '
                A(g,h)=' ';
            end
        end
    end
end
for m=1:n-1
    A(m,1)=' ';A(m,8*n-7)=' ';
end
for q=1:n
fprintf(fd,'%s\n',A(q,:));
end
end
        
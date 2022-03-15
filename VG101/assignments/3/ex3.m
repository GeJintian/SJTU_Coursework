function ex3(n)
fd=fopen('file.txt','w');
for i=0:10
    a=n*i;
    fprintf(fd,'%d x% d = %d\r\n',n,i,a);
end
end
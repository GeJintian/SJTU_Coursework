
function ex1(n)
n=input('generate a graph,press 1;svae a graph,press 2; load a graph,press 3;colorize a garph, press 4;exit, press5:');
if n==1
    GenGraph(n);
elseif n==2
    SaveGraph(n);
elseif n==3
    ex1c(n);
elseif n==4
    exld(n);
end
end
function GenGraph(n)
n=input('please input the number:');
a=randi(2,n)-1;
disp(a)
f=1;
for i=1:n
    for j=1:n
        if a(i,j)==1
         V(f)=i;E(f)=j;
         f=f+1
        end
    end
end
G=grahp(V,E);
plot(G);
ex1(1);
end
function SaveGraph(n)
fprintf('the file name is ''graph''')
fd=fopen('file.txt','w');
fplot(G)


a=[0,1,1,1,0;1,0,1,0,1;1,1,0,0,0;1,0,0,0,1;0,1,0,1,0]
f=1;
for i=1:5
    for j=1:5
        if a(i,j)==1
         V(f)=i;E(f)=j;
         f=f+1;
        end
    end
end
disp(V)
disp(E)
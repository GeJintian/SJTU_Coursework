function lab3(k)
d=k(1);
m=k(2)-2;
h=num2str(k(3));
c=str2double(h(1))*10+str2double(h(2));
y=str2double(h(3))*10+str2double(h(4));
if m==-1
    m=11;y=y-1;
elseif m==0
    m=12;y=y-1;
end
day=1+mod((d+floor((13*m-1)/5)+y+floor(y/4)+floor(c/4)-2*c),7);
if day==1
    disp('Sunday');
elseif day==2
    disp('Monday');
elseif day==3
    disp('Tuesday');
elseif day==4
    disp('Wendesday');
elseif day==5
    disp('Tursday');
elseif day==6
    disp('Friday');
else
    disp('Saturday');
end
end
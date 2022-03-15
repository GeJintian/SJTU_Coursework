function EX3(n)
a=length(num2str(n));
if a==1 && n~=0
    EX31(n)
elseif a==1 && n==0
    fprintf('zero');
elseif a==2
    EX32(n)
elseif a==3
    EX33(n)
elseif a==4
    EX34(n)
elseif a==5
    EX35(n)
elseif a==6
    EX36(n)
elseif a==7
    EX37(n)
elseif a==8
    EX38(n)
elseif a==9
    EX39(n)
end
end
function EX39(n)
b=fix(n/10^8);
if fix(mod(n/10^8)/10^6)~=0
if b==9
    fprintf('nine hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==8
    fprintf('eight hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==7
    fprintf('seven hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==6
    fprintf('six hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==5
    fprintf('five hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==4
    fprintf('four hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==3
    fprintf('three hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==2
    fprintf('two hundreds and ');n=mod(n,10^8);EX38(n);
elseif b==1
    fprintf('one hundred and ');n=mod(n,10^8);EX38(n);
end
else
    if b==9
    fprintf('nine hundreds ');n=mod(n,10^6);EX36(n);
elseif b==8
    fprintf('eight hundreds ');n=mod(n,10^6);EX36(n);
elseif b==7
    fprintf('seven hundreds ');n=mod(n,10^6);EX36(n);
elseif b==6
    fprintf('six hundreds ');n=mod(n,10^6);EX36(n);
elseif b==5
    fprintf('five hundreds ');n=mod(n,10^6);EX36(n);
elseif b==4
    fprintf('four hundreds ');n=mod(n,10^6);EX36(n);
elseif b==3
    fprintf('three hundreds ');n=mod(n,10^6);EX36(n);
elseif b==2
    fprintf('two hundreds ');n=mod(n,10^6);EX36(n);
elseif b==1
    fprintf('one hundred ');n=mod(n,10^6);EX36(n);
    end
end
end
function EX38(n)
c=fix(n/10^7);
if c==9
    fprintf('ninety millions');n=mod(n,10^7);EX37(n);
elseif c==8
    fprintf('eighty millions');n=mod(n,10^7);EX37(n);
elseif c==0
    n=mod(n,10^7);EX37(n);
elseif c==7
    fprintf('seventy ');n=mod(n,10^7);EX37(n);
elseif c==6
    fprintf('sixty ');n=mod(n,10^7);EX37(n);
elseif c==5
    fprintf('fifty ');n=mod(n,10^7);EX37(n);
elseif c==4
    fprintf('forty ');n=mod(n,10^7);EX37(n);
elseif c==3
    fprintf('thirty ');n=mod(n,10^7);EX37(n);
elseif c==2
    fprintf('twenty ');n=mod(n,10^7);EX37(n);
elseif c==1
    if fix(n/10^6)==11
        fprintf('eleven millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==12
        fprintf('twelve millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==13
        fprintf('thirteen millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==14
        fprintf('fourteen millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==15
        fprintf('fifteen millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==16
        fprintf('sixteen millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==17
        fprintf('seventeen millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==18
        fprintf('eighteen millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==19
        fprintf('ninteen millions and ');n=mod(n,10^6);EX36(n);
    elseif fix(n/10^6)==10
        fprintf('ten millions and ');n=mod(n,10^6);EX36(n);
    end
end
end
function EX37(n)
d=fix(n/10^6);
    if d==9
        fprintf('nine millions and ');
    elseif d==8
        fprintf('eight millions and ');
    elseif d==7
        fprintf('seven millions and ');
    elseif d==6
        fprintf('six millions and ');
    elseif d==5
        fprintf('five millions and ');
    elseif d==4
        fprintf('four millions and ');
    elseif d==3
        fprintf('three millions and ');
    elseif d==2
        fprintf('two millions and ');
    elseif d==1
        fprintf('one millions and ');
    else
        fprintf('millions and');
    end
n=mod(n,10^6);
EX36(n)
end
function EX36(n)
e=fix(n/10^5);
if fix(mod(n,10^5)/10^3)~=0
if e==9
    fprintf('nine hundreds and ');
elseif e==8
    fprintf('eight hundreds and ');
elseif e==7
    fprintf('seven hundreds and ');
elseif e==6
    fprintf('six hundreds and ');
elseif e==5
    fprintf('five hundreds and ');
elseif e==4
    fprintf('four hundreds and ');
elseif e==3
    fprintf('three hundreds and ');
elseif e==2
    fprintf('two hundreds and ');
elseif e==1
    fprintf('one hundred and ');
end
n=mod(n,10^5);
EX35(n);
else
    if e==9
    fprintf('nine hundreds ');
elseif e==8
    fprintf('eight hundreds ');
elseif e==7
    fprintf('seven hundreds ');
elseif e==6
    fprintf('six hundreds ');
elseif e==5
    fprintf('five hundreds ');
elseif e==4
    fprintf('four hundreds ');
elseif e==3
    fprintf('three hundreds ');
elseif e==2
    fprintf('two hundreds ');
elseif e==1
    fprintf('one hundred ');
    end
n=mod(n,10^3)
EX33(n);
end
end
function EX35(n)
f=fix(n/10^4);
if f==9
    fprintf('ninety ');n=mod(n,10^4);EX34(n)
elseif f==8
    fprintf('eighty ');n=mod(n,10^4);EX34(n)
elseif f==0
    n=mod(n,10^4);EX34(n);
elseif f==7
    fprintf('seventy ');n=mod(n,10^4);EX34(n)
elseif f==6
    fprintf('sixty ');n=mod(n,10^4);EX34(n)
elseif f==5
    fprintf('fifty ');n=mod(n,10^4);EX34(n)
elseif f==4
    fprintf('forty ');n=mod(n,10^4);EX34(n)
elseif f==3
    fprintf('thirty ');n=mod(n,10^4);EX34(n)
elseif f==2
    fprintf('twenty ');n=mod(n,10^4);EX34(n)
elseif f==1
    if fix(n/10^3)==11
        fprintf('eleven thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==12
        fprintf('twelve thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==13
        fprintf('thirteen thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==14
        fprintf('fourteen thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==15
        fprintf('fifteen thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==16
        fprintf('sixteen thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==17
        fprintf('seventeen thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==18
        fprintf('eighteen thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==19
        fprintf('ninteen thousands and ');n=mod(n,10^3);EX33(n)
    elseif fix(n/10^3)==10
        fprintf('ten thousands and ');n=mod(n,10^3);EX33(n)
    end
end
end
function EX34(n)
g=fix(n/10^3);
    if g==9
        fprintf('nine thousands and ');
    elseif g==8
        fprintf('eight thousands and ');
    elseif g==7
        fprintf('seven thousands and ');
    elseif g==6
        fprintf('six thousands and ');
    elseif g==5
        fprintf('five thousands and ');
    elseif g==4
        fprintf('four thousands and ');
    elseif g==3
        fprintf('three thousands and ');
    elseif g==2
        fprintf('two thousands and ');
    elseif g==1
        fprintf('one thousands and ');
    elseif g==0
        fprintf('thousands and ');
    end
n=mod(n,10^3);
EX33(n)
end
function EX33(n)
h=fix(n/10^2);
if mod(n,10^2)~=0
if h==9
    fprintf('nine hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==8
    fprintf('eight hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==7
    fprintf('seven hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==6
    fprintf('six hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==5
    fprintf('five hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==4
    fprintf('four hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==3
    fprintf('three hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==2
    fprintf('two hundreds and ');n=mod(n,10^2);EX32(n);
elseif h==1
    fprintf('one hundred and ');n=mod(n,10^2);EX32(n);
elseif h==0
    n=mod(n,10^2);EX32(n);
end
else
if h==9
    fprintf('nine hundreds ');
elseif h==8
    fprintf('eight hundreds ');
elseif h==7
    fprintf('seven hundreds ');
elseif h==6
    fprintf('six hundreds ');
elseif h==5
    fprintf('five hundreds ');
elseif h==4
    fprintf('four hundreds ');
elseif h==3
    fprintf('three hundreds ');
elseif h==2
    fprintf('two hundreds');
elseif h==1
    fprintf('one hundred ');
end    
end
end
function EX32(n)
i=fix(n/10^1);
if i==9
    fprintf('ninety ');n=mod(n,10);EX31(n)
elseif i==0
    n=mod(n,10);EX31(n)
elseif i==8
    fprintf('eighty ');n=mod(n,10);EX31(n)
elseif i==7
    fprintf('seventy ');n=mod(n,10);EX31(n)
elseif i==6
    fprintf('sixty ');n=mod(n,10);EX31(n)
elseif i==5
    fprintf('fifty ');n=mod(n,10);EX31(n)
elseif i==4
    fprintf('forty ');n=mod(n,10);EX31(n)
elseif i==3
    fprintf('thirty ');n=mod(n,10);EX31(n)
elseif i==2
    fprintf('twenty ');n=mod(n,10);EX31(n)
elseif i==1
    if n==11
        fprintf('eleven');
    elseif n==12
        fprintf('twelve');
    elseif n==13
        fprintf('thirteen');
    elseif n==14
        fprintf('fourteen');
    elseif n==15
        fprintf('fifteen');
    elseif n==16
        fprintf('sixteen');
    elseif n==17
        fprintf('seventeen');
    elseif n==18
        fprintf('eighteen');
    elseif n==19
        fprintf('ninteen');
    elseif fix(n/10)==10
        fprintf('ten');
    end
end
end
function EX31(n)
if n==1
    fprintf('one');
elseif n==2
    fprintf('two');
elseif n==3
    fprintf('three');
elseif n==4
    fprintf('four');
elseif n==5
    fprintf('five');
elseif n==6
    fprintf('six');
elseif n==7
    fprintf('seven');
elseif n==8
    fprintf('eight');
elseif n==9
    fprintf('nine');
end
end
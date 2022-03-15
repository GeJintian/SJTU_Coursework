clear all
a=input('input the weight:');
b=input('if the weight is stone,please press 1,if it is pound,plese press 2,if it is kg,please press 3:','s');
if b=='1'
    s=[a,0];p=s*[14;0];k=s*[6.35;0];fprintf('pounds=%f\nkg=%f\n',p,k)
elseif b=='2'
    p=[a,0];s=p*[0.0714;0];k=p*[0.4536;0];fprintf('stones=%f\nkg=%f\n',s,k)
else
    k=[a,0];s=k*[0.1575;0];p=k*[2.2095;0];fprintf('stones=%f\npounds=%f\n',s,p)
end
    
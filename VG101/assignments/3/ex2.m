clear all, clc;
s(1)=struct('type','Jumpers Blue','Quantity',2,'Bought','04/2005','year',2005);
s(2)=struct('type','Jumpers Brown','Quantity',3,'Bought','02/2013','year',2013);
s(3)=struct('type','Jumpers Green','Quantity',5,'Bought','01/2015','year',2015);
s(4)=struct('type','Trousers Black','Quantity',3,'Bought','06/2012','year',2012);
s(5)=struct('type','Trousers Grey','Quantity',2,'Bought','04/2011','year',2011);
s(6)=struct('type','Trousers White','Quantity',1,'Bought','12/2013','year',2013);
s(7)=struct('type','T-shirts Blue','Quantity',1,'Bought','05/2010','year',2010);
s(8)=struct('type','T-shirts Green','Quantity',2,'Bought','09/2014','year',2014);
s(9)=struct('type','T-shirts Red','Quantity',3,'Bought','01/2012','year',2012);
s(10)=struct('type','T-shirts White','Quantity',2,'Bought','03/2008','year',2008);
s(11)=struct('type','T-shirts Yellow','Quantity',1,'Bought','11/2012','year',2012);
[m,i]=max([s(1:11).Quantity]);
s(i).type
a=mean([s(1:11).year]);
floor(a)
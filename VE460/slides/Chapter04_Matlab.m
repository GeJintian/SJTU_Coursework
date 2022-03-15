clear all; clc

whichcase=2;
switch whichcase
    case 1 % Example on Page 3
        syms R1 L1 R2 L2 C s;
        A=[-R1/L1 0 -1/L1; 0 -R2/L2 1/L2; 1/C -1/C 0];
        b=[1/L1; 0; 0];
        c=[1 0 0];
        simplify( c*inv(s*eye(3)-A)*b )
        
        pretty( collect( ans, 's') )
        
    case 2 % Example on Page 18
        syms Ra La Kb La Ki Jm Bm s
        A=[-Ra/La -Kb/La  0;
            Ki/Jm -Bm/Jm  0;
            0 1 0];
        b=[1/La; 0; 0];
        c=[0 0 1];
        simplify( c*inv(s*eye(3)-A)*b )
        
        pretty( collect( ans, 's') )
            
end
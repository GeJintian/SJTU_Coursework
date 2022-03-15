clear all; clc

whichcase=3;
switch whichcase
    case 1 % Define LTI systems in Matlab Control Toolbox
        num=[1 0];
        den=[1 1 1];
        Gs=tf(num, den)
        
        s=tf('s');
        Gs1=s/(s^2+s+1)
        
        Gnum={1 -1; 2 1}; Gden={[1 1], [1 0]; 1 [1 2]};
        Gs2=tf(Gnum, Gden)
        
        sys=simplify( feedback(Gs2, eye(2)) )
        
    case 2 %  Example on Page 9
        syms a b c d
        inv([a b; c d])
        pretty(ans)
        
        syms s
        Gs=[1/(s+1) -1/s; 2 1/(s+2)];
        Hs=eye(2);
        simplify( inv(eye(2)+Gs*Hs)*Gs )
        pretty(ans)
        
    case 3
        s=tf('s');                         % specify a transfer function using a rational function in the Laplace variable s
        sysG1=2;                           % define subsystem G1
        sysG2=4/s;                         % define subsystem G2
        sysG3=parallel(sysG1,sysG2);       % parallel combination of G1 and G2
        sysG4=1/s;                         % define subsystem G4
        sysG5=series(sysG3,sysG4);         % series combination of G3 and G4
        sysCL=feedback(sysG5,1,-1)         % feedback combination of G5 and G6
        
end
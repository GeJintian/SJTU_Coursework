clear all; clc

whichcase=5;
switch whichcase
    case 1 % Basic commands in Matlab Symbolic Toolbox
        syms x y s n
        
        % Polynomial calculations
        f=x^3+y^3;
        g=(x^2-1)*(x^4+x^3+x^2+x+1)*(x^4-x^3+x^2-x+1);
        
        factor(f)
        expand(g)
        
        z=factor(x^8+98*x^4*y^4+y^8)
        
        latex(z(1))
        latex(z(2))
        
        % Calculus calculations
        diff(sin(x)^2)
        int(sin(x)^2)
        taylor(sin(x), 'Order', 8)
        
    case 2 % Nonlinear observer for Motor model
        J=[0 -1; 1 0];
        
        syms k1 k2 d q w0 s kp ki real;
        
        K=[k1;k2]*[d q];
        l=[d;q]/(d^2+q^2);
        
        A=simplify( [ -(w0*J+K) K*J*[d;q] zeros(2,1);
            -kp*l'*J -kp*l'*[d;q] -ki;
            l'*J l'*[d;q] 0]);
        b=[0 0 1 0]';
        c=[kp*l'*J kp*l'*[d;q] ki];
        
        Gs=simplify( c*inv(s*eye(4)-A)*b )
        
    case 3 % Laplace transform
        syms a w t
        
        laplace(t)
         
        laplace(exp(-a*t))
        
        laplace(cos(w*t))
        
        laplace(sin(w*t))
        
        laplace(exp(-a*t)*sin(w*t))
        
    case 4 % Residue
        a=[1 6 11 6];
        b=[5 3];
        [r,p,k]=residue(b, a)

    case 5 % Inverse Laplace transformation
        syms s t
        ilaplace(-6/(s+3))
        
        ilaplace((5*s+3)/(s^3+6*s^2+11*s+6))
        
        ilaplace(1,s,t)
        
        % Example on Page 33
        [r,p,k]=residue(1, [1 5 9 7 2 0])
        
        Gs=1/(s*(s+1)^3*(s+2));
        ilaplace(Gs)
        
        k1=simplify(s*Gs);          pretty(k1)
        k2=simplify((s+2)*Gs);      pretty(k2)
        a3=simplify((s+1)^3*Gs);    pretty(a3)
        a2=simplify( diff(a3) );    pretty(a2)
        
        a1=simplify( 1/2*diff(a3,2) ); pretty(a1)
        
        s=0;  eval(k1)
        s=-2;  eval(k2)
        s=-1;  [eval(a3) eval(a2) eval(a1)]

        
        syms zeta wn s;
        ilaplace(wn^2/(s^2+2*zeta*wn*s+wn^2))
        
end
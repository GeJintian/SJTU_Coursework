clear all; clc; close all;

whichcase=2;
switch whichcase
    case 1 % Root locus: 1/( s*(s+1) )
        s=tf('s');
        sys1=1/( s*(s+1) );
        rlocus(sys1);
        grid on; axis equal; shg
        
    case 2 % Root locus: s/(s^2+1)
        s=tf('s');
        sys2=s/(s^2+1);
        rlocus(sys2);
        grid on; axis equal; shg

    case 3 % Root locus: (s+1)/( s*(s+2)*(s+3) )
        s=tf('s');
        sys3=(s+1)/( s*(s+2)*(s+3) );
        rlocus(sys3);
        grid on; axis equal; shg
        
    case 4 % Root locus
        s=tf('s');
        rlocus( 1/(s*(s+1)) );
        hold on; grid on; axis equal; shg
        
        rlocus( 1/(s*(s+1)*(s+2)) );
        axis equal; shg
        
        rlocus( 1/(s*(s+1)*(s+2)*(s+3)) );
        axis equal; shg
        
        close all;
        rlocus( 1/(s*(s+1)*(s^2+2*s+2)) );
        grid on; axis equal; shg
        
    case 5 % Addition of zeros to G(s)H(s)
        s=tf('s');
        rlocus( 1/(s*(s+1)) );
        hold on; grid on; axis equal; shg
        
        rlocus( (s+2)/(s*(s+1)) );
        axis equal; shg
        
        close all;
        rlocus( (s^2+2*s+2)/(s*(s+1)) );
        grid on; axis equal; shg
        
        close all;
        rlocus( 1/(s*(s+1)*(s+2)) );
        hold on; 
        rlocus( (s+2)/(s*(s+1)*(s+3)) );
        grid on; axis equal; shg
        
    case 6 % Example
        s=tf('s');
        rlocus( (s+1)/(s^2*(s+10)) );
        hold on; grid on; axis equal; shg
        
        rlocus( (s+1)/(s^2*(s+9)) );
        axis equal; shg
        
        rlocus( (s+1)/(s^2*(s+8)) );
        axis equal; shg
        
        rlocus( (s+1)/(s^2*(s+3)) );
        axis equal; shg
        
        rlocus( (s+1)/(s^2*(s+1)) );
        axis equal; shg
end
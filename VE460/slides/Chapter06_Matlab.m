clear all; clc

whichcase=1;
switch whichcase
    case 1 % Inverse Laplace transformation
        syms s t
        
        ilaplace(1/s/(s^2+1))
        laplace(ilaplace(1/s/(s^2+1)))
        
        ilaplace(1/(s^2+1)/(s^2+4))
        ilaplace(1/(s^2+1)^2)
        
end
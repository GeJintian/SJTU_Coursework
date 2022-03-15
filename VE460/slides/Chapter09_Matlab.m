clear all; clc

whichcase=6;
switch whichcase
    case 1 % Freq response for prototype 2nd order system
        zeta=[0.1 0.2 0.4 0.5 0.6 1/sqrt(2) 1.0 1.5 2.0];
        
        w=[0:0.01:3]; H=zeros(length(zeta), length(w));
        for k=1:length(zeta)
           sys1=tf(1, [1 2*zeta(k) 1]);
           H(k,:)=freqresp(sys1,w);
        end
        
        idx=find(zeta==1);
        plot(w, abs(H), 'c', w, abs(H(idx,:)), 'k')
        xlabel('\omega/\omega_n')
        ylabel('u=|M(j\omega)|')
        axis([0 3 0 6]); shg
        
    case 2 % Nyquist plot for K/(s+1)^2;
        K=1;
        s=tf('s');
        sys2=K/(s+1)^2;
        [re,im,w]=nyquist(sys2);
        
        x=squeeze(re); y=squeeze(im);
        plot(x, y, x, -y)
        axis([-0.4 1.2 -0.8 0.4]); axis equal; 
        shg
        
    case 3 % Nyquist plot for K/s(s+1)^2;
        K=1;
        s=tf('s');
        sys2=K/s/(s+1)^2;
        w=logspace(-2, 5, 100);
        [re,im]=nyquist(sys2,w);
        
        x=squeeze(re); y=squeeze(im);
        plot(x, y, x, -y); 
        shg

    case 4 % Nyquist plot for K/s(s+2)(s+10);
        K=1;
        s=tf('s');
        sys2=K/s/(s+2)/(s+10);
        w=logspace(-2, 5, 100);
        [re,im]=nyquist(sys2,w);
        
        x=squeeze(re); y=squeeze(im);
        plot(x, y); 
        shg
        
    case 5 %  Nyquist plot for K*exp(-s)/s;
        K=1;
        s=tf('s');
        sys2=K*exp(-s)/s;
        w=logspace(-1, 2, 1000);
        [re,im]=nyquist(sys2,w);
        
        x=squeeze(re); y=squeeze(im);
        plot(x, y); 
        axis equal; axis([-0.3 0.3 -0.4 0.4]); 
        shg    
        
    case 6 %  Nyquist plot for K*(0.1*s+1)^2/(s+1)^3/(0.01*s+1)^2;
        K=3000;
        s=tf('s');
        sys2=K*(0.1*s+1)^2/(s+1)^3/(0.01*s+1)^2;
        w=logspace(-3, 6, 1000);
        [re,im]=nyquist(sys2,w);
        
        x=squeeze(re); y=squeeze(im);
        plot(x, y, x, -y); 
        axis equal; 
        shg    
        
    case 7 % Bode plot for
        s=tf('s');
        sys3=10*(s+10)/s/(s+2)/(s+5);
        
        bode(sys3);
        grid on;
end
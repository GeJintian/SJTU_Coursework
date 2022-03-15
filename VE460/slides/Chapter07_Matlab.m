clear all; clc

whichcase=1;
switch whichcase
    case 1 % Step response for prototype 2nd order system
        zeta=[0.1:0.1:1.0 1.5 2.0];
        
        t=[0:0.1:13]; y=zeros(length(zeta), length(t));
        for k=1:length(zeta)
           sys1=tf(1, [1 2*zeta(k) 1]);
           y(k,:)=step(sys1,t);
        end
        
        plot(t, y)
        xlabel('\omega_n t')
        ylabel('y(t)')
        axis([0 13 0 1.8])
        
    case 2 % Adding poles to OLTF, zeta=1
        t=[0:0.1:20];
        zeta1=1;
        Tp=[0 1.0 2.0 5.0];
        for k=1:length(Tp)
            sys1=tf(1, [Tp(k) 1+2*zeta1*Tp(k) 2*zeta1 1]);
            y1(k,:)=step(sys1,t);
        end
        figure(1)
        plot(t, y1)
        xlabel('Time (sec)')
        ylabel('y(t)')
        axis([0 20 0 2])
        
    case 3 % Adding poles to OLTF, zeta=0.25
        t=[0:0.1:20];
        zeta2=0.25; 
        Tp=[0.2 0.667 1];
        for k=1:length(Tp)
            sys2=tf(1, [Tp(k) 1+2*zeta2*Tp(k) 2*zeta2 1]);
            y2(k,:)=step(sys2,t);
        end
        plot(t, y2)
        xlabel('Time (sec)')
        ylabel('y(t)')
        axis([0 20 0 2.8])

    case 4 % Adding a pole to CLTF
        t=[0:0.1:15];
        zeta=0.5; 
        Tp=[0 0.5 1 2 4];
        for k=1:length(Tp)
            den=conv([1 2*zeta 1], [Tp(k) 1]);
            sys=tf(1, den);
            y(k,:)=step(sys,t);
        end
        plot(t, y)
        xlabel('Time (sec)')
        ylabel('y(t)')
        axis([0 15 0 1.8])
        
    case 5 % Adding a zero to CLTF
        t=[0:0.1:15];
        zeta=0.5; 
        Tz=[0 1 3 6 10];
        for k=1:length(Tz)
            sys=tf([Tz(k) 1], [1 2*zeta 1]);
            y(k,:)=step(sys,t);
        end
        plot(t, y)
        xlabel('Time (sec)')
        ylabel('y(t)')
        axis([0 15 0 6])        
        
    case 6 % Adding a zero to OLTF
        t=[0:0.05:10];
        zeta=0.5; 
        Tz=[0 0.2 0.5 2 5 10];
        for k=1:length(Tz)
            sys=tf(6*[Tz(k) 1], [1 3 2+6*Tz(k) 6]);
            y(k,:)=step(sys,t);
        end
        plot(t, y)
        xlabel('Time (sec)')
        ylabel('y(t)')
        axis([0 10 0 2])            
end
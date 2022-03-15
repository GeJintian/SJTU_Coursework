import matplotlib.pyplot as plt

N = 1000 #Total number of people
delta = 0.1 #Recovery rate
beta = 0.2 #Transmission rate
R = 0
I = 1/1000
S = 999/1000
day = []
S_list = []
I_list = []
R_list = []
for i in range(1000):
    day.append([i])
    S_list.append([S])
    I_list.append([I])
    R_list.append([R])
    
    Stmp = S-S*I*beta
    Rtmp = R + delta * I
    Itmp = I + (beta*S*I-delta*I)

    S = Stmp
    R = Rtmp
    I = Itmp

Sline = plt.plot(day,S_list, label = 'Susceptible number')
Iline = plt.plot(day,I_list, label = 'Infected number')
Rline = plt.plot(day,R_list, label = 'Recovered number')
plt.setp(Sline, color = 'r')
plt.setp(Iline, color = 'g')
plt.setp(Rline, color = 'b')
plt.legend(loc='upper right')
plt.title('SIR Model')
plt.xlabel('Day')
plt.ylabel('Relative groups size (%)')
plt.show()

import numpy as np
s = [1,1,2,2,3,3,3,4,5]
t = [2,5,3,4,4,5,6,1,1]

matrix = np.zeros((6,6))
for i in range(9):
        matrix[s[i]-1][t[i]-1] = 1
beta = 0.85

r1 = r2 = r3 = r4 = r5 = r6 = 1/6
for i in range(200):
    r1t = beta*(r4+r5)+(1-beta)*1/6
    r2t = beta*(0.5*r1)+(1-beta)*1/6
    r3t = beta*(0.5*r2)+(1-beta)*1/6
    r4t = beta*(0.5*r2+1/3*r3)+(1-beta)*1/6
    r5t = beta*(1/3*r3+0.5*r1)+(1-beta)*1/6
    r6t = beta*(1/3*r3)+(1-beta)*1/6

    r1=r1t
    r2=r2t
    r3=r3t
    r4=r4t
    r5=r5t
    r6=r6t
print("Node1\t",r1,"\n",
    "Node2\t",r2,"\n",
    "Node3\t",r3,"\n",
    "Node4\t",r4,"\n",
    "Node5\t",r5,"\n",
    "Node6\t",r6,"\n")
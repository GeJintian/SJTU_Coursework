import numpy as np
s = [1,1,2,2,3,3,3,4,5]
t = [2,5,3,4,4,5,6,1,1]

matrix = np.zeros((6,6))
for i in range(9):
        matrix[s[i]-1][t[i]-1] = 1
print(matrix)
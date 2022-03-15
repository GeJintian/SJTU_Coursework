import matplotlib.pyplot as plt

name_list = {'Andy': 0, 'Claude':0, 'Frida':0, 'Georgia':0, 'Joan':0, 'Vincent':0, 'Lee':0, 'Pablo':0}

f = open("Employee_Relationships.txt","r")
line = f.readline()
line = line[:-1]
x = line.split()
while line:
    line = f.readline()
    line = line[:-1]
    x = line.split()
    if len(x) == 0: break
    if int(x[2]) > 0:
        name_list[x[0]] = name_list[x[0]] + 1
        name_list[x[1]] = name_list[x[1]] + 1
f.close()
number_list = []
for i in name_list:
    number_list.append(name_list[i])
print(number_list)
plt.hist(number_list,range = (0,8),rwidth=0.6)
#plt.axis([0,8,0,1])
plt.grid(True)
plt.title(u'Friend Distribution Graph')
plt.show()
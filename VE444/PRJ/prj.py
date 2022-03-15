#TODO:  1. implement the node embedding algorithm



import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Model, Sequential
from tensorflow.keras import layers
import random
import matplotlib.pyplot as plt

class ANN():
    def __init__(self, input_dim):
        self.input_dim = input_dim
        self.model = self.build_network()
    def build_network(self):

        model = Sequential([
        layers.Dense(25, input_dim = self.input_dim, activation='relu'),
        #layers.Dense(25,activation='relu'),
        layers.Dense(1)
        ])

        model.compile(optimizer = 'sgd',
         loss='binary_crossentropy',
          metrics = ["accuracy"])

        return model

class Collaborative_filtering():
    def __init__(self, number, mat, feat_num):
        self.map = mat
        self.number = number
        self.feat_num = feat_num
        self.user_feat = np.random.rand(self.number, self.feat_num)
        self.generate_feature()

    def generate_feature(self):
        J = self.Cost_function()
        #print(self.user_feat)
        #print('Before descent. loss is:',J)
        for i in range(self.number):
            for j in range(self.number):
                if i == j: continue
                self.Gradient_Descent(i,j)
                #print(self.user_feat)
        #print('After descent. loss is:',J)
        #print(self.user_feat)

    def Cost_function(self):
        J = 0
        for i in range(self.number):
            for j in range(self.number):
                if i == j: continue
                j_m = 0
                for k in range(self.feat_num):
                    j_m = j_m + self.user_feat[i][k] * self.user_feat[j][k]
                j_m = (j_m-self.map[i][j])*(j_m-self.map[i][j])
                J = J + j_m
        return J

    def Gradient(self, u1, u2):
        j=0
        for i in range(self.feat_num):
            j = j + self.user_feat[u1][i] * self.user_feat[u2][i]
        j = j - self.map[u1][u2]
        #print(j)
        return j

    def Gradient_Descent(self, u1, u2):
        gradient1 = np.zeros(self.feat_num)
        gradient2 = np.zeros(self.feat_num)
        y = self.map[u1][u2]
        for i in range(self.feat_num):
            gradient1[i] = 0.3*self.Gradient(u1,u2)*self.user_feat[u2][i] + 0.5*self.user_feat[u1][i]
            gradient2[i] = 0.3*self.Gradient(u1,u2)*self.user_feat[u1][i] + 0.5*self.user_feat[u2][i]
        for i in range(self.feat_num):
            self.user_feat[u1][i] -= gradient1[i]
            self.user_feat[u2][i] -= gradient2[i]


edges = np.zeros((347,347))
f = open("facebook/0.edges","r")
line = f.readline()
line = line[:-1]
x = line.split()
edges[int(x[0])-1][int(x[1])-1] = 1
while line:
    line = f.readline()
    line = line[:-1]
    x = line.split()
    if len(x) == 0: break
    edges[int(x[0])-1][int(x[1])-1] = 1
f.close()

features = np.zeros((347,224))
f = open("facebook/0.feat","r")
line = f.readline()
line = line[:-1]
x = line.split()
for i in range(224):
    features[int(x[0])-1][i] = int(x[i+1])
while line:
    line = f.readline()
    line = line[:-1]
    x = line.split()
    if len(x) == 0: break
    for i in range(224):
        features[int(x[0])-1][i] = int(x[i+1])
f.close()

#Begin to split dataset
#0~170, 171~346
store_edges = np.zeros((171,176))
pos_id = np.zeros((1263,2))
count = 0
for i in range(171):
    for j in range(176):
        k = j + 171
        if edges[i][k] == 1:
            store_edges[i][j] == 1
            pos_id[count][0] = i
            pos_id[count][1] = k
            count = count + 1
print(count)


#Preparing for training dataset
neg_id = np.zeros((5000,2))
idx1 = []
idx2 = []
for i in range(5000):
    m = random.randint(0,170)
    n = random.randint(0,175)
    while (store_edges[m][n] == 1) | m == n | ((m in idx1) & (n in idx2)):
        m = random.randint(0,170)
        n = random.randint(0,175)
    idx1.append(m)
    idx2.append(n)
    neg_id[i][0] = m
    neg_id[i][1] = n + 171


#900 pos and 900 neg for training, 363 pos and 600 neg for validation
#This is for the binary features
training_set = np.zeros((1800,224*2))
train_tag = np.zeros((1800,1))
for i in range(900):
    train_tag[i] = 1
    dx1 = pos_id[i][0]
    dx2 = pos_id[i][1]
    for m in range(224):
        training_set[i][m] = features[int(dx1)][m]
    for m in range(224):
        n = m + 224
        training_set[i][n] = features[int(dx2)][m]
for i in range(900):
    j = i+900
    train_tag[j] = 0
    dx1 = neg_id[i][0]
    dx2 = neg_id[i][1]
    for m in range(224):
        training_set[j][m] = features[int(dx1)][m]
    for m in range(224):
        n = m + 224
        training_set[j][n] = features[int(dx2)][m]
validation_set = np.zeros((963,224*2))
val_tag = np.zeros((963,1))
for i in range(363):
    j = i+900
    val_tag[i] = 1
    dx1 = pos_id[j][0]
    dx2 = pos_id[j][1]
    for m in range(224):
        validation_set[i][m] = features[int(dx1)][m]
    for m in range(224):
        n = m + 224
        validation_set[i][n] = features[int(dx2)][m]
for i in range(600):
    j = i+900
    k = i + 363
    dx1 = neg_id[j][0]
    dx2 = neg_id[j][1]
    for m in range(224):
        training_set[k][m] = features[int(dx1)][m]
    for m in range(224):
        n = m + 224
        training_set[k][n] = features[int(dx2)][m]

"""
CF = Collaborative_filtering(347, edges, 10)
#This is for CF generated features
training_set = np.zeros((1800,10*2))
train_tag = np.zeros((1800,1))
for i in range(900):
    train_tag[i] = 1
    dx1 = pos_id[i][0]
    dx2 = pos_id[i][1]
    for m in range(10):
        training_set[i][m] = CF.user_feat[int(dx1)][m]
    for m in range(10):
        n = m + 10
        training_set[i][n] = CF.user_feat[int(dx2)][m]
for i in range(900):
    j = i+900
    train_tag[j] = 0
    dx1 = neg_id[i][0]
    dx2 = neg_id[i][1]
    for m in range(10):
        training_set[j][m] = CF.user_feat[int(dx1)][m]
    for m in range(10):
        n = m + 10
        training_set[j][n] = CF.user_feat[int(dx2)][m]
print("2")
validation_set = np.zeros((963,10*2))
val_tag = np.zeros((963,1))
for i in range(363):
    j = i+900
    val_tag[i] = 1
    dx1 = pos_id[j][0]
    dx2 = pos_id[j][1]
    for m in range(10):
        validation_set[i][m] = features[int(dx1)][m]
    for m in range(10):
        n = m + 10
        validation_set[i][n] = features[int(dx2)][m]
for i in range(600):
    j = i+900
    k = i + 363
    dx1 = neg_id[j][0]
    dx2 = neg_id[j][1]
    for m in range(10):
        training_set[k][m] = features[int(dx1)][m]
    for m in range(10):
        n = m + 10
        training_set[k][n] = features[int(dx2)][m]
print("3")
"""

ML = ANN(224*2)
train_ds = [training_set,train_tag]
val_ds = [validation_set,val_tag]
#AUTOTUNE = tf.data.experimental.AUTOTUNE
#train_ds = train_ds.cache().shuffle(1000).prefetch(buffer_size=AUTOTUNE)
#val_ds = val_ds.cache().prefetch(buffer_size=AUTOTUNE)
history = ML.model.fit(
    x = training_set,
    y = train_tag,
    validation_data = (validation_set, val_tag),
    epochs = 10
)
#Plot the training result
acc = history.history['accuracy']
val_acc = history.history['val_accuracy']

loss=history.history['loss']
val_loss=history.history['val_loss']

epochs_range = range(10)

plt.figure(figsize=(8, 8))
plt.subplot(1, 2, 1)
plt.plot(epochs_range, acc, label='Training Accuracy')
plt.plot(epochs_range, val_acc, label='Validation Accuracy')
plt.legend(loc='lower right')
plt.title('Training and Validation Accuracy')

plt.subplot(1, 2, 2)
plt.plot(epochs_range, loss, label='Training Loss')
plt.plot(epochs_range, val_loss, label='Validation Loss')
plt.legend(loc='upper right')
plt.title('Training and Validation Loss')
plt.show()
scores = ML.model.evaluate(validation_set, val_tag, verbose=1)
print('result is :',scores)

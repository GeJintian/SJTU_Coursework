#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from sklearn import linear_model
from sklearn.model_selection import train_test_split


# In[2]:


dataset = pd.read_csv('C:/Users/69009/Desktop/last/441/problem/CALI.csv')
print(dataset)


# In[3]:


feature_names={"MedInc","HouseAge","AveRooms","AveBedrms","Population","AveOccup","Latitude","Longitude"}
df_x = pd.DataFrame(dataset, columns = feature_names)
df_y = pd.DataFrame(dataset, columns = {"HOUSING PRICE"})
df_x


# In[4]:


for column in df_x.columns:
    df_x[column] = (df_x[column] - df_x[column].min()) / (df_x[column].max() - df_x[column].min())
df_x


# In[5]:


x_train, x_test, y_train, y_test = train_test_split(df_x, df_y, test_size = 0.2, random_state = 4)


# In[6]:


model = linear_model.LinearRegression()
model.fit(x_train,y_train)
results = model.predict(x_test)
print(results)


# In[7]:


model.coef_


# In[8]:


from sklearn.metrics import mean_squared_error, r2_score
model_score = model.score(x_train,y_train)
print('R2 sq: ', model_score)
# The mean squared error
print("Mean squared error: %.2f"% mean_squared_error(y_test, results))
# Explained variance score: 1 is perfect prediction
print('Test Variance score: %.2f' % r2_score(y_test, results))


# In[9]:


print(np.c_[y_test.values, results][0:5,:])


# In[ ]:





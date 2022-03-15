#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
from sklearn import ensemble
from sklearn import tree


# In[2]:


dataset = pd.read_csv('C:/Users/69009/Desktop/last/441/problem/CALI.csv')
feature_names={"MedInc","HouseAge","AveRooms","AveBedrms","Population","AveOccup","Latitude","Longitude"}
df_x = pd.DataFrame(dataset, columns = feature_names)
df_y = pd.DataFrame(dataset, columns = {"HOUSING PRICE"})
for column in df_x.columns:
    df_x[column] = (df_x[column] - df_x[column].min()) / (df_x[column].max() - df_x[column].min())
x_train, x_test, y_train, y_test = train_test_split(df_x, df_y, test_size = 0.2, random_state = 4)
df_x


# In[3]:


params = {'n_estimators': 1000, 'max_depth': 4, 'min_samples_split': 2, 'learning_rate': 0.01, 'loss': 'ls'}
model = ensemble.GradientBoostingRegressor(**params)

model.fit(x_train, y_train)


# In[4]:


model.feature_importances_


# In[5]:


from sklearn.metrics import mean_squared_error, r2_score
model_score = model.score(x_train,y_train)
print('R2 sq: ',model_score)

y_predicted = model.predict(x_test)
# The mean squared error
print("Mean squared error: %.2f"% mean_squared_error(y_test, y_predicted))
# Explained variance score: 1 is perfect prediction
print('Test Variance score: %.2f' % r2_score(y_test, y_predicted))


# In[6]:


from sklearn.model_selection import cross_val_predict

fig, ax = plt.subplots()
ax.scatter(y_test, y_predicted, edgecolors=(0, 0, 0))
ax.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'k--', lw=4)
ax.set_xlabel('Actual')
ax.set_ylabel('Predicted')
ax.set_title("Ground Truth vs Predicted")
plt.show()


# In[ ]:





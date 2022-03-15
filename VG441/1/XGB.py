#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split

from sklearn.metrics import mean_squared_error, r2_score

from sklearn import ensemble
import xgboost as xgb


# In[2]:


dataset = pd.read_csv('C:/Users/69009/Desktop/last/441/problem/CALI.csv')
feature_names={"MedInc","HouseAge","AveRooms","AveBedrms","Population","AveOccup","Latitude","Longitude"}
df_x = pd.DataFrame(dataset, columns = feature_names)
df_y = pd.DataFrame(dataset, columns = {"HOUSING PRICE"})
for column in df_x.columns:
    df_x[column] = (df_x[column] - df_x[column].min()) / (df_x[column].max() - df_x[column].min())
df_x


# In[3]:


x_train, x_test, y_train, y_test = train_test_split(df_x, df_y, test_size = 0.2, random_state = 4)


# In[4]:


params = {'n_estimators': 500, "objective":"reg:linear",'colsample_bytree': 0.5,'learning_rate': 0.01,
                'max_depth': 4, 'alpha': 1}
xg_reg = xgb.XGBRegressor(**params)

xg_reg.fit(x_train,y_train)
y_predicted = xg_reg.predict(x_test)


# In[5]:


xg_reg.feature_importances_


# In[6]:


print("Mean squared error: %.2f"% mean_squared_error(y_test, y_predicted))
# Explained variance score: 1 is perfect prediction
print('Test Variance score: %.2f' % r2_score(y_test, y_predicted))


# In[8]:


params = {"objective":"reg:linear",'colsample_bytree': 0.5,'learning_rate': 0.01, 'max_depth': 4, 'alpha': 1}
data_dmatrix = xgb.DMatrix(data=df_x,label=df_y)
xg_reg = xgb.train(params=params, dtrain=data_dmatrix, num_boost_round=10)
xgb.plot_tree(xg_reg,num_trees=9)
plt.rcParams['figure.figsize'] = (70.0, 70.0)
plt.savefig('C:/Users/69009/Desktop/last/441/problem/XGB/fig1.jpg')
plt.show()


# In[ ]:





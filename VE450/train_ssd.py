import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import os
import pandas as pd

def Picture_segmentation(picture, theta):
    # picture should be a 3-D array representing the picture
    # theta should be the angle given by the radar
    # table should be a class of looking up table for position

    pos = theta
    #pos = table.find(theta)
    _,segmentation,_ = np.split(picture,(pos, pos+60),axis = 1)
    return segmentation

lena = mpimg.imread('0.jpg');
plt.imshow(lena)
plt.axis('on')
plt.show()




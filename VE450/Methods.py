import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import pandas as pd
import time
from tensorflow.keras import layers
from tensorflow.keras.models import Model, Sequential
from tensorflow.keras.layers import Dense, Activation, Input, Add, Conv2D, ZeroPadding2D, BatchNormalization, Flatten
from tensorflow.keras.layers import AveragePooling2D, MaxPooling2D, Dropout, GlobalMaxPooling2D, GlobalAveragePooling2D
from tensorflow.keras.preprocessing import image
from tensorflow.keras.applications.imagenet_utils import preprocess_input
from tensorflow.keras.optimizers import RMSprop
from IPython.display import SVG
import tensorflow.keras.backend as K
import os
import pathlib
import tensorflow as tf
from tensorflow.keras import regularizers


class Table():
    def __init__(self, path):
        self.table = pd.read_csv(path)
        self.path = path
    def add(self, theta, position):
        # Add one pair into the table
        self.table[theta] = position
    def save(self):
        # Save this table
        self.table.to_csv(self.path)
    def find(self, theta):
        # return the position given theta
        return self.table[theta][0]



# begin to construct the convolutional neural network
class CNN:
    def __init__(self, input_dim, output_dim):
        print("!!!!!!!!!!!!!!!Call init function")
        print("Input_dim is ",input_dim)
        print("Input_dim is ",output_dim)
        K.set_image_data_format('channels_last')
        self.input_dim = input_dim #Input dim is (h,w,3)
        self.output_dim = output_dim #class number
        self.model = self.build_network()

    def build_network(self):
        
        #This network has an architecture: c->p->c->p->c->p->fc->fc
        #Firstly scale the input
        #input_layer = layers.experimental.preprocessing.Rescaling(1./255, input_shape = self.input_dim)
        input_layer = Input(self.input_dim)
        Scale_layer = layers.experimental.preprocessing.Rescaling(1./255)(input_layer)

        #Zero-Padding: pads the border of X input with zeroes
        Padding_layer = ZeroPadding2D((3,3))(Scale_layer)
        
        # First Convolution layer
        # CONV->BN->RELU->MAXPOOL
        Conv_layer0 = Conv2D(16, 3, padding = "same", kernel_regularizer= regularizers.l1_l2(l1=1e-5,l2=1e-4), name = 'conv0')(Padding_layer)
        BN0 = BatchNormalization(axis = 3, name = 'bn0')(Conv_layer0)
        ACT0 = Activation('relu')(BN0)
        MAXPOOL0 = MaxPooling2D((2,2), name = 'max_pool0')(ACT0)

        # Second Convolution layer
        # CONV->BN->RELU->MAXPOOL
        Conv_layer1 = Conv2D(32, 3, padding = "same",kernel_regularizer= regularizers.l1_l2(l1=1e-5,l2=1e-4), name = 'conv1')(MAXPOOL0)
        BN1 = BatchNormalization(axis = 3, name = 'bn1')(Conv_layer1)
        ACT1 = Activation('relu')(BN1)
        MAXPOOL1 = MaxPooling2D((2,2), name = 'max_pool1')(ACT1)

        # Third Convolution layer
        # CONV->BN->RELU->MAXPOOL
        Conv_layer2 = Conv2D(64, 3, padding = "same",kernel_regularizer= regularizers.l1_l2(l1=1e-5,l2=1e-4), name = 'conv2')(MAXPOOL1)
        BN2 = BatchNormalization(axis = 3, name = 'bn2')(Conv_layer2)
        ACT2 = Activation('relu')(BN2)
        MAXPOOL2 = MaxPooling2D((2,2), name = 'max_pool2')(ACT2)

        # Fourth Convolution layer
        # CONV->BN->RELU->MAXPOOL
        Conv_layer3 = Conv2D(128, 3, padding = "same",kernel_regularizer= regularizers.l1_l2(l1=1e-5,l2=1e-4), name = 'conv3')(MAXPOOL2)
        BN3 = BatchNormalization(axis = 3, name = 'bn3')(Conv_layer3)
        ACT3 = Activation('relu')(BN3)
        MAXPOOL3 = MaxPooling2D((2,2), name = 'max_pool3')(ACT3)

        # FLATTEN + FULLYCONNECTED
        Flatten_layer = Flatten()(MAXPOOL3)
        FC0 = Dense(128, activation = 'sigmoid', name = 'fc0')(Flatten_layer)
        FC1 = Dense(self.output_dim, name = 'fc1')(FC0)
        
        #Create model
        model = Model(inputs = input_layer, outputs = FC1, name = 'Detection')
        """
        model = Sequential([
        layers.experimental.preprocessing.Rescaling(1./255, input_shape=self.input_dim),
        layers.Conv2D(16, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(),
        layers.Conv2D(32, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(),
        layers.Conv2D(64, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(),
        layers.Flatten(),
        layers.Dense(128, activation='relu'),
        layers.Dense(self.output_dim)
        ])
        """
        model.compile(optimizer = 'adam',
         loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
          metrics = ["accuracy"])

        return model


    def load(self, name):
        print("Call load function")
        print("Parameter is ", name)
        self.model.load_weights(name)
        print("Finish load")

    def save(self, name):
        self.model.save_weights(name)
    
    def pred(self, picture):
        print("Call pred function")
        a = mpimg.imread(picture)
        print("Finish reading picture")
        pic = np.array([a])
        print("Ready to predict ", pic.shape)
        prediction = self.model(pic, training = False)
        print("prediction is ", prediction)
        return prediction.index(max(prediction))


    def Picture_segmentation(picture, theta, table):
        # picture should be a 3-D array representing the picture
        # theta should be the angle given by the radar
        # table should be a class of looking up table for position
        plt.imshow(picture)
        plt.show()
        #pos = theta
        pos = table.find(theta)
        _,segmentation,_ = np.split(picture,(pos-100, pos+100),axis = 1)
    
        print('after division, shape is ', segmentation.shape)
        plt.imshow(segmentation)
        plt.show()

        return segmentation
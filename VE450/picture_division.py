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
import pydot
from IPython.display import SVG
import tensorflow.keras.backend as K
import os
import pathlib
import tensorflow as tf
from tensorflow.keras import regularizers
from tensorflow.python.framework.convert_to_constants import convert_variables_to_constants_v2

K.set_image_data_format('channels_last')


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


def Picture_segmentation(picture, theta, table):
    # picture should be a 3-D array representing the picture
    # theta should be the angle given by the radar
    # table should be a class of looking up table for position
    plt.imshow(picture)
    plt.show()
    pos = theta
    #pos = table.find(theta)
    _,segmentation,_ = np.split(picture,(pos-100, pos+100),axis = 1)
    
    print('after division, shape is ', segmentation.shape)
    plt.imshow(segmentation)
    plt.show()
    
    return segmentation


# begin to construct the convolutional neural network
class CNN:
    def __init__(self, input_dim, output_dim):
        self.input_dim = input_dim
        self.output_dim = output_dim
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
        FC0 = Dense(500, activation = 'sigmoid', name = 'fc0')(Flatten_layer)
        FC1 = Dense(128, activation = 'sigmoid', name = 'fc1')(FC0)
        FC2 = Dense(self.output_dim, name = 'fc2')(FC1)
        
        #Create model
        model = Model(inputs = input_layer, outputs = FC2, name = 'Detection')
        """
        
        model = Sequential([
        layers.experimental.preprocessing.Rescaling(1./255, input_shape=self.input_dim, name = "Input_layer"),
        layers.Conv2D(16, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(),
        layers.Conv2D(32, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(),
        layers.Conv2D(64, 3, padding='same', activation='relu'),
        layers.MaxPooling2D(),
        layers.Flatten(),
        layers.Dense(128, activation='relu'),
        layers.Dense(self.output_dim,name = "Output_layer")
        ])
        """
        model.compile(optimizer = 'adam',
         loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
          metrics = ["accuracy"])

        return model

    def load(self, name):
        self.model.load_weights(name)

    def save(self, name):
        self.model.save_weights(name)
    


#Training
#Set parameters
num_classes = 5 #number of classes
batch_size = 32
img_height = 480
img_width = 60
input_dim = (img_height, img_width, 3)
output_dim = num_classes
#Set dataset directory
data_dir = pathlib.Path('D:/SJTU/VE450_Training/1/picture')
image_count = len(list(data_dir.glob('*/*.jpg')))
print("Total image numbers: ",image_count)
#Set training set (80% of whole dataset)
train_ds = tf.keras.preprocessing.image_dataset_from_directory(
  data_dir,
  validation_split=0.2,
  subset="training",
  seed=123,
  image_size=(img_height, img_width),
  batch_size=batch_size)
#Set validation set (20% of whole dataset)
val_ds = tf.keras.preprocessing.image_dataset_from_directory(
  data_dir,
  validation_split=0.2,
  subset="validation",
  seed=123,
  image_size=(img_height, img_width),
  batch_size=batch_size)
class_names = train_ds.class_names
print("Class names are ", class_names)

#exit()
#Configure the dataset for performance
AUTOTUNE = tf.data.experimental.AUTOTUNE
train_ds = train_ds.cache().shuffle(1000).prefetch(buffer_size=AUTOTUNE)
val_ds = val_ds.cache().prefetch(buffer_size=AUTOTUNE)

#Begin to use neural network
CovNN = CNN(input_dim, output_dim)
#CovNN.load('C:/Users/69009/Desktop/object_detection/parameters/training_parameters')
#CovNN.load('Second_training_weights')
#Train the model
epochs = 10
history = CovNN.model.fit(
    train_ds,
    validation_data = val_ds,
    epochs = epochs
)
CovNN.save('C:/Users/69009/Desktop/object_detection/parameters/training_parameters')
#Plot the training result
acc = history.history['accuracy']
val_acc = history.history['val_accuracy']

loss=history.history['loss']
val_loss=history.history['val_loss']

epochs_range = range(epochs)

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

"""
#Test one sample
num_classes = 5 #number of classes
batch_size = 32
img_height = 480
img_width = 60
input_dim = (img_height, img_width, 3)
output_dim = num_classes
CovNN = CNN(input_dim, output_dim)
#CovNN.load('First_training_weights')
CovNN.load('C:/Users/69009/Desktop/object_detection/parameters/training_parameters')

pict1 = mpimg.imread('D:/SJTU/VE450_Training/Picture/picture/Blue/blue.jpg')
pict1 = np.array([pict1])
preid = CovNN.model(pict1,training = False)
print(preid)
"""



#Save architecture
print("!!!!Begin to save")
frozen_out_path = 'C:/Users/69009/Desktop/object_detection/frozen'
frozen_graph_filename = "frozen_graph"
frozen_model = CovNN.model
full_model = tf.function(lambda x: frozen_model(x))
full_model = full_model.get_concrete_function(tf.TensorSpec(frozen_model.inputs[0].shape, frozen_model.inputs[0].dtype))
frozen_func = convert_variables_to_constants_v2(full_model)
frozen_func.graph.as_graph_def()
layers = [op.name for op in frozen_func.graph.get_operations()]
print("-" * 60)
print("Frozen model layers: ")
for layer in layers:
    print(layer)
    print("-" * 60)
print("Frozen model inputs: ")
print(frozen_func.inputs)
print("Frozen model outputs: ")
print(frozen_func.outputs)
tf.io.write_graph(graph_or_graph_def = frozen_func.graph,
                    logdir = frozen_out_path,
                    name = f"{frozen_graph_filename}.pb",
                    as_text=False)
tf.io.write_graph(graph_or_graph_def = frozen_func.graph,
                    logdir = frozen_out_path,
                    name = f"{frozen_graph_filename}.pbtxt",
                    as_text=True)
#tf.keras.models.save_model(CovNN.model,"model_save")
print("Model saved!")



"""
#Time test
pict1 = mpimg.imread('orange.jpg')
pict1 = np.array([pict1])
pict2 = mpimg.imread('orange1.jpg')
pict2 = np.array([pict2])

while(1):
    preid = CovNN.model(pict1,training = False)
    time.sleep(0.01)
creid = CovNN.model(pict2,training = False)
time.sleep(0.01)
creid = CovNN.model(pict2,training = False)
time.sleep(0.01)
creid = CovNN.model(pict2,training = False)
time5 = time.time()

print(np.array(preid))
"""
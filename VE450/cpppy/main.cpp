#include <iostream>
#include <Python.h>

using namespace std;
int main() {
    Py_SetPythonHome(L"C:\\Users\\69009\\Anaconda3");

    Py_Initialize();
    int img_height = 480;
    int img_width = 60;
    int batch_size = 32;
    int num_classes = 6;
    if(!Py_IsInitialized()) return -1;
    //Change to the directory of .py
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('C:/Users/69009/Desktop/object_detection')");
    PyObject * pModule = NULL;//Declare of python module
    PyObject * pFunc = NULL;//Declare of python function
    PyObject * CovNN = NULL;//Pointer to neural network

    //CovNN = Methods.CNN(input_dim, output_dim)
    pModule = PyImport_ImportModule("Methods");
    if(pModule == NULL) {
        cout<<"Nothing is found"<<endl;
        return -1;
    }
    PyObject * pDict = PyModule_GetDict(pModule);//Get a list of function in this module
    if(pDict == NULL){
        cout << "There is no dictionary."<<endl;
        return -1;
    }
    PyObject * pClassCNN = PyDict_GetItemString(pDict, "CNN");
    if(pClassCNN == NULL){
        cout<<"Can't find CNN class."<<endl;
    }
    PyObject * Class_init_args = Py_BuildValue("(iii) i", img_height, img_width, 3, num_classes);
    CovNN = PyObject_CallObject(pClassCNN, Class_init_args);
    Py_DECREF(pModule);//Destroy
    Py_DECREF(pDict);
    Py_DECREF(Class_init_args);
    Py_DECREF(pClassCNN);

    //CovNN.load()
    PyObject * load_arg = Py_BuildValue("s", "C:/Users/69009/Desktop/object_detection/First_training_weights");
    PyObject_CallMethod(CovNN, "load","O", load_arg);
    Py_DECREF(load_arg);

    //CovNN.pred('orange.jpg')
    PyObject * picture_name = Py_BuildValue("s", "C:/Users/69009/Desktop/object_detection/orange.jpg");
    PyObject * predict = PyObject_CallMethod(CovNN, "pred","O", picture_name);
    //int result = -1000000;
    //PyArg_Parse(predict, "i", result);
    //cout<<result;
    Py_DECREF(predict);
    Py_DECREF(picture_name);
    Py_DECREF(CovNN);

    Py_Finalize();
    return 0;
}
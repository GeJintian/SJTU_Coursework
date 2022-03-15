#include <iostream>
#include <Python.h>

using namespace std;
int main() {
    Py_SetPythonHome(L"C:\\Users\\69009\\Anaconda3");

    Py_Initialize();
    if(!Py_IsInitialized()) return -1;
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('C:/Users/69009/Desktop/object_detection')");
    PyObject * pModule = NULL;//Declare of python module
    PyObject * PictureDivision = NULL;//Declare of python function

    return 0;
}
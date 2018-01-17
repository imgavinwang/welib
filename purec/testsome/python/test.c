#include <iostream>
#include <Python.h>
using namespace std;

int main(int argc, char* argv[])
{
    Py_Initialize();   //初始化

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pParam = NULL;
    PyObject* pResult = NULL;
    const char* pBuffer = NULL;
    int iBufferSize = 0;

    pModule = PyImport_ImportModule(“test_python");

    if (!pModule)
    {
        cout << "get module failed!" << endl;
        exit (0);
    }

    pFunc = PyObject_GetAttrString(pModule, "main");
    if (!pFunc)
    {
        cout << "get func failed!" << endl;
        cout << int(pFunc) << endl;
        exit (0);
    }
    pParam = Py_BuildValue("(s)", "HEHEHE");
    pResult = PyEval_CallObject(pFunc,pParam);
    if(pResult)
    {
        if(PyArg_Parse(pResult, "(si)", &pBuffer, iBufferSize))
        {
            cout << pBuffer << endl;
            cout << iBufferSize << endl;
        }
    }
    Py_DECREF(pParam);
    Py_DECREF(pFunc);

    Py_Finalize();
    //cout << "hello" << endl;
    return 0;
}
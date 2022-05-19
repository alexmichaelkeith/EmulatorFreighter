#ifndef SCRAPE_H
#define SCRAPE_H
#pragma push_macro("slots")
#undef slots
#define PY_SSIZE_T_CLEAN
#include "Python.h"
#pragma pop_macro("slots")
#include <string>
#include <chrono>
#include <thread>
inline void scrapeROMS() {
    std::printf("test");
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(5000ms);
    std::string funcName = "metadata";
    std::string query  = "test";
    char* procname = new char[funcName.length() + 1];
    strcpy(procname, funcName.c_str());
    char* paramval = new char[query.length() + 1];
    strcpy(paramval, query.c_str());
    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"scrapeIGDB");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyUnicode_AsString(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();
    // clean
    delete[] procname;
    delete[] paramval;
    //return _PyUnicode_AsString(presult);
}
#endif // SCRAPE_H

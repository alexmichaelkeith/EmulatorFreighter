// Custom Function created for Emulation Station
#pragma once

// Headers
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "json.hpp"
#include <Python.h>

// Custom headers
#include <structures.h>

// Namespace std, filesystem, and json
using namespace std;
using namespace filesystem;
using json = nlohmann::json;

// Function to read roms json file
vector<rom> readRomsJSON() {

    std::fstream fin;
    vector<rom> romVector;
    if (exists("config/paths/roms.json")) {
        fin.open("config/paths/roms.json", ios::in | ios::app);
        if(fin.is_open())
        {
            json j = json::parse(fin);
            romVector = j;
        }
    }

    return(romVector);

}

// Function to read emulators json file
vector<emulator> readEmulatorsJSON() {

    std::fstream fin;
    vector<emulator> emulatorVector;
    if (exists("config/paths/emulators.json")) {
        fin.open("config/paths/emulators.json", ios::in | ios::app);
        if(fin.is_open())
        {
            json j = json::parse(fin);
            emulatorVector = j;
        }
    }

    return(emulatorVector);

}


// Function used to call Python script and get a return string
string callIntFunc(string funcName, string query)
{

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
    return _PyUnicode_AsString(presult);
}

// Function to output roms as json file
void outputRomsJSON(vector<rom> romVector) {

    std::fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("config/paths/roms.json", std::ofstream::out | std::ofstream::trunc);
    fout.close();

    fout.open("config/paths/roms.json", ios::out | ios::app);
    json j = romVector;
    //fout << j;
    fout << std::setw(4) << j << std::endl;
}

// Function to output settings as json file
void outputConfigJSON(config myConfig) {

    std::fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("config/paths/config.json", std::ofstream::out | std::ofstream::trunc);
    fout.close();

    fout.open("config/paths/config.json", ios::out | ios::app);
    json j = myConfig;
    //fout << j;
    fout << std::setw(4) << j << std::endl;
}

// Function to open and read the config file
config readConfigJSON() {

    std::fstream fin;
    fin.open("config/paths/config.json", ios::in | ios::app);
    config myConfig;
    if(fin.is_open())
    {
    json j = json::parse(fin);
    myConfig = j;
    }
    return(myConfig);
}

// Function to return the correct emulator for each rom
string findRomEmulatorValues(vector<emulator> emulatorVector, rom currentRom, string value) {

    bool flag = false;
    for (int i = 0; i< emulatorVector.size();i++) {

        for (int j = 0; j< emulatorVector[i].extensions.size();j++) {

            if (emulatorVector[i].extensions[j] == currentRom.extension) {
                if (value == "emulator") {
                    return emulatorVector[i].name.c_str();
                }
                else if (value == "path") {

                    return emulatorVector[i].path;
                }
                else if (value == "midParameters") {

                    return emulatorVector[i].midParameters;
                }
                else if (value == "trailingParameters") {

                    return emulatorVector[i].trailingParameters;
                }
                flag = true;

            }

        }

    }

    if (flag == false) {
            return "No supported emulator configured.";
    }
}

// Function to find the compatible extensions
vector<string> getCompatibleExtensions(vector<emulator> emulatorVector, vector<string> compatibleExtensions) {

    for (int i = 0; i< emulatorVector.size();i++) {

        for (int j = 0; j< emulatorVector[i].extensions.size();j++) {

                    compatibleExtensions.push_back(emulatorVector[i].extensions[j]);
                }
            }

    return compatibleExtensions;
}

// Function to find image for widget tiles
string findImage(rom currentRom) {

    if (exists(currentRom.imagePathIGDB)) {
        return currentRom.imagePathIGDB;
    }
    else {
        return "config/images/covermissing.png";
    }
}

// Function to find name for widget tiles
string findName(rom currentRom) {

    if (currentRom.nameIGDB != "No Match Found" || currentRom.nameIGDB != "") {
        return currentRom.nameIGDB;
    }
    else {
        return currentRom.filename;
    }
}

// Function to find run path for roms
string getRunPath(string emulatorPath, string midParameters, string path, string trailingParameters) {

    string runPath;
    runPath = "\"\"" + emulatorPath + "\" " + midParameters + " \"" + path + "\"" + trailingParameters + "\"";

    return runPath;
}

// Function to remove commas from filename
string cleanupFilename(string fileName) {

    // Replace commas and semicolons to preserve csv file accuracy
    replace(fileName.begin(), fileName.end(), ',', ' '); // replace all ',' to ' '
    return fileName;
}

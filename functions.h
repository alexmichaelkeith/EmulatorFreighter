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
#include <Python.h>
#include "json.hpp"

// Custom headers
#include <structures.h>

// Namespace std and filesystem
using namespace std;
using namespace filesystem;
using json = nlohmann::json;

// Function to read roms.csv and return saved roms in a vector if the path is still exists
vector<rom> readRoms() {

    string line;
    string entry;
    string currentRom;
    vector<string> entryVector;
    vector<rom> romVector;

    // Create roms.csv if missing
    if (!exists("config/paths/roms.csv")) {
        std::ofstream myfile;
        myfile.open ("config/paths/roms.csv");
        myfile.close();
    }

    // Open roms.csv file
    fstream file ("config/paths/roms.csv", ios::in);
    if(file.is_open())
    {
        // Loop to read lines
        while(getline(file, line))
        {
            // Clear entryVector and take in line
            entryVector.clear();
            stringstream str(line);

            // Loop to get csv entries
            while(getline(str, entry, ','))
            {
                // Add word to temp vector
                entryVector.push_back(entry);
            }
                // Create instance of new rom
                currentRom = entryVector[0].c_str();
                rom currentRom;

                // Set rom values
                currentRom.filename = entryVector[0];
                currentRom.extension = entryVector[1];
                currentRom.filesize = stod(entryVector[2]);
                currentRom.path = {absolute(entryVector[3]).u8string()};
                currentRom.runpath = entryVector[4];
                currentRom.imagePathIGDB ={absolute(entryVector[5]).u8string()};
                currentRom.nameIGDB = entryVector[6];

                // Add emulator to vector
                if (exists(currentRom.path)) {
                    romVector.push_back(currentRom);
                }
            }
    }

    // Return rom Vector
    return(romVector);
}

// Function to read emulators.csv and return saved emulators in a vector if the path is still exists
vector<emulator> readEmulators() {

    string line;
    string entry;
    string currentEmulator;
    vector<string> entryVector;
    vector<emulator> emulatorVector;

    // Create emulators.csv if missing
    if (!exists("config/paths/emulators.csv")) {
        std::ofstream myfile;
        myfile.open ("config/paths/emulators.csv");
        myfile.close();
    }

    // Open emulators.csv file
    fstream file ("config/paths/emulators.csv", ios::in);
    if(file.is_open())
    {
        // Loop to read lines
        while(getline(file, line))
        {
            // Clear entryVector and take in line
            entryVector.clear();
            stringstream str(line);

            // Loop to get csv entries
            while(getline(str, entry, ','))
            {
                // Add word to temp vector
                entryVector.push_back(entry);
            }
                // Create instance of new emulator
                currentEmulator = entryVector[0].c_str();
                emulator currentEmulator;

                // Set emulator values
                currentEmulator.name = entryVector[0].c_str();
                currentEmulator.midParameters = entryVector[1].c_str();
                currentEmulator.trailingParameters = entryVector[2].c_str();
                currentEmulator.path = {absolute(entryVector[3]).u8string()};
                // Loop to add all extensions located after name and path
                for (int i = 4;i < entryVector.size();i++) {
                    currentEmulator.extensions.push_back(entryVector[i].c_str());
                }
                // Add emulator to vector
                if (exists(currentEmulator.path)) {
                    emulatorVector.push_back(currentEmulator);
                }
        }
    }

    // Return emulator Vector
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

// Function to output roms list to csv file
void outputRoms(vector<rom> romVector)
{
    // file pointer
    std::fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("config/paths/roms.csv", std::ofstream::out | std::ofstream::trunc);
    fout.close();

    fout.open("config/paths/roms.csv", ios::out | ios::app);
    for (int i = 0; i < romVector.size(); i++) {
        fout << romVector[i].filename << ","
             << romVector[i].extension << ","
             << romVector[i].filesize << ","
             << romVector[i].path << ","
             << romVector[i].runpath << ","
             << romVector[i].imagePathIGDB << ","
             << romVector[i].nameIGDB << endl;
        }
}

// Function to output roms as json file
void outputRomsJSON(vector<rom> romVector) {

    json j;
    std::ofstream file("config/paths/key.json");
    for(int i=0;i<romVector.size();i++) {
        json j = romVector[i];
        file << std::setw(4) << j << std::endl;
        cout << romVector[i].emulator << " " << romVector[i].emulatorpath << endl;
    }

    //std::ofstream file("key.json");
    //file << std::setw(4) << jVector[0] << std::endl;

}

// Function to output settings as json file
void outputSettingsJSON(vector<rom> romVector) {

    json j;
    std::ofstream file("config/paths/settings.json");
    for(int i=0;i<romVector.size();i++) {
        json j = romVector[i];
        file << std::setw(4) << j << std::endl;
        cout << romVector[i].emulator << " " << romVector[i].emulatorpath << endl;
    }

    //std::ofstream file("key.json");
    //file << std::setw(4) << jVector[0] << std::endl;

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

// Function to remove commas from filename
string cleanupFilename(string fileName) {

    // Replace commas and semicolons to preserve csv file accuracy
    replace(fileName.begin(), fileName.end(), ',', ' '); // replace all ',' to ' '
    return fileName;
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

// Function to read config file
config readConfig() {

    string line;
    string entry;
    vector<string> entryVector;
    config myConfig;

    // Create config.csv if missing
    if (!exists("config/paths/config.csv")) {
        std::ofstream myfile;
        myfile.open ("config/paths/config.csv");
        myfile.close();
    }

    // Open config.csv file
    fstream file ("config/paths/config.csv", ios::in);
    if(file.is_open())
    {
        // Loop to read lines
        while(getline(file, line))
        {
            // Clear entryVector and take in line
            entryVector.clear();
            stringstream str(line);

            // Loop to get csv entries
            while(getline(str, entry, ','))
            {
                // Add word to temp vector
                entryVector.push_back(entry);
            }

                // Loop to add all settings located in the current line
                for (int i = 0;i < entryVector.size();i++) {
                    myConfig.romDirectories.push_back(entryVector[i]);
                }

        }
    }

    // Return config map
    return(myConfig);
}

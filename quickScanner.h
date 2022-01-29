#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <Python.h>

// Custom headers
#include <functions.h>
#include <structures.h>


using namespace std;
using namespace filesystem;


class quickScanner {
    public:

        // scans roms directory and outputs vector of roms
        vector<rom> scanRoms() {
            // Read roms and emulator file
            vector<emulator> emulatorVector = readEmulators();


            for (int i=0;i<emulatorVector.size();i++) {
                cout << emulatorVector[i].name << endl;
            }
            cout << emulatorVector.size();



            vector<rom> romVectorCSV = readRoms();

            // Create roms vector
            vector<rom> romVector;

            // Create vector of compatible extensions
            vector<string> compatibleExtensions;
            compatibleExtensions = getCompatibleExtensions(emulatorVector, compatibleExtensions);

            // Create rom folder if nonexistent
            if(!exists("roms")) {
                create_directory("roms");
            }
            if(!exists("metadata")) {
                create_directory("metadata");
            }
            if(!exists("emulators")) {
                create_directory("emulators");
            }

            // Loop to search recursivly through the roms folder and cleanup filenames
            for (const auto & file : filesystem::recursive_directory_iterator("roms"))
            {
                // If it's a regular file, list it
                if (is_regular_file(file.path()) && (find(compatibleExtensions.begin(), compatibleExtensions.end(), file.path().extension().string()) != compatibleExtensions.end())) {

                    // Remove "," from filenames
                    string cleanedPath = cleanupFilename(file.path().string());
                    rename(file.path().string(), cleanedPath.c_str());
                }
            }

            // Loop to search recursivly through the roms folder
            string currentRom;
            string namesToScrape;
            bool flag = false;
            for (const auto & file : filesystem::recursive_directory_iterator("roms"))
            {

                // If it's a regular file and is not already in roms vector, list it
                if (is_regular_file(file.path()) && (find(compatibleExtensions.begin(), compatibleExtensions.end(), file.path().extension().string()) != compatibleExtensions.end())) {

                    // check if rom already exists in roms vector
                    flag = false;
                    for (int i=0;i<romVectorCSV.size();i++) {
                        if (file.path().stem().string() == romVectorCSV[i].filename && exists(romVectorCSV[i].path) && exists(romVectorCSV[i].imagePathIGDB)) {

                                flag = true;
                                romVector.push_back(romVectorCSV[i]);
                                break;
                        }
                    }

                    if (flag == false) {
                        // Create new instance of rom
                        currentRom = file.path().string();
                        rom currentRom;

                        //Assign rom values
                        currentRom.filename = file.path().stem().string();
                        currentRom.extension = file.path().extension().string();
                        currentRom.emulator = findRomEmulatorValues(emulatorVector,currentRom, "emulator");
                        currentRom.emulatorpath = findRomEmulatorValues(emulatorVector,currentRom, "path");
                        currentRom.filesize = file_size(file);
                        currentRom.path = {absolute(file.path()).u8string()};
                        currentRom.midParameters = findRomEmulatorValues(emulatorVector,currentRom, "midParameters");
                        currentRom.trailingParmeters = findRomEmulatorValues(emulatorVector,currentRom, "trailingParameters");
                        currentRom.runpath = getRunPath(currentRom.emulatorpath, currentRom.midParameters, currentRom.path, currentRom.trailingParmeters);

                        // Loop to create list of roms missing metadata
                        namesToScrape = namesToScrape + to_string(romVector.size()) + ';' + cleanupFilename(currentRom.filename) + ',';

                        // Add rom to romVector
                        romVector.push_back(currentRom);
                    }
                }
            }

            if (namesToScrape != "") {

                namesToScrape.pop_back();
                string s = callIntFunc("scrapeRom", namesToScrape);
                string delimiter = ",";
                string token;
                int romNumber;
                string romName;
                string imagePath;

                    vector<string> v;
                    stringstream ss(s);

                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, ',');
                        v.push_back(substr);
                    }

                    for (size_t i = 0; i < v.size(); i++) {
                        romNumber = stoi(v[i]);
                        i++;
                        romName = v[i];
                        i++;
                        romVector[romNumber].nameIGDB = romName;
                        imagePath = v[i];
                        romVector[romNumber].imagePathIGDB = imagePath;
                    }
            }

            // Return Completed romVector
            return romVector;
        }
};

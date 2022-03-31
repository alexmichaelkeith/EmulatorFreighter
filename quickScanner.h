#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
//#include <Python.h>

// Custom headers
#include <functions.h>
#include <structures.h>

using namespace std;
using namespace filesystem;

class quickScanner {
    public:

        // scans roms directory and outputs vector of roms
        vector<rom> scanRoms(config myConfig) {

            string namesToScrape;
            string currentRom;

            // Read roms and emulator file
            vector<emulator> emulatorVector = readEmulators();
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

            for (int i=0; i < myConfig.romDirectories.size();i++) {

                // Loop to search recursivly through the roms folder
                bool flag = false;
                for (const auto & file : filesystem::recursive_directory_iterator(myConfig.romDirectories[i]))
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


                            // Add rom to romVector
                            romVector.push_back(currentRom);
                        }
                    }
                }

            // Output metadataNeededVector to JSON



            // Return Completed romVector
            return romVector;
        }
     }
};

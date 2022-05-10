#ifndef EMULATORFREIGHTER_H
#define EMULATORFREIGHTER_H

#include <vector>
#include <string>

#include <filesystem>

#include <fstream>

#include <iostream>

#include "json.hpp"

#include <QUrl>

// Singleton Design Pattern EmulatorFreighter class definition

class EmulatorFreighter
{
    public:

        struct ROM {

            // define ROM variables
            std::string filename;
            std::string extension;
            std::string emulator;
            std::string emulatorpath;
            std::string midParameters;
            std::string trailingParmeters;
            std::string runpath;
            double filesize;
            std::string path;
            std::string imagePathIGDB;
            std::string nameIGDB;

            // Define JSON mapping scheme
            NLOHMANN_DEFINE_TYPE_INTRUSIVE(ROM, filename, extension, emulator, emulatorpath, midParameters, trailingParmeters, runpath, filesize, path, imagePathIGDB, nameIGDB);

            // Constructor
            ROM(std::filesystem::directory_entry file) {

                EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();
                this->filename = file.path().stem().string();
                this->extension = file.path().extension().string();
                this->emulator = emulatorFreighter.findRomEmulatorValues(getInstance().emulators,*this, "emulator");;
                this->emulatorpath = emulatorFreighter.findRomEmulatorValues(emulatorFreighter.emulators,*this, "path");
                this->filesize = file_size(file);;
                this->path = {absolute(file.path()).u8string()};
                this->midParameters = emulatorFreighter.findRomEmulatorValues(emulatorFreighter.emulators,*this, "midParameters");
                this->trailingParmeters = emulatorFreighter.findRomEmulatorValues(emulatorFreighter.emulators,*this, "trailingParameters");
                this->runpath = emulatorFreighter.getRunPath(this->emulatorpath, this->midParameters, this->path, this->trailingParmeters);

                emulatorFreighter.roms.push_back(*this);
            }

            // Blank Const fixes JSON Serializing issue?
            ROM() {}
         };
         struct Emulator {

            // Blank Const fixes JSON Serializing issue?
            Emulator() {}
            Emulator(std::string a, std::vector<std::string> b, std::string c, std::string d, std::string e) {// Constructor

                this->name = a;
                this->extensions = b;
                this->path = c;
                this->midParameters = d;
                this->trailingParameters = e;

                EmulatorFreighter& emulatorFreighter = EmulatorFreighter::getInstance();
                emulatorFreighter.emulators.push_back(*this);
            }
            // define Emulator variables
            std::string name;
            std::string path;
            std::string midParameters;
            std::string trailingParameters;
            std::vector<std::string> extensions;
            // Define JSON mapping scheme
            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Emulator, name, path, midParameters, trailingParameters, extensions);
        };
        struct Config {
            public:
                // Constructor
                Config() {}
                // define Config variables
                std::vector<std::string> romDirectories;
                int tileHeight;
                int tileWidth;
                // Define JSON Serializing scheme
                NLOHMANN_DEFINE_TYPE_INTRUSIVE(Config, romDirectories, tileHeight, tileWidth);
    };

    // EmulatorFreighter Singleton method
    public:
        static EmulatorFreighter& getInstance()
        {
            static EmulatorFreighter    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        EmulatorFreighter() {

            // Directory check
            verifyFileStructure();
            // Reading config, emulators, roms
            readConfig();
            readEmulators();
            readRoms();
            // Get Compatible Extensions
            getCompatibleExtensions();

        }

    public:
        EmulatorFreighter(EmulatorFreighter const&)               = delete;
        void operator=(EmulatorFreighter const&)  = delete;


    // EmulatorFreighter public variables

    public:
        // Create single instance of roms, vector of ROM
        std::vector<ROM> roms;
        // Create single instance of emulators, vector of Emulator
        std::vector<Emulator> emulators;
        // Create single instance of compatibleExtensions, vector of strings
        std::vector<std::string> compatibleExtensions;
        // Create single instance of config
        Config config;


    // EmulatorFreighter methods


    public:
        // Method to read roms json file
        void readRoms() {
            std::fstream fin;
            if (std::filesystem::exists("config/paths/roms.json")) {
                try {
                    fin.open("config/paths/roms.json", std::ios::in | std::ios::app);
                    if(fin.is_open())
                    {
                        nlohmann::json j = nlohmann::json::parse(fin);
                        roms = j;
                    }
                } catch (...) {}
            }
        }

        // Method to read emulators json file
        void readEmulators() {
            std::fstream fin;
            if (std::filesystem::exists("config/paths/emulators.json")) {
                try {
                    fin.open("config/paths/emulators.json", std::ios::in | std::ios::app);
                    if(fin.is_open())
                    {
                        nlohmann::json j = nlohmann::json::parse(fin);
                        emulators = j;
                    }
                } catch (...) {}
            }
        }

        // Method to read the config json file
        void readConfig() {
            std::fstream fin;
            fin.open("config/paths/config.json", std::ios::in | std::ios::app);
            try {
                if(fin.is_open())
                {
                    nlohmann::json j = nlohmann::json::parse(fin);
                    config = j;
                }
            }  catch (...) {}
        }

        // Method to write the roms json file
        void writeRoms() {

            std::fstream fout;
            fout.open("config/paths/roms.json", std::ofstream::out | std::ofstream::trunc);
            fout.close();
            fout.open("config/paths/roms.json", std::ios::out | std::ios::app);
            nlohmann::json j = roms;
            fout << std::setw(4) << j << std::endl;
        }

        // Method to write the emulators json file
        void writeEmulators() {

            std::fstream fout;
            fout.open("config/paths/emulators.json", std::ofstream::out | std::ofstream::trunc);
            fout.close();
            fout.open("config/paths/emulators.json", std::ios::out | std::ios::app);
            nlohmann::json j = emulators;
            fout << std::setw(4) << j << std::endl;
        }

        // Method to write the settings json file
        void writeConfig() {

            std::fstream fout;
            fout.open("config/paths/config.json", std::ofstream::out | std::ofstream::trunc);
            fout.close();

            fout.open("config/paths/config.json", std::ios::out | std::ios::app);
            nlohmann::json j = config;
            fout << std::setw(4) << j << std::endl;
        }

        // Method to return the correct emulator for each rom
        std::string findRomEmulatorValues(std::vector<Emulator> emulatorVector, ROM currentRom, std::string value) {

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


        // Method to verify file structure

        void verifyFileStructure(){

            std::fstream fout;

            // Create rom folder if nonexistent
            if(!std::filesystem::exists("roms")) {
                std::filesystem::create_directory("roms");
            }
            // Create metadata folder if nonexistent
            if(!std::filesystem::exists("metadata")) {
                std::filesystem::create_directory("metadata");
            }
            // Create emulators folder if nonexistent
            if(!std::filesystem::exists("emulators")) {
                std::filesystem::create_directory("emulators");
            }

            // Create Config folder if nonexistent
            if(!std::filesystem::exists("config")) {
                std::filesystem::create_directory("config");
            }

            // Create Config folder if nonexistent
            if(!std::filesystem::exists("config/paths")) {
                std::filesystem::create_directory("config/paths");
            }

            // Create roms file if nonexistent
            if(!std::filesystem::exists("config/paths/roms.json")) {
                writeRoms();
            }

            // Create emulators file if nonexistent
            if(!std::filesystem::exists("config/paths/emulators.json")) {
                writeEmulators();
            }

            // Create config file if nonexistent
            if(!std::filesystem::exists("config/paths/config.json")) {
                writeConfig();
            }
        }


        // Method to find the compatible extensions
        void getCompatibleExtensions() {

            for (int i = 0; i< emulators.size();i++) {
                for (int j = 0; j< emulators[i].extensions.size();j++) {
                    compatibleExtensions.push_back(emulators[i].extensions[j]);
                }
            }
        }

        // Method to find image for widget tiles
        std::string findImage(ROM currentRom) {

            if (std::filesystem::exists(currentRom.imagePathIGDB)) {
                return currentRom.imagePathIGDB;
            }
            else {
                return "config/images/covermissing.png";
            }
        }

        // Method to find name for widget tiles
        std::string findName(ROM currentRom) {
            if (currentRom.nameIGDB == "No Match Found" || currentRom.nameIGDB == "") {
                return currentRom.filename;
            }
            else {
                return currentRom.nameIGDB;
            }
        }

        // Method to find run path for roms
        std::string getRunPath(std::string emulatorPath, std::string midParameters, std::string path, std::string trailingParameters) {

            std::string runPath;
            runPath = "\"\"" + emulatorPath + "\" " + midParameters + " \"" + path + "\"" + trailingParameters + "\"";
            return runPath;
        }

        // Method to remove commas from filename
        std::string cleanupFilename(std::string fileName) {

            // Replace commas and semicolons to preserve csv file accuracy
            replace(fileName.begin(), fileName.end(), ',', ' '); // replace all ',' to ' '
            return fileName;
        }

        // Method to scan filesystem for roms
        void scanRoms() {
            std::string currentRom;

            // Verify file structure
            verifyFileStructure();

            for (int i=0; i < config.romDirectories.size();i++) {
                // Loop to search recursivly through the roms folder
                bool flag = false;
                try{
                    for (const auto & file : std::filesystem::recursive_directory_iterator(config.romDirectories[i]))
                    {
                        // If it's a regular file and is not already in roms vector, list it
                        if (is_regular_file(file.path()) && (find(compatibleExtensions.begin(), compatibleExtensions.end(), file.path().extension().string()) != compatibleExtensions.end())) {
                            // check if rom already exists in roms vector
                            flag = false;
                            for (int i=0;i<roms.size();i++) {
                                if (file.path().stem().string() == roms[i].filename && std::filesystem::exists(roms[i].path)) {
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag == false) {
                                // Create new instance of rom
                                currentRom = file.path().string();
                                ROM currentRom(file);
                            }
                        }
                    }
                } catch (...) {}
             }
            // Save ROMS file
            writeRoms();
        }
        void scrapeIGDB(){



        }
};

#endif // EMULATORFREIGHTER_H

#pragma once

#include <string>
#include <vector>
#include "json.hpp"
struct rom {

    public:
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
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(rom, filename, extension, emulator, emulatorpath, midParameters, trailingParmeters, runpath, filesize, path, imagePathIGDB, nameIGDB)
};

struct emulator {

    public:
        std::string name;
        std::string path;
        std::string midParameters;
        std::string trailingParameters;
        std::vector<std::string> extensions;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(emulator, name, path, midParameters, trailingParameters, extensions);

};

struct config {

    public:
        std::vector<std::string> romDirectories;
        int tileHeight;
        int tileWidth;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(config, romDirectories, tileHeight, tileWidth);
};

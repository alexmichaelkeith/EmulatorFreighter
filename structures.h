#pragma once

#include <string>
#include <vector>
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
};

struct emulator {

    public:
        std::string name;
        std::string path;
        std::string midParameters;
        std::string trailingParameters;
        std::vector<std::string> extensions;
};

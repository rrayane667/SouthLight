// fileUtil.cpp
#include "fileUtil.h"
#include <stdexcept>
#include <fstream>
#include <cstring>  // For std::strcpy

const char* readFiles(std::string path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::string s;
    std::string sTotal;
    while (std::getline(in, s)) {
        sTotal += s + "\n";
    }
    in.close();

    size_t size = sTotal.size() + 1;
    char* result = new char[size];

    // Call standard strcpy with exactly 2 arguments
    std::strcpy(result, sTotal.c_str());

    return result;
}

#include <iostream>
#include <fstream>
#include "Logger.h"
#include "load_file.h" 

std::string load_file(std::string path) {
    std::ifstream ip;
    std::string str;
    try {
        ip.open(path);
    }
    catch (const std::bad_alloc&) {
        LOG("FILE LOADER ERROR", "memory bad_alloc", WHITE_RED_CODE);
    }

    if (!ip.is_open()) {
        LOG("FILE LOADER ERROR", "file is not open " + path, WHITE_RED_CODE);
        return str;
    }

    std::string line;
    
    while (getline(ip, line)) { 
        str += line + '\n';
    }

    ip.close();
    return str;
}


#include "load_dialog.h"

std::string load_dialog(std::string path, std::string str_number){
    std::ifstream ip;
    std::string str;
    std::string line;
    std::string sub_line;
    bool next_read = false;
    bool next_read_ = false;

    try{
        ip.open(path);
    }
    catch(const std::bad_alloc&) {
        std::cout << "ERROR:MEMORY";  
        return str;  
    }
    if(!ip.is_open()){
        std::cout << "ERROR: file open" << '\n';
        return str;
    }

    while(getline(ip, line)){
        if(line.find(str_number + '*') != std::string::npos && !next_read){
            line = line.erase(0, line.find('*'));
            str += line + '\n';
            next_read = true;
        }
        else if(!(line.find('&') != std::string::npos) && next_read){
            if(line.find('*') != std::string::npos){
                line = line.erase(0, line.find('*'));
            }
            str += line + '\n';
            next_read_ = true;
        }
        if(line.find('&') != std::string::npos && next_read_){
            break;
        }
    }

    ip.close();
    return str;
}
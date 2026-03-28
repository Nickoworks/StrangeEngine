#include "Logger.h"

std::string getCurrentDateTime(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

#if defined(__APPLE__) || defined(__linux__)
void LOG(std::string type, std::string log){
    if(type == "WARNING" || type == "warning"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << YELLOW_CODE << "WARNING" << MAGENTA_CODE << "] "
        << GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "ERROR" || type == "error"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << RED_CODE << "ERROR" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "INFO" || type == "info"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << WHITE_CODE << "INFO" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "DEBUG" || type == "debug"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << ORANGE_CODE << "DEBUG" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "FATAL ERROR" || type == "fatal error"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << WHITE_RED_CODE << "FATAL ERROR" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else {
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << BLUE_CODE << type << MAGENTA_CODE << "] "
        << GREEN_CODE << log << RESET_CODE << std::endl;
    }
}

void LOG(std::string type, std::string log, std::string color){
    if(type == "WARNING" || type == "warning"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << YELLOW_CODE << "WARNING" << MAGENTA_CODE << "] "
        << GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "ERROR" || type == "error"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << RED_CODE << "ERROR" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "INFO" || type == "info"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << WHITE_CODE << "INFO" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "DEBUG" || type == "debug"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << ORANGE_CODE << "DEBUG" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else if(type == "FATAL ERROR" || type == "fatal error"){
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << WHITE_RED_CODE << "FATAL ERROR" << MAGENTA_CODE << "] "
        <<  GREEN_CODE << log << RESET_CODE << std::endl;
    } else {
        std::cout << MAGENTA_CODE << "[" << CYAN_CODE << getCurrentDateTime() 
        << MAGENTA_CODE << "] " << "[" << color << type << MAGENTA_CODE << "] "
        << GREEN_CODE << log << RESET_CODE << std::endl;
    }
}
#elif defined(_WIN32)
void LOG(std::string type, std::string log){
    if(type == "WARNING" || type == "warning"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "WARNING" << "] "
        << log << std::endl;
    } else if(type == "ERROR" || type == "error"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "ERROR" << "] "
        << log << std::endl;
    } else if(type == "INFO" || type == "info"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "INFO" << "] "
        << log << std::endl;
    } else if(type == "DEBUG" || type == "debug"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "DEBUG" << "] "
        << log << std::endl;
    } else if(type == "FATAL ERROR" || type == "fatal error"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "FATAL ERROR" << "] "
        << log << std::endl;
    } else {
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << type << "] "
        << log << std::endl;
    }
}

void LOG(std::string type, std::string log, std::string color){
    if(type == "WARNING" || type == "warning"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "WARNING"<< "] "
        << log << std::endl;
    } else if(type == "ERROR" || type == "error"){
        std::cout << "[" << getCurrentDateTime() 
         << "] " << "[" << "ERROR" << "] "
        << log << std::endl;
    } else if(type == "INFO" || type == "info"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "INFO" << "] "
        << log << std::endl;
    } else if(type == "DEBUG" || type == "debug"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "DEBUG" << "] "
        << log << std::endl;
    } else if(type == "FATAL ERROR" || type == "fatal error"){
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << "FATAL ERROR" << "] "
        << log << std::endl;
    } else {
        std::cout << "[" << getCurrentDateTime() 
        << "] " << "[" << color << type << "] "
        << log << std::endl;
    }
}
#endif


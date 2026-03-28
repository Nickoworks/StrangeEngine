#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

#define RESET_CODE     "\033[0m"
#define RED_CODE       "\033[31m"
#define WHITE_RED_CODE "\033[1;31m"
#define GREEN_CODE     "\033[32m"
#define YELLOW_CODE    "\033[33m"
#define BLUE_CODE      "\033[34m"
#define MAGENTA_CODE   "\033[35m"
#define CYAN_CODE      "\033[36m"
#define WHITE_CODE     "\033[37m"
#define ORANGE_CODE    "\033[38;5;214m"
std::string getCurrentDateTime();
void LOG(std::string type, std::string log);
void LOG(std::string type, std::string log, std::string color);

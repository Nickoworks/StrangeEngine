#pragma once

#include "Logger.h"

#if defined(__APPLE__)
#include <sys/sysctl.h>

#elif defined(__linux__)
#include <fstream>
#include <sstream>
#include <string>

#elif defined(_WIN32)
#include <windows.h>

#endif

void getCpuInfo();
void getMemoryInfo();

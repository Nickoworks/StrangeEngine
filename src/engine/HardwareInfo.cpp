#include "HardwareInfo.h"

#if defined(__APPLE__)
void getCpuInfo() {
    std::ostringstream oss;
    char cpu_brand[128];
    size_t len = sizeof(cpu_brand);
    sysctlbyname("machdep.cpu.brand_string", &cpu_brand, &len, NULL, 0);
    oss << "Processor: " << cpu_brand;
    LOG("HARDWARE INFO", oss.str(), GREEN_CODE);
}

void getMemoryInfo() {
    std::ostringstream oss;
    int64_t total_memory;
    size_t len = sizeof(total_memory);
    sysctlbyname("hw.memsize", &total_memory, &len, NULL, 0);
    oss << "Total Memory: " << total_memory / (1024 * 1024) << " MB";
    LOG("HARDWARE INFO", oss.str(), GREEN_CODE);
}

#elif defined(__linux__)
void getCpuInfo(){
    std::ostringstream oss;
    std::ifstream cpuFile("/proc/cpuinfo");
    std::string line;
    while(std::getline(cpuFile, line)){
        if(line.find("model name") != std::string::npos){
            oss << "Processor: " << line.substr(line.find(":") + 2);
            break;
        }
    }
    LOG("HARDWARE INFO", oss.str(), GREEN_CODE);
}

void getMemoryInfo(){
    std::ostringstream oss;
    std::ifstream memFile("/proc/meminfo");
    std::string line;
    while(std::getline(memFile, line)){
        if(line.find("MemTotal" != std::string::npos)){
            oss << "Total Memory: " << std::stoi(line.substr(line.find(":") + 1)) / 1024 << " MB";
            break;
        }
    }
    LOG("HARDWARE INFO", oss.str(), GREEN_CODE);
}

#elif defined(_WIN32)
void getCpuInfo(){
    std::ostringstream oss;
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    oss << "Processor: " << sysInfo.dwProcessorType;
    LOG("HARDWARE INFO", oss.str(), GREEN_CODE);
}

void getMemoryInfo(){
    std::ostringstream oss;
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    oss << "Total Memory: " << status.ullTotalPhys / (1024 * 1024) << " MB";
    LOG("HARDWARE INFO", oss.str(), GREEN_CODE);
}
#endif
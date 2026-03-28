#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <any>
#include <vector>
#include "Logger.h"

class ScriptRegistry{
private:
    static std::unordered_map<std::string, std::function<void()> > scripts;
public:
    using Script = std::function<void()>;
    static void registerScript(std::string name, Script script);
    static void runScript(std::string name);
    static bool isValidScript(std::string name);
};

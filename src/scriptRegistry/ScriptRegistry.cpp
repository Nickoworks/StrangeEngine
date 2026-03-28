#include "ScriptRegistry.h"

std::unordered_map<std::string, std::function<void()> > ScriptRegistry::scripts;
void ScriptRegistry::registerScript(std::string name, Script script){
    scripts[name] = script;
}

void ScriptRegistry::runScript(std::string name){
    auto script = scripts[name];
    if(script){
        script();
    } else {
        LOG("SCRIPT REGISTRY", "script not found " + name, YELLOW_CODE);
    }
}

bool ScriptRegistry::isValidScript(std::string name){
    auto script = scripts[name];
    if(script){
        return true;
    }
    return false;
}
